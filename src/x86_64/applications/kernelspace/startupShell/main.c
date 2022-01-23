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

static char buffer[(MAX_CURSOR_X - MIN_CURSOR_X) + 1];
static unsigned int bufferIdx = 0;

int _ssmain() {
    curs_move(18, 2);
    put_prompt("Kernel@ToxicOS~$ ");
    _destub_kb_isr(kb_isr);
    return 0;
}


static unsigned char bufcmp(const char* str) {
    unsigned int buflen = 0;
    while (buffer[buflen++]);

    for (int i = 0; i < buflen; ++i) {
        if (buffer[i] != str[i]) {
            return 0;
        }
    }

    return 1;
}


static unsigned short buflen() {
    unsigned short buflen;
    while (buffer[buflen++]);
    return buflen;
}


static void reset_prompt() {
     for (int i = 0; i < buflen() + 1; ++i) {
            buffer[i] = '\0'; 
        }

        for (int i = 0; i < cursor_x; ++i) {
            __asm__ __volatile__("mov $0x5, %eax; int $0x80");
        }

        curs_move(cursor_x = MIN_CURSOR_X, cursor_y);
        put_prompt("Kernel@ToxicOS~$ ");

        bufferIdx = 0;
}


static void clear_prompt() {
    curs_move(0x0, 80);

    for (int i = 0; i < cursor_x; ++i) {
            __asm__ __volatile__("mov $0x5, %eax; int $0x80");
        }
}


static void reset_cursor() {
    curs_move(cursor_x = MIN_CURSOR_X, 0x2);
}



void kb_isr() {
    unsigned short scancode = inportb(0x60);
    static unsigned char prompt_mode = 1;
    char ch = SC_ASCII[scancode];

   if (ch >= 'a' && ch <= 'z' && cursor_x < MAX_CURSOR_X && prompt_mode) {
        curs_move(++cursor_x, cursor_y);
        ch -= 0x20;
        putch(ch);
        buffer[bufferIdx] = ch;
        ++bufferIdx;
    } else if (ch == '\x08' && cursor_x > MIN_CURSOR_X && prompt_mode) {
        curs_move(--cursor_x, cursor_y);
        __asm__ __volatile__("mov $0x5, %eax; int $0x80");
        --bufferIdx;
        buffer[bufferIdx] = '\0';
    } else if (scancode == 28 && prompt_mode) {
       if (bufcmp("REBOOT\0")) {
            __asm__ __volatile__("mov $0x0, %eax; int $0x80");
       }
    }
 


    send_pic_eoi();     // END OF INTERRUPT.
}
