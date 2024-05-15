all: build/karg

clean:
	@rm -rf build

fmt:
	@clang-format -i $(shell find -not -path "./build/*" -name "*.[ch]")

build:
	@mkdir build
	@cmake -B build -D CMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE) \
		-D LIBC_INCLUDE=$(LIBC_INCLUDE) -D LUA_INCLUDE=$(LUA_INCLUDE)

FORCE:

build/karg: FORCE | build
	@cmake --build build
