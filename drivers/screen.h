#define VID_ADDR 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHIT_BLK 0x0f //color setting

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

int handle_scrolling(int offset);
void set_cursor(int offset);
int get_cursor();
int get_screen_offset(int col, int row);
void print_char(char character, int row, int col, char attribute);
void clear_screen();
void print_at(unsigned char* message, int row, int col);
void print(char* message);
unsigned char in_b(unsigned short port);
void out_b(unsigned short port, unsigned char data);
