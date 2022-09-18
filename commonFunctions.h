#pragma once
#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

void init();
char* getInput();
void generateAns(char* string);
void getOutput(char *string);
void dlTrain(int iteration);
void calloc2dArray(double **array, int row, int col);
void getTrainAns(char *string);
bool dlXor(char num1, char num2);
int selectMode();
void dlQuadraticLoss(int iteration,int lossReportSteps);



#endif //COMMONFUNCTIONS_H