#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include <string.h>
#define LOOKUP_SIZE 4096

void init();
void getInput();
void dlIterate(int maxIteration, int iterationSteps);
void generateAns(char *string);
void getOutput(char *string);
void checkAns();
void calError();
void dlTrain(int iteration,int lossReportSteps);
void convertToBinary(char n);
void displaybits(char n);
void getTrainAns(char *string);
void calloc2dArray(double **array, int row, int col);
bool dlXor(char num1, char num2);
double *sampleOutput;
double **sampleInput;
char *string;
double *trainingResult;

int main()
{

  init();
  dlTrain(30000,10000);
  getInput();

  // getOutput();
  // generateAns();
  free(string);
}
void init()
{
  double *lookup;
  lookup = calloc(LOOKUP_SIZE, sizeof(double));
  /* This will make the neural network initialize differently each run. */
  /* If you don't get a good result, try again for a different result. */
  srand(time(0));

  /* Input and expected out data for the XOR function. */
  // double *input = (double*);,malloc(4*2*sizeof(double));
  sampleOutput = calloc(4, sizeof(double));
  sampleInput = calloc(4, sizeof(double *));

  calloc2dArray(sampleInput, 4, 2);

  sampleInput[0][0] = 0;
  sampleInput[0][1] = 0;
  sampleInput[1][0] = 0;
  sampleInput[1][1] = 1;
  sampleInput[2][0] = 1;
  sampleInput[2][1] = 0;
  sampleInput[3][0] = 1;
  sampleInput[3][1] = 1;
  sampleOutput[0] = 0;
  sampleOutput[1] = 1;
  sampleOutput[2] = 1;
  sampleOutput[3] = 0;

  /* New network with 2 inputs,
   * 1 hidden layer of 2 neurons,
   * and 1 output. */
}
void getInput()
{
  string = (char *)malloc(100);
  printf("Please enter a string. This Program will output the XOR checksum of this string.");
  scanf("%s", string);
  // printf("\n%s\n", string1);
  
  getOutput(string);
}
// data storage in this area should be refined.
void generateAns(char *string)
{
  int result = 0;
  for (int i = 0; i < (strlen(string)) * 8; i++)
  {
    // printf("%d|", (int)string[i]);
    result ^= string[i];
  }
  // result ^= string[strlen(string)-1];

  printf("\nchecksum: %d\n", result);
}
void getOutput(char *string)
{
  char *outputBits;
  outputBits = calloc(strlen(string), sizeof(char));
  for (int i = 0; string[i] != 0; i++)
  {
    for (int j = 7; j >= 0; j--)
    {
      outputBits[i * 8 + j] = ((string[i] & (1 << j)) >> j); // gets each bit of character
    }
    // printf("\n");
  }
  // for (int i = 0; i < strlen(string) * 8; i++)
  // {
  //   printf("%d", outputBits[i]);
  //   if (i % 8 == 7)
  //     printf("\n");
  // }

  generateAns(outputBits);
  getTrainAns(outputBits);
}
void dlTrain(int iteration,int lossReportSteps)
{
  genann *ann = genann_init(2, 1, 2, 1);
  double quadraticLoss;

  /* Train on the four labeled data points many times. */
  for (int i = 0; i < iteration; ++i)
  {
    quadraticLoss = 0;
    genann_train(ann, sampleInput[0], sampleOutput + 0, 3);
    genann_train(ann, sampleInput[1], sampleOutput + 1, 3);
    genann_train(ann, sampleInput[2], sampleOutput + 2, 3);
    genann_train(ann, sampleInput[3], sampleOutput + 3, 3);
    // if(i % lossReportSteps == 1 && i != iteration){
    //   for(int j = 0; j < 4; j++ ){
    //     quadraticLoss += pow((*genann_run(ann,sampleInput[j]) - *(sampleOutput + j)),2);
    //   }
    //   printf("Quadratic loss for %d is %f\n",i, quadraticLoss);
    // }
  }

  /* Run the network and see what it predicts. */

  trainingResult = (double *)malloc(4);
  printf("Training Result: ");
  for (int i = 0; i < 4; i++)
  {
    trainingResult[i] = round(*genann_run(ann, sampleInput[i]));
    printf("%1.f ", trainingResult[i]);
  }
  printf("\n");
  genann_free(ann);
}
void dlIterate(int maxIteration, int iterationSteps)
{
  for (int i = 1; i < maxIteration; i += iterationSteps)
  {
    // dlTrain(i);
    getOutput(string);
  }
}
void calloc2dArray(double **array, int row, int col)
{
  // array = calloc(row, sizeof(double*));
  for (int i = 0; i < row; i++)
  {
    sampleInput[i] = calloc(col, sizeof(*(array[i])));
  }
}
void getTrainAns(char *string)
{
  bool xorChecksum = 0;
  for (int i = 0; i < (strlen(string)) * 8; i++)
  {
    xorChecksum = dlXor(xorChecksum, string[i]);
    // printf("%d", string[i]);
    // result  ^= string[i];
  }
  printf("\n DL-Learning: %d", xorChecksum);
}
bool dlXor(char num1, char num2)
{
  if (num1 == 0)
    return (num2 == 0 ? trainingResult[0] : trainingResult[1]);
  else
    return (num2 == 0 ? trainingResult[2] : trainingResult[3]);
}