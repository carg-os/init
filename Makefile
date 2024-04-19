BUILDDIR = $(CURDIR)/build

all: githooks $(BUILDDIR)/init.a

FORCE:

githooks: | hooks
	@git config core.hooksPath hooks/

$(BUILDDIR):
	@mkdir $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR)

CC = $(CROSS_PREFIX)gcc

SRCS = $(wildcard src/*.S src/*.c)
OBJS = $(patsubst src/%.S,$(BUILDDIR)/%.S.o,$(SRCS))
OBJS := $(patsubst src/%.c,$(BUILDDIR)/%.c.o,$(OBJS))
DEPS = $(patsubst %.o,%.d,$(OBJS))

CFLAGS = -std=gnu2x -I libc/include -I include/ -MMD -ffreestanding \
         -mcmodel=medany -O3 -fdata-sections -ffunction-sections -flto

libc:
	@git clone https://github.com/carg-os/libc.git

$(BUILDDIR)/%.S.o: src/%.S | $(BUILDDIR)
	@printf "  CCAS\t$(@F)\n"
	@$(CC) $< -c -o $@ $(CFLAGS)

$(BUILDDIR)/%.c.o: src/%.c | libc $(BUILDDIR)
	@printf "  CC\t$(@F)\n"
	@$(CC) $< -c -o $@ $(CFLAGS)

$(BUILDDIR)/libc.a: FORCE | libc $(BUILDDIR)
	@$(MAKE) -C libc BUILDDIR=$(BUILDDIR)

$(BUILDDIR)/init.o: $(OBJS) $(BUILDDIR)/libc.a | $(BUILDDIR)
	@printf "  CCLD\t$(@F)\n"
	@$(CC) $^ -r -o $@ -Wl,--whole-archive

$(BUILDDIR)/%.a: $(BUILDDIR)/%.o | $(BUILDDIR)
	@printf "  AR\t$(@F)\n"
	@$(AR) cr $@ $<

-include $(DEPS)
