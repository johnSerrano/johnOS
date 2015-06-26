#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "utils.h"
#include "commands/command.h"

void main() {

  
  clear_screen();

  unsigned char strsplash[] = "JohnOS";
  print_at(strsplash, 10, 37);

  unsigned char strpressenter[] = "Press Enter";
  print_at(strpressenter, 24, 0);
  
  /*wait for enter to progress*/
  char currChar = 0;
  while(currChar != '\n'){
    currChar = handleKBD(99);
  }
  

  clear_screen();
  prompt();


  /*current line array*/
  unsigned char currLine[100];
  int currLinePointer = 0;

  
  //MAIN LOOP
  while(0==0){



    //HANDLE KEYBOARD//
    currChar = handleKBD(currLinePointer);

    //add currchar to currline
    if (currChar != 0 && currChar != '\n' && currChar != '\b'){
      if (currLinePointer < 99){
		currLine[currLinePointer] = currChar;
		currLinePointer++;
      }
    }
    
    else if (currChar == '\n'){
	
      
	//RUN COMMAND//

	
	  _execute(currLine, currLinePointer);
	
	
	//END RUN COMMAND//

      prompt();

      currLinePointer = 0;





      
    }
    else if (currChar == '\b' && currLinePointer >= 0){
      
      currLinePointer -= 1;
    }

    
    //END HANDLE KEYBOARD//
    
  }
}

void _execute(unsigned char* currLine, int currLinePointer){

  unsigned char toExecute[currLinePointer + 1];
  
  int i;
  for (i = 0; i <= currLinePointer; i++){
    toExecute[i] = currLine[i];
  }

  toExecute[currLinePointer] = '\0';

//  unsigned char strdebug[] = "Debugging";

//  print(toExecute);

  execute(toExecute);
  

}