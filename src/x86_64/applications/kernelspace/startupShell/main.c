#include "../../../kernel/drivers/IO.h"   // Only driver we will use in our application.


#define MIN_CURSOR_X 18
#define MAX_CURSOR_X 35

// EXTERNEL FUNCTION DECLARATIONS.
void curs_move(int x, int y);
void put_prompt(char* prompt);
void send_pic_eoi();
void putch(char ch);
void _destub_kb_isr(void* fptr);
// END


void kb_isr();

unsigned int cursor_x = 18;
unsigned int cursor_y = 2;

const unsigned char* const SC_ASCII = "\x00\x1B" "1234567890-=" "\x08"
"\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
"zxcvbnm,./" "\x00\x00\x00" " ";


int _ssmain() {
    curs_move(18, 2);
    put_prompt("Kernel@ToxicOS~$ ");
    _destub_kb_isr(kb_isr);
    return 0;
}


void kb_isr() {
    unsigned short scancode = inportb(0x60);
    char ch = SC_ASCII[scancode];

    if (ch >= 'a' && ch <= 'z' && cursor_x < MAX_CURSOR_X) {
        curs_move(++cursor_x, cursor_y);
        ch -= 0x20;
        putch(ch);
    } else if (scancode == 57 && cursor_x < MAX_CURSOR_X) {
        curs_move(++cursor_x, cursor_y);
        putch(' ');
    } else if (ch == '\x08' && cursor_x > MIN_CURSOR_X) {
        curs_move(--cursor_x, cursor_y);
        __asm__ __volatile__("mov $0x5, %eax; int $0x80");
    }

    send_pic_eoi();     // END OF INTERRUPT.
}
