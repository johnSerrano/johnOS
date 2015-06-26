//useful kernel utilities

void memcopy(char* source, char* destination, int no_bytes){
  
  //copy memory from one place to another. does not check anything, so be careful!

  int i;
  for (i=0; i<no_bytes; i++){
    *(destination+i) = *(source+i);
  }
}

unsigned char in_b(unsigned short port){

  //read data in from port. useful for low level io

  
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}


void out_b(unsigned short port, unsigned char data){

  //write data to port
  
  __asm__("out %%al, %%dx" : :"a" (data), "d" (port));

}


int strcmp(unsigned char* arg1, unsigned char* arg2){

  //compare two strings. if equal, return 1. Otherwise, return 0.

  //strings should be null terminated.

  //if no termination, automatically terminate after 100 characters.


  
  int equal = 1;
  
  int i;
  for (i = 0; i < 100; i++){
    if (arg1[i] != 0 && arg2[i] != 0){
      if (arg1[i] != arg2[i]){
	equal = 0;
	i = 100; //break
      }
    }
    else{
      i = 100; //break
    }

  }
  
  return equal;
}

