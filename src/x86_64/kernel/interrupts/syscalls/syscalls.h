#ifndef SYSCALLS_H
#define SYSCALLS_H

#define MAX_SYSCALLS 3

#include "../../drivers/IO.h"
#include "../../drivers/VGA.h"
#include "../IDT.h"
#include "../../util/types.h"

void syscall_restart() {
    outportb(0x64, 0xFE);
}


void syscall_curs_move() {
    register const uint16_t X asm("ecx");
    register const uint16_t Y asm("ebx"); 
    update_cursor(X, Y);
}


void syscall_change_kb_isr() {
    register void* isr asm("ecx");
    set_idt_desc32(0x21, isr, INT_GATE_FLAGS);
}


void* syscalls[MAX_SYSCALLS] = {
    syscall_restart,
    syscall_change_kb_isr,
    syscall_curs_move,
};

#endif
