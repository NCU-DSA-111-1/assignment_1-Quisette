#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "genann.h"
#include "commonFunctions.h"
#define ANN_INPUT_NUM 2
#define ANN_HIDDEN_LAYERS 1
#define ANN_NEURONS_PER_LAYER 2
#define ANN_OUTPUT_NUM 1
#define ANN_LEARNING_RATE 0.1
#define LOOKUP_SIZE 4096
double *sampleOutput;
double **sampleInput;
double *trainingResult;
char *outputBits;
void init()
{
  double *lookup;
  lookup = (double *)calloc(LOOKUP_SIZE, sizeof(double));
  /* This will make the neural network initialize differently each run. */
  /* If you don't get a good result, try again for a different result. */
  srand(time(0));

  /* Input and expected out data for the XOR function. */

  // allocate memories for sample inputs and outputs.
  sampleOutput = (double *)calloc(4, sizeof(double));
  sampleInput = (double **)calloc(4, sizeof(double *));

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
}
char *getInput()
{
  // string = (char*)calloc(10, sizeof(char));
  printf("Please enter a string. This Program will output the XOR checksum of this string.");
  char *string;
  string = (char *)malloc(100);
  // char string ;
  scanf("%s", string);

  // string = fgets(string,sizeof(string),stdin);
  // printf("\n%s\n", string);

  // getOutput(string);
  return (string);

  // free(string);
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
  outputBits = calloc(strlen(string) * 8, sizeof(char));
  for (int i = 0; string[i] != 0; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      outputBits[i * 8 + j] = ((string[i] & (1 << j)) >> j); // gets each bit of character
    }
  }
  // displays bits of string (8 bits for a byte to store)
  for (int i = 0; i < strlen(string) * 8; i++)
  {
    printf("%d", outputBits[i]);
    if (i % 8 == 7)
      printf("\n");
  }

  generateAns(outputBits);
  getTrainAns(outputBits);
  free(outputBits);
}
void dlTrain(int iteration)
{
  genann *ann = genann_init(ANN_INPUT_NUM, ANN_HIDDEN_LAYERS, ANN_NEURONS_PER_LAYER, ANN_OUTPUT_NUM);
  double quadraticLoss;

  /* Train on the four labeled data points many times. */

  // 4 training results in total
  for (int i = 0; i < iteration; ++i)
  {
    quadraticLoss = 0;
    genann_train(ann, sampleInput[0], sampleOutput + 0, ANN_LEARNING_RATE);
    genann_train(ann, sampleInput[1], sampleOutput + 1, ANN_LEARNING_RATE);
    genann_train(ann, sampleInput[2], sampleOutput + 2, ANN_LEARNING_RATE);
    genann_train(ann, sampleInput[3], sampleOutput + 3, ANN_LEARNING_RATE);
  }

  /* Run the network and see what it predicts. */
  // 4 training results in total
  trainingResult = (double *)calloc(4, sizeof(double));
  printf("Training Result: ");
  for (int i = 0; i < 4; i++)
  {
    trainingResult[i] = round(*genann_run(ann, sampleInput[i]));
    printf("%1.f ", trainingResult[i]);
  }
  printf("\n");
  printf("If the result is not \"0 1 1 0 \", please consider increase the iteration count or try rerun this program.\n");
  genann_free(ann);
}

void calloc2dArray(double **array, int row, int col)
{
  for (int i = 0; i < row; i++)
  {
    sampleInput[i] = (double *)calloc(col, sizeof(*(array[i])));
  }
}
void getTrainAns(char *string)
{
  bool xorChecksum = 0;
  for (int i = 0; i < (strlen(string)) * 8; i++)
  {
    xorChecksum = dlXor(xorChecksum, string[i]);
  }
  printf("\nDL-Learning xor checksum: %d", xorChecksum);
}

bool dlXor(char num1, char num2)
{
  if (num1 == 0)
    return (num2 == 0 ? trainingResult[0] : trainingResult[1]);
  else
    return (num2 == 0 ? trainingResult[2] : trainingResult[3]);
}
int selectMode()
{
  char mode;
  printf("Welcome to this program. Please choose the mode you want to execute this program.\n");
  printf("Enter 1 to show quadratic loss of the training process.\n");
  printf("Enter 2 to enter custom string and show the XOR checksum based on NN learning output.\n");
  scanf("%c", &mode);
  return (mode - 48);
}
void dlQuadraticLoss(int iteration, int lossReportSteps)
{
  /* New network with 2 inputs, 1 hidden layer of 2 neurons, and 1 output. */
  genann *ann = genann_init(ANN_INPUT_NUM, ANN_HIDDEN_LAYERS, ANN_NEURONS_PER_LAYER, ANN_OUTPUT_NUM);
  double quadraticLoss;
  /* Train on the four labeled data points many times. */
  for (int i = 0; i < iteration; ++i)
  {
    quadraticLoss = 0;
    genann_train(ann, sampleInput[0], sampleOutput + 0, 3);
    genann_train(ann, sampleInput[1], sampleOutput + 1, 3);
    genann_train(ann, sampleInput[2], sampleOutput + 2, 3);
    genann_train(ann, sampleInput[3], sampleOutput + 3, 3);
    // calculates quadratic loss on a specific interval given.
    if (i % lossReportSteps == 0)
    {
      for (int j = 0; j < 4; j++)
      {
        quadraticLoss += pow((*genann_run(ann, sampleInput[j]) - *(sampleOutput + j)), 2);
      }
      printf("Quadratic loss for %d is %f\n", i, quadraticLoss);
    }
  }
  genann_free(ann);
}
