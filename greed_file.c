#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "greed_struct.h"
#include "greed_display.h"

void addResult(char* name, int deleted, time_t time){    //Ergebnis speichern
    FILE* fp;

    fp = fopen("result.txt", "a");
    fprintf(fp, "%s %d %d\n", name, deleted, (int)time);
    fclose(fp);
}

void result(COORD c, WORD saved_attributes){    //Ergebnisse oeffnen

    FILE* fp;
    results* person;
    results t;
    int i, j, n = 0;
    char a[30]={""};

    fp = fopen("result.txt", "r");

    while(!feof(fp)){                          //Zeilen zaehlen
        fgets(a, 30, fp);
        n++;
    }

    person = (results*)malloc(n*sizeof(results));   //Struktur-Array fuer die Ergebnisse
    rewind(fp);


    for(i=0; !feof(fp); i++){
        fscanf(fp, "%s%d%d", person[i].name, &person[i].points, &person[i].time);   //Name, Punkte und Spielzeit einlesen
    }


    for(i = n-1; i>0; i--){                                     //Die Ergebnisse werden sortiert
        for(j=0; j<i; j++){
            if(person[j].points<person[j+1].points){
                t = person[j];
                person[j] = person[j+1];
                person[j+1] = t;

            }
        }
    }

    fclose(fp);
    printRank(person, n, c, saved_attributes);
    free(person);
    getchar();
}

void saveGame(strarray* arr, int* pos){         //Das Spielbrett wird gespeichert

    FILE* fptr;
    int i, j;

    fptr = fopen("last.txt", "w");
    fprintf(fptr, " %d", pos[0]);
    fprintf(fptr, " %d", pos[1]);

    for(i=0; i<=SIZE_Y; i++){
        for(j=0; j<=SIZE_X; j++){
            fprintf(fptr, " %d", arr->row[i][j]);
        }
    }
    fclose(fptr);
}

void openArray(strarray* arr, int* pos){      //Das Spielbrett wird eingelesen

    FILE* fptr;
    int i, j;

    fptr = fopen("last.txt", "r");
    fscanf(fptr, "%d", &pos[0]);
    fscanf(fptr, "%d", &pos[1]);
    for(i=0; i<=SIZE_Y; i++){
        for(j=0; j<=SIZE_X; j++){
            fscanf(fptr, "%d", &arr->row[i][j]);
        }
    }
    fclose(fptr);
}
