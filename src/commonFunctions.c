#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "genann.h"
#include "commonFunctions.h"
// displays bits of string (8 bits for a byte to store)
// #define SHOW_BITS
// shows raw result of each training period
// #define ANN_SHOW_EACH_RESULT
#define ANN_INPUT_NUM 2
#define ANN_HIDDEN_LAYERS 1
#define ANN_NEURONS_PER_LAYER 2
#define ANN_OUTPUT_NUM 1
#define ANN_LEARNING_RATE 3
#define LOOKUP_SIZE 4096
#define BYTE_SIZE 8
#define MAX_CHAR_LEN 100
#define ZERO_ASCII 48
#define TRAIN_SETS 4
double *sampleOutput;
double **sampleInput;
double *trainingResult;
char *outputBits;
// initialize neural network and variables.
void init()
{
	double *lookup;
	lookup = (double *)calloc(LOOKUP_SIZE, sizeof(double)); // allocates memory for NN engine.
	/* This will make the neural network initialize differently each run. */
	/* If you don't get a good result, try again for a different result. */
	srand(time(0));

	/* Input and expected out data for the XOR function. */

	sampleOutput = (double *)calloc(TRAIN_SETS, sizeof(double));
	sampleInput = (double **)calloc(TRAIN_SETS, sizeof(double *));

	calloc2dArray(sampleInput, TRAIN_SETS, ANN_INPUT_NUM);

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
// mode selection and turn input string to number.
int selectMode()
{
	char mode;
	printf("Welcome to this program. Please choose the mode you want to execute this program.\n");
	printf("Enter 1 to show quadratic loss of the training process.\n");
	printf("Enter 2 to enter custom string and show the XOR checksum based on NN learning output.\n>>");
	scanf("%c", &mode);
	return (mode - ZERO_ASCII);
}
// gets string input on custom entered string mode (mode 2).
char *getInput()
{
	printf("Please enter a string. This Program will output the XOR checksum of this string.\n>>");
	char *string;
	string = (char *)malloc(MAX_CHAR_LEN);
	scanf("%s", string);
	return (string);
}
// show quadratic loss report of NN for given iteration and interval of report.
void nnQuadraticLoss(int iteration, int lossReportSteps)
{
	/* New network with ANN_INPUT_NUM inputs, ANN_HIDDEN_LAYERS hidden layer of
	 ANN_NEURONS_PER_LAYER neurons,  and ANN_OUTPUT_NUM output. */
	genann *ann = genann_init(ANN_INPUT_NUM, ANN_HIDDEN_LAYERS, ANN_NEURONS_PER_LAYER, ANN_OUTPUT_NUM);
	double quadraticLoss = 0;
	printf("Quadratic loss:\n (Iteration, Loss)\n");
	/* Train on the four labeled data points many times. */
	for (int i = 0; i < iteration; ++i)
	{
		quadraticLoss = 0;
		for (int j = 0; j < TRAIN_SETS; j++)
			genann_train(ann, sampleInput[j], sampleOutput + j, ANN_LEARNING_RATE);
		// calculates quadratic loss on a specific interval given.
		if (i % lossReportSteps == 0)
		{
			for (int j = 0; j < TRAIN_SETS; j++)
			{
				quadraticLoss += pow((*genann_run(ann, sampleInput[j]) - *(sampleOutput + j)), 2);
			}
			quadraticLoss /= TRAIN_SETS;
			printf("%d,\t%f\n", i, quadraticLoss);
			for (int j = 0; j < TRAIN_SETS; j++)
			{
// shows raw result of each training period
#ifdef ANN_SHOW_EACH_RESULT
				printf("%f\n", *genann_run(ann, sampleInput[j]));
#endif // ANN_SHOW_EACH_RESULT
			}
		}
	}
	genann_free(ann);
}
// Trains xor output based on given iteration.
void nnTrain(int iteration)
{
	genann *ann = genann_init(ANN_INPUT_NUM, ANN_HIDDEN_LAYERS, ANN_NEURONS_PER_LAYER, ANN_OUTPUT_NUM);

	/* Train on the four labeled data points many times. */

	for (int i = 0; i < iteration; ++i)
	{
		for (int j = 0; j < TRAIN_SETS; j++)
			genann_train(ann, sampleInput[j], sampleOutput + j, ANN_LEARNING_RATE);
	}

	/* Run the network and see what it predicts. */
	trainingResult = (double *)calloc(TRAIN_SETS, sizeof(double)); // stores the final training result
	printf("Training Result: ");
	for (int i = 0; i < TRAIN_SETS; i++)
	{
		trainingResult[i] = round(*genann_run(ann, sampleInput[i]));
		printf("%1.f ", trainingResult[i]);
	}
	printf("\n");
	printf("If the result is not \"0 1 1 0 \", please consider increase the iteration count or try rerun this program.\n");
	genann_free(ann);
}
// Parse the string into the bit-by-bit string and calculates both correct and dl-learned results.
void getBitString(char *string)
{
	outputBits = calloc(strlen(string) * BYTE_SIZE, sizeof(char));
	for (int i = 0; string[i] != 0; i++)
	{
		for (int j = 0; j < BYTE_SIZE; j++)
		{
			outputBits[i * BYTE_SIZE + j] = ((string[i] & (1 << j)) >> j); // gets each bit of character
		}
	}
// displays bits of string (8 bits for a byte to store)
#ifdef SHOW_BITS
	for (int i = 0; i < strlen(string) * BYTE_SIZE; i++)
	{
		printf("%d", outputBits[i]);
		if (i % 8 == 7)
			printf("\n");
	}

#endif // SHOW_BITS
	getRealAns(outputBits);
	getTrainAns(outputBits);
	free(outputBits);
}
// Using logic xor operator to calculate the correct result for reference.
void getRealAns(char *string)
{
	int result = 0;
	for (int i = 0; i < (strlen(string)) * BYTE_SIZE; i++)
	{
		result ^= string[i];
	}

	printf("\nChecksum by XOR operator: %d\n", result);
}
// get xor checksum based on xor function learned by neural network.
void getTrainAns(char *string)
{
	bool xorChecksum = 0;
	for (int i = 0; i < (strlen(string)) * BYTE_SIZE; i++)
	{
		xorChecksum = nnXor(xorChecksum, string[i]);
	}
	printf("Checksum generated by neural network: %d\n", xorChecksum);
}
// use calloc to generate 2d array for given **pointer and numbers of row and column.
void calloc2dArray(double **array, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		sampleInput[i] = (double *)calloc(col, sizeof(*(array[i])));
	}
}
// get the xor result based on learned result.
bool nnXor(char num1, char num2)
{
	if (num1 == 0)
		return (num2 == 0 ? trainingResult[0] : trainingResult[1]);
	else
		return (num2 == 0 ? trainingResult[2] : trainingResult[3]);
}
