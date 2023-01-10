#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include "commonFunctions.h"
#include <string.h>
#define LOOKUP_SIZE 4096
enum Modes
{
  LossMode = 1,
  StringMode = 2
};
int main()
{
  init();
  int iterationTime, lossReportInterval;
 
  switch (selectMode())
  {
  case LossMode:
    printf("Please enter the training iteration. (integer)\n>>");
    scanf("%d", &iterationTime);
    printf("Please enter the interval to report quadratic loss (integer)\n>>");
    scanf("%d", &lossReportInterval);
    nnQuadraticLoss(iterationTime, lossReportInterval);
    break;
  case StringMode:
    printf("Please enter the training iteration. (integer)\n");
    printf("The training result would be better if trained for 5000 times for 1 layer with 2 nodes per layer.\n>>");
    scanf("%d", &iterationTime);
    nnTrain(iterationTime);
    getBitString(getInput());
    break;
  }
  return 0;
}
