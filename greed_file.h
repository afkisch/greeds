#ifndef GREED_FILE_H
#define GREED_FILE_H
#include <windows.h>
#include "greed_struct.h"

void addResult(char* name, int deleted, time_t time);
void result(COORD c, WORD saved_attributes);
void saveGame(strarray* arr, int* pos);
void openArray(strarray* arr, int* pos);

#endif
