#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "greed_file.h"
#include "greed_struct.h"
#include "greed_display.h"

void fillArray(strarray* arr){      //Array 'row' mit Zufallszahlen auffuellen

    int i, j;

    for(i=0; i<=SIZE_Y; i++){
        for(j=0; j<=SIZE_X; j++){
            arr->row[i][j] = (rand() % (9 - 1 + 1)) + 1;
        }
    }
}

int testSelected(strarray* arr, int y, int x, int element){     //Testen, ob Array 'selected' (x;y) enthaelt

    int i;

    for(i=0; i<element; i++){
        if(arr->selected[i][0]==x && arr->selected[i][1]==y) return 1;
    }

    return 0;
}

int testAround(strarray* arr, int y, int x){        //Testen, ob '@' einen Nachbarn mit den Koordinaten (x;y) hat

    int i;

    for(i=0; i<8; i++){
        if(arr->around[i][1]==x && arr->around[i][2]==y) return 1;
    }

    return 0;
}

int isNull(strarray* arr, int n, const int* vorz){      //Testen, ob in Richtung Nr. 'n' es genuegende zusammenhaengende Zahlen gibt.
                                                        //Also es gibt inzwischen keine leere Felder
    int i;
    int x = arr->around[n][1];
    int y = arr->around[n][2];

    for(i=0; i<arr->around[n][0]; i++){
        if(arr->row[y][x] == 0) {
            return 1;
        }
        x += vorz[2*n+0];
        y += vorz[2*n+1];
    }
    return 0;
}

void nextStep(strarray* arr, int* pos, int n, int* deleted, int* vorz){ //Ein Schritt wird gemacht

    int i;

    if(arr->row[pos[1]-vorz[2*n+1]][pos[0]-vorz[2*n+0]]){   //Zahlen der gewaehlten Richtung werden geloescht
        for(i=0; i<arr->around[n][0]; i++){
            arr->row[pos[1]][pos[0]] = 0;
            pos[0] -= vorz[2*n+0];
            pos[1] -= vorz[2*n+1];
            *deleted += 1;                                 //Anzahl der geloeschten Felder
            }

        pos[0] = arr->around[n][1];                        //Neue Position
        pos[1] = arr->around[n][2];
    }
}

void fillSelected(strarray* arr, int* countSelected, int n, int* vorz){     //Array 'selected' wird mit den Koordinaten der erreichbaren Zahlen aufgefuellt

    int i;

    for(i=0; i<=arr->around[n][0]; i++){
        arr->selected[*countSelected][0] = arr->around[n][1];
        arr->selected[*countSelected][1] = arr->around[n][2];
        arr->around[n][1] += vorz[2*n+0];
        arr->around[n][2] += vorz[2*n+1];
        *countSelected += 1;
    }

    arr->around[n][1] -= vorz[2*n+0];
    arr->around[n][2] -= vorz[2*n+1];
}

void keyPressed(strarray* arr, int* pos, int* deleted, int* vorz, int* endOfGame){        //Falls eine Taste gedrueckt wird, wird ein Schritt gemacht

    switch (getch()){

        case 49:                                                                            //Zifferntaste 1
            if(arr->around[5][1]>=0 && arr->around[5][2]<=SIZE_Y && !isNull(arr, 5, vorz)){ //Der Schritt ist innerhalb des Spielbretts
                nextStep(arr, pos, 5, deleted, vorz);
            }
            break;

        case 50:                                                                            //Zifferntaste 2
            if(arr->around[4][2]<=SIZE_Y && !isNull(arr, 4, vorz)){
                nextStep(arr, pos, 4, deleted, vorz);
            }
            break;

        case 51:                                                                            //Zifferntaste 3
            if(arr->around[3][1]<=SIZE_X && arr->around[3][2]<=SIZE_Y && !isNull(arr, 3, vorz)){
                nextStep(arr, pos, 3, deleted, vorz);
            }
            break;

        case 52:                                                                            //usw.
            if(arr->around[6][1]>=0 && !isNull(arr, 6, vorz)){
                nextStep(arr, pos, 6, deleted, vorz);
            }
            break;

        case 54:
            if(arr->around[2][1]<=SIZE_X && !isNull(arr, 2, vorz)){
                nextStep(arr, pos, 2, deleted, vorz);
                }
                break;

        case 55:
            if(arr->around[7][1]>=0 && arr->around[7][2]>=0 && !isNull(arr, 7, vorz)){
                nextStep(arr, pos, 7, deleted, vorz);
                }
                break;

        case 56:
            if(arr->around[0][2]>=0 && !isNull(arr, 0, vorz)){
                nextStep(arr, pos, 0, deleted, vorz);
                }
                break;

        case 57:
            if(arr->around[1][1]<=SIZE_X && arr->around[1][2]>=0 && !isNull(arr, 1, vorz)){
                nextStep(arr, pos, 1, deleted, vorz);
                }
                break;

        case 113:               //Taste q
            *endOfGame = 1;     //Das Spiel ist zu Ende
            break;

        case 115:
            saveGame(arr, pos);     //Der aktuelle Zustand des Spiels speichern
            *endOfGame = 1;         //Das Spiel ist zu Ende
            break;
        }
}

void endPosition(strarray* arr, int* countSelected, int* vorz){     //Testen, ob ein Schritt in jeder Richtung gueltig waere
    if(arr->around[0][2]>=0 && !isNull(arr, 0, vorz)){
        fillSelected(arr, countSelected, 0, vorz);                  //Falls ja, werden die Koordinaten zum Array 'selected' addiert
    }

    if(arr->around[1][1]<=SIZE_X && arr->around[1][2]>=0 && !isNull(arr, 1, vorz)){
        fillSelected(arr, countSelected, 1, vorz);
    }

    if(arr->around[2][1]<=SIZE_X && !isNull(arr, 2, vorz)){
        fillSelected(arr, countSelected, 2, vorz);
    }

    if(arr->around[3][1]<=SIZE_X && arr->around[3][2]<=SIZE_Y && !isNull(arr, 3, vorz)){
        fillSelected(arr, countSelected, 3, vorz);
    }

    if(arr->around[4][2]<=SIZE_Y && !isNull(arr, 4, vorz)){
        fillSelected(arr, countSelected, 4, vorz);
    }

    if(arr->around[5][1]>=0 && arr->around[5][2]<=SIZE_Y && !isNull(arr, 5, vorz)){
        fillSelected(arr, countSelected, 5, vorz);
    }

    if(arr->around[6][1]>=0 && !isNull(arr, 6, vorz)){
        fillSelected(arr, countSelected, 6, vorz);
    }

    if(arr->around[7][1]>=0 && arr->around[7][2]>=0 && !isNull(arr, 7, vorz)){
        fillSelected(arr, countSelected, 7, vorz);
    }
}
