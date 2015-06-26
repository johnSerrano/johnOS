//#include "keyboards/kbdus.h"
#include "keyboard.h"
#include "../kernel/utils.h"
#include "screen.h"

char getChar(){


  /*I don't like allocating this memory every time a key is pressed but for now it works*/
  unsigned char kbdus[128]=
    
    {
      0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
      '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
      0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
      '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
      '*',
      0, ' ', 0, /* capslock */
      0, /* f1... */
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0, /* ...f10 */
      0, /* numlock */
      0, /*scroll lock*/
      0, /*home*/
      0, /*uparrow*/
      0, /*pgup*/
      '-',
      0, /*leftarrow*/
      0, /*rightarrow*/
      '+',
      0, /*end*/
      0, /*downarrow*/
      0, /*pgdown*/
      0, /*insert*/
      0, /*delete*/
      0, 0, 0,
      0, /*f11*/
      0, /*f12*/
      0, /*else*/
    };
  
  int result;
  result = getScancode();
  if (result != (result & 127)){
    return 0;
  }
  result = result & 127;
  
  unsigned char ret;
  ret = kbdus[result];
  return (char) ret;
}


int getScancode(){
  int result;
  result = in_b(REGISTER_KEYBOARD_DATA);
  return result;
}

//TODO
char handleKBD(int currLinePosition){
  /*return char if key pressed, 0 if no key press*/
  
  char flag;
  char mychar = 0;



  /*read keyboard status*/
  flag = in_b(0x64);

  
  /*if there is data to read, read data*/
  if (flag & 0x1){
    mychar = getChar();

    //if at line cap, don't write
    if((mychar != '\b' && mychar != '\n') && currLinePosition == 99){
      mychar = 0;
    }
    
    if (mychar != 0){ //mychar returns 0 on keyup, deal with this differently, current is crutch
      if (!(mychar == '\b' && currLinePosition == 0)){ //DON'T BACKSPACE OVER PROMPT
	//print char to screen
	print_char(mychar, -1, -1, WHIT_BLK);
      }
      else {
	mychar = 0;
      }
    }
  }
  
  return mychar;
}



void print_kbd_flag(char flag){
  if(flag & 0x80){
    /* parity bit set */
    unsigned char strparity[] = "Parity set\n";
    print_at(strparity, 1, 0);
  }

  if(flag & 0x40){
    /*time out*/
    unsigned char strtimeout[] = "Time Out\n";
    print_at(strtimeout,2,0);
  }

  if(flag & 0x20){
    /*aux data*/
    unsigned char straux[] = "Aux Data set\n";
    print_at(straux,3,0);
  }

  if (flag & 0x10){
    /* keyboard free (not locked) */
    unsigned char strfree[] = "Keyboard not locked\n";
    print_at(strfree,4,0);
  }

  if (flag & 0x8){
    /*command byte written (not data)*/
    unsigned char strcmd[] = "Command byre written\n";
    print_at(strcmd,5,0);
  }

  if (flag & 0x4){
    /*self test successful*/
    unsigned char strtest[] = "Self test successful\n";
    print_at(strtest,6,0);
  }

  if (flag & 0x2){
    /* cpu data in input buffer */
    unsigned char strcpu[] = "CPU data in input buffer\n";
    print_at(strcpu,7,0);
  }

  if (flag & 0x1){
    /*output buffer not empty*/
    unsigned char strready[] = "output buffer ready \n";
    print_at(strready,8,0);
  }
}
