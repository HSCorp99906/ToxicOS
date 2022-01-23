ENTRY(start)

SECTIONS {
    . = 1M;

    .boot : 
    {
        *(.multiboot_header)
    }

   	. = 0x100000;
   	.text : { *(.text) }
   	.data : { *(.data) }
   	.bss  : { *(.bss)  }
}
