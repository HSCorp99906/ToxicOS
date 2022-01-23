// EXTERNEL FUNCTION DECLARATIONS.
void curs_move(int x, int y);
void put_prompt(char* prompt);
// END

int _ssmain() {
    curs_move(18, 2);
    put_prompt("Kernel@ToxicOS~$ ");
    return 0;
}
