ENTRY(_start)
SECTIONS {
    . = 0x84000000;

    .text : {
        *(.text .text.*)
    }

    . = ALIGN(4K);
    .rodata : {
        *(.rodata .rodata.*)
    }

    . = ALIGN(4K);
    .data : {
        *(.data .data.*)
    }

    .sdata : {
        *(.sdata .sdata.*)
    }

    .sbss : {
        *(.sbss .sbss.*)
    }

    .bss : {
        *(.bss .bss.*)
    }
}
