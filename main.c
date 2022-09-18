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
  int iterationTime, lossReportInterval;
  
  switch (selectMode())
  {
  case 1:
    printf("Please enter the training iteration. (integer)");
    scanf("%d", &iterationTime);
    printf("Please enter the interval to report quadratic loss (integer)");
    scanf("%d", &lossReportInterval);
    dlQuadraticLoss(iterationTime, lossReportInterval);
    break;
  case 2:
    printf("Please enter the training iteration. (integer)\n");
    printf("The training result would be better if trained for 30000 times.\n");
    scanf("%d", &iterationTime);

    dlTrain(iterationTime);
    getOutput(getInput());
    break;
  }
  return 0;
}
