#ifndef SYSCALLS_H
#define SYSCALLS_H

#define MAX_SYSCALLS 1

#include "../../drivers/IO.h"
#include "../../drivers/VGA.h"
#include "../IDT.h"
#include "../../util/types.h"

void syscall_restart() {
    outportb(0x64, 0xFE);
}


void* syscalls[MAX_SYSCALLS] = {
    syscall_restart,
};

#endif
