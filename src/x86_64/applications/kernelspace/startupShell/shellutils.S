global _destub_kb_isr
global curs_move
global put_prompt

_destub_kb_isr:
    mov ecx, [esp + 4]
    mov eax, 0x2
    int 0x80
    ret

curs_move:
    mov eax, 0x2
    mov ecx, [esp + 4]  ; X.
    mov ebx, [esp + 8]  ; Y.
    int 0x80
    ret

put_prompt:
    mov eax, 0x3
    mov ecx, [esp + 4]
    mov ebx, 0
    int 0x80
    ret
