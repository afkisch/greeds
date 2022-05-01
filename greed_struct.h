#ifndef GREED_STRUCT_H
#define GREED_STRUCT_H
#define SIZE_X 80   //Groesse des Bretts
#define SIZE_Y 20

typedef struct results{
    char name[30]; //Name des Spielers
    int time;      //Spielzeit
    int points;    //Erreichte Punkte
} results;

typedef struct strarray{
    int around[8][3];               //Nachbarzahlen von '@'; Werte und Koordinaten
    int row[SIZE_Y+1][SIZE_X+1];    //Zahlen des Bretts
    int selected[72][2];            //Alle Schrittmöglichkeiten
}strarray;

#define consoleWhite SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY)      //Weisser Hintergrund im Console
#define consoleBlack SetConsoleTextAttribute(hConsole, saved_attributes)                                                                //Schwarzer Hintergrund im Console

#endif
