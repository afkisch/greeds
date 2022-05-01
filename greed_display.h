#ifndef GREED_DISPLAY_H
#define GREED_DISPLAY_H
#include <time.h>

void cursorPosition(int x, int y, COORD c);
void printFrame(COORD c);
void printRank(results* person, int n, COORD c, WORD saved_attributes);
int menu(COORD c, WORD saved_attributes);
void printLogo(COORD c);
void printSmallFrame(COORD c);
void print(int n);
void printTime(time_t tEnd);
void printResult(time_t tEnd, int deleted, COORD c);

#endif
