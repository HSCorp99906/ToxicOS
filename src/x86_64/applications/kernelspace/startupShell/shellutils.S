global _destub_kb_isr


_destub_kb_isr:
    mov ecx, [esp + 4]
    mov eax, 0x2
    int 0x80
    ret
