#define _KERNEL_START


#include "drivers/VGA.h"
#include "drivers/IO.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupt_handlers.h"
#include "memory/GDT.h"

#define SW 80

char* vga_main = (char*)0xB8000;

static void unmask_kb_irq() {
    outportb(PIC1_DATA_PORT, 0xFD);
}


static void kb_irq_stub() {
    outportb(0x20, 0x20);
}


int _start() { 
    _gdt_install();
    idt_install();

    set_idt_desc32(0x0, div_by_0_handler, TRAP_GATE_FLAGS);
    set_idt_desc32(0x21, kb_irq_stub, INT_GATE_FLAGS);
    unmask_kb_irq();
    __asm__ __volatile__("sti");

    vga_clear(&vga_main, 0x1, 0xE);
    vga_puts("Kernel Initialized.", &vga_main, 1); 

    return 0;
}
