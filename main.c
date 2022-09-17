#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include <string.h>
// #define MAX_ITERATION 300000
#define ITERATION_STEPS 1000
#define LOOKUP_SIZE 4096

void init();
void getInput();
void dlIterate(int maxIteration, int iterationSteps);
void generateAns(char* string);
void getOutput(char *string);
void checkAns();
void calError();
void dlTrain();
void convertToBinary(char n);
void displaybits(char n);
void calloc2dArray(double ** array, int row, int col);
double *sampleOutput; 
double  **sampleInput;
char *string;

int main()
{

  init();
  dlTrain(300000);
  getInput();
  // dlIterate(300000, 1000);
  
  
 
  // getOutput();
  // generateAns();

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
  sampleOutput = calloc(4,sizeof(double));
  sampleInput = calloc(4,sizeof(double*)); 

  calloc2dArray(sampleInput, 4,2);
 
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
  free(string);
}
void generateAns(char* string)
{
  int result = 0;
  for (int i = 0; i < (strlen(string))*8 ; i++)
  {
    // printf("%d", string[i]);
    result  ^= string[i];
  }
  // result ^= string[strlen(string)-1];

  printf("\nchecksum: %d\n",result);
}
void getOutput(char *string){
  char *outputBits;
  outputBits = calloc(strlen(string), sizeof(char));
  for (int i = 0; string[i] != 0; i++)
  {
    for (int j = 7; j >= 0; j--){
      outputBits[i * 8 + j] = ((string[i] & (1 << j)) >> j); // gets each bit of character
    }
    // printf("\n");
  }
  for (int i = 0; i < strlen(string) * 8; i++)
  {
    printf("%d", outputBits[i]);
    if (i % 8 == 7)
      printf("\n");
  }

  generateAns(outputBits);
}
void dlTrain(int iteration)
{
  genann *ann = genann_init(2, 1, 2, 1);

   /* Train on the four labeled data points many times. */
  for (int i = 0; i < iteration; ++i)
  {
    genann_train(ann, sampleInput[0], sampleOutput + 0, 3);
    genann_train(ann, sampleInput[1], sampleOutput + 1, 3);
    genann_train(ann, sampleInput[2], sampleOutput + 2, 3);
    genann_train(ann, sampleInput[3], sampleOutput + 3, 3);
  }

  /* Run the network and see what it predicts. */
  double *result;
  result = (double *)malloc(4);
  printf("Training Result: ");
  for (int i = 0; i < 4; i++)
  {
    result[i] = round(*genann_run(ann, sampleInput[i]));
    printf("%1.f ", result[i]);
  }
  printf("\n");
  genann_free(ann);
}
void dlIterate(int maxIteration, int iterationSteps){
  for ( int i = 1; i < maxIteration; i += iterationSteps){
    dlTrain(i);
  }
}
void calloc2dArray(double **array, int row, int col ){
  // array = calloc(row, sizeof(double*)); 
  for (int i=0; i<row; i++){
  sampleInput[i] = calloc(col, sizeof(*(array[i])));
  }

}