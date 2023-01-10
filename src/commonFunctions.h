#pragma once
#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H
// initialize neural network and variables.
void init();
// mode selection and turn input string to number.
int selectMode();
// gets string input on custom entered string mode (mode 2).
char *getInput();
// show quadratic loss report of NN for given iteration and interval of report.
void nnQuadraticLoss(int iteration, int lossReportSteps);
// Trains xor output based on given iteration.
void nnTrain(int iteration);
// Parse the string into the bit-by-bit string and calculates both correct and dl-learned results.
void getBitString(char *string);
// Using logic xor operator to calculate the correct result for reference.
void getRealAns(char *string);
// get xor checksum based on xor function learned by neural network.
void getTrainAns(char *string);

// use calloc to generate 2d array for given **pointer and numbers of row and column.
void calloc2dArray(double **array, int row, int col);

// get the xor result based on learned result.
bool nnXor(char num1, char num2);

#endif // COMMONFUNCTIONS_H