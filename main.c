#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include "commonFunctions.h"
#include <string.h>
#define LOOKUP_SIZE 4096


int main()
{
  init();
  char *inputString;
  // inputString =  getInput();

  
  switch(selectMode()){
    case 1:
    
    dlTrain(30000,1000,true);
    break;
    case 2:
    dlTrain(30000,1000,false);
    inputString =  getInput();
  }
 
  
}
