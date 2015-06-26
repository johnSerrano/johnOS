#include "helloWorld.h"
#include "../utils.h"
#include "../../drivers/keyboard.h"

typedef int (*functionPtr)();


struct command{
  
  unsigned char* name; //max command size 15 //might need to make malloc for this to work
  functionPtr function;

};

struct command commands[2];

int execute(unsigned char* arg){
  //check commands name, if match, execute function at pointer
  //kernel can call this to execute command line functions

  //filler hello command

  unsigned char commandone[] = "hello";
  commands[0].name = *commandone;
  commands[0].function = &hello;

  unsigned char commandtwo[] = "clear";
  commands[1].name = *commandtwo;
  commands[1].function = &clear;

  print(commands[0].name); //prints 'S '


  int i;
  for (i = 0; i < 2; i++){ //i < number of commands
    
    if(strcmp(arg, commands[i].name)){ //commands[].name is broken so this doesnt work
      
      commands[i].function(); //breaks things
      
    }
  }

  return 0;
}
