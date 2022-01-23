#define _KERNEL_START


#include "drivers/VGA.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupt_handlers.h"
#include "memory/GDT.h"

#define SW 80

char* vga_main = (char*)0xB8000;

int _start() { 
    _gdt_install();
    idt_install();
    vga_clear(&vga_main, 0x1, 0xE);
    vga_puts("Kernel Initialized.", &vga_main, 1); 
    set_idt_desc32(0x0, div_by_0_handler, TRAP_GATE_FLAGS);
    return 0;
}
