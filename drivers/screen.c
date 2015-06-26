#include "screen.h"
#include "../kernel/utils.h"

//function to print a character to the screen
void print_char(char character, int row, int col, char attribute){

  //pointer to start of video memory
  unsigned char* vidmem = (unsigned char*) VID_ADDR;
  
  //default color scheme
  if (!attribute){
    attribute = WHIT_BLK;
  }

  //memory offset
  int offset; 
  // if row and col < 0, offset is cursor

  if (col >= 0 && row >= 0){
    offset = get_screen_offset(col, row);
  }
  else {
    offset = get_cursor();
  }
  int backspace = 0;
  if (character == '\b'){
    //backspace
    offset -= 2;
    character = ' ';
    backspace = 1;
  }
  
  if (character == '\n'){
    //new line
    int rows = offset / (2 * MAX_COLS);
    offset = get_screen_offset(79, rows);
  }

  else{
    unsigned char* locale = vidmem + offset;
    unsigned char* attr_locale = vidmem + offset + 1;
    *locale = character;
    *attr_locale = attribute;
  }

  if (backspace == 0){
    offset += 2;
  }
  offset = handle_scrolling(offset);
  set_cursor(offset);
}


//returns the linear offset for video memory of screen x, y coord
int get_screen_offset(int col, int row){
  return (((row * 80) + col) * 2);
}

int get_cursor(){

  out_b(REG_SCREEN_CTRL, 14); // cursor offset high byte
  int offset = in_b(REG_SCREEN_DATA) << 8; //set offset high byte
  out_b(REG_SCREEN_CTRL, 15); // cursor offset low byte
  offset += in_b(REG_SCREEN_DATA); //set offset low byte

  return offset * 2;
}

void set_cursor(int offset){
  offset /= 2;
  
  out_b(REG_SCREEN_CTRL, 14); //see get cursor comments
  out_b(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  out_b(REG_SCREEN_CTRL, 15);
  out_b(REG_SCREEN_DATA, (unsigned char)(offset));
}
		

int handle_scrolling(int offset) {
  if (offset < MAX_ROWS * MAX_COLS*2){
    return offset;
  }

  int i;
  for (i = 1; i < MAX_ROWS; i++){
    memcopy((char*)(get_screen_offset(0, i) + VID_ADDR), (char*)(get_screen_offset(0,i-1) + VID_ADDR), (MAX_COLS * 2));
  }

  char* last_line = (char*) get_screen_offset(0, MAX_ROWS - 1) + VID_ADDR;
  for (i=0; i < MAX_COLS; i++){
    last_line[i] = 0;
  }

  offset -= 2*MAX_COLS;
  return offset;
}

void clear_screen(){
  int row = 0;
  int col = 0;

  for (row=0; row<MAX_ROWS; row++){
    for (col=0; col<MAX_COLS; col++){
      print_char(' ', row, col, WHIT_BLK);
    }
  }

  set_cursor(get_screen_offset(0,0));
}

void print_at(unsigned char* message, int row, int col){ //string must be manually created for some reason
                                               
  if (col >= 0 && row >= 0){
    int a = get_screen_offset(col, row);
    set_cursor(a);
  }
  
  int i=0;
  while (message[i] != '\0'){
    
    print_char(message[i], -1, -1, WHIT_BLK);
    i++;
  }
}

void print(char* message){
  print_at(message, -1, -1);
}

void prompt(){
  unsigned char strprompt[] = ">>>: ";
  print(strprompt);
}
