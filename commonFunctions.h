#pragma once
#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

void init();
// gets string input on custom entered string mode (mode 2).
char* getInput();
// Using logic xor operator to calculate the correct result for reference.
void generateAns(char* string);
// Parse the string into the bit-by-bit string and calculates both correct and dl-learned results. 
void getOutput(char *string);
// Trains xor output based on given iteration.
void dlTrain(int iteration);
// use calloc to generate 2d array for given **pointer and numbers of row and column.
void calloc2dArray(double **array, int row, int col);
// get xor checksum based on xor function learned by neural network.
void getTrainAns(char *string);
// get the xor result based on learned result.
bool dlXor(char num1, char num2);
// mode selection and turn input string to number. 
int selectMode();
// show quadratic loss report of NN for given iteration and interval of report. 
void dlQuadraticLoss(int iteration,int lossReportSteps);



#endif //COMMONFUNCTIONS_H