
#define REGISTER_KEYBOARD_DATA 0x60

char getChar();
int getScancode();
void read_kbd_flag(char flag);
char handleKBD(int currLinePosition);
