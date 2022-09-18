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
  int iterationTime, lossReportinterval;
  
  switch (selectMode())
  {
  case 1:
    printf("Please enter the training iteration. (integer)");
    scanf("%d", &iterationTime);
    printf("Please enter the interval to report quadratic loss (integer)");
    scanf("%d", &lossReportinterval);
    dlQuadraticLoss(iterationTime, 1000);
    break;
  case 2:
    printf("Please enter the training iteration. (integer)");
    scanf("%d", &iterationTime);

    dlTrain(iterationTime);
    getOutput(getInput());
    break;
  }
  return 0;
}
