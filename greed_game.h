#ifndef GREED_GAME_H
#define GREED_GAME_H
#include <windows.h>

void fillArray(strarray* arr);
int testSelected(strarray* arr, int y, int x, int element);
int testAround(strarray* arr, int y, int x);
int isNull(strarray* arr, int n, int* vorz);
void nextStep(strarray* arr, int pos[2], int n, int* deleted, int* vorz);
void fillSelected(strarray* arr, int* countSelected, int n, int* vorz);
void keyPressed(strarray* arr, int pos[2], int* deleted, int* vorz, int* endOfGame);
void endPosition(strarray* arr, int* k, int* vorz);

#endif
