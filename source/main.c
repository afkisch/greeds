#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "greed_file.h"
#include "greed_struct.h"
#include "greed_display.h"
#include "greed_game.h"


int main(){

    int i, j;               //Laufvariablen
    char name[30] = {""};   //Name des Spielers
    int pos[2] = {23, 11};  //Position des Symbols
    int vorz [8][2] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}}; //Verschiebung der Koordinaten
    int countSelected = 0;  //Elemente von Array 'selected'
    int deleted = 0;        //Geloeschte Zahlen
	int direct = 0;         //Verbleibende Richtungen
	time_t tBegin;          //Zeit am Anfang
	time_t tEnd;            //Zeit am Ende
	int endOfGame = 0;      //Logikvariable; 1-Spiel ist zu Ende

    srand((unsigned int)time(NULL));      //Seed fuer rand() einstellen
	tBegin = time(NULL);

    strarray arr;           //Struktur von Arrays
    COORD c;
    c.X = pos[0];
    c.Y = pos[1];

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Einstellungen der Kommandozeile
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes;                             //Aktueller Zustand der Konsole (schwarzer Hintergrund, weisse Charakter)
    saved_attributes = consoleInfo.wAttributes;

    while(1){

        endOfGame = 0;

        system("cls"); //Loeschen der Kommandozeile
        printFrame(c); //Der Rahme von '#' und das Logo zeichnen
        printLogo(c);

        switch(menu(c, saved_attributes)){      //Menue-Optionen
            case 0:                             //Erste Moeglichkeit
                fillArray(&arr);                //'row' mit Zufallszahlen auffuellen
                system("cls");
                break;
            case 1:
                openArray(&arr, pos);           //'row' mit den gespeicherten Zahlen auffuellen
                system("cls");
                break;
            case 2:
                result(c, saved_attributes);    //Rangliste zeigen
                endOfGame = 1;
                break;
        }

        if(!endOfGame){                         //Das Spiel ist nicht zu Ende
            printSmallFrame(c);                 //Kleine Rahme zeichnen
            cursorPosition(21, 13, c);          //Neue Cursorposition einstellen
            printf("Gib deinen Namen ein!");    //Name einlesen
            cursorPosition(21, 15, c);
            scanf("%s", name);
            system("cls");
            cursorPosition(0, 0, c);

            for(i=0; i<=SIZE_Y; i++){           //Zahlen herausschreiben
                for(j=0; j<=SIZE_X; j++){
                    print(arr.row[i][j]);
                }
                printf("\n");
            }

            while(!endOfGame){                  //Falls das Spiel nicht zu Ende ist
                for(i=0; i<=SIZE_Y; i++){       //Wird jede Zahl getestet
                    for(j=0; j<=SIZE_X; j++){
                        if(testSelected(&arr, i, j, countSelected)||!arr.row[i][j]){ //Diejenige Zahlen werden uebergeschrieben, die anders aussehen, als vorher
                            cursorPosition(j, i, c);                                 //Jede Zahl hat jetzt schwarzen Hintergrund, die Nulls erscheinen nicht
                            print(arr.row[i][j]);
                            consoleBlack;
                    }
                }
                printf("\n");
            }

            cursorPosition(pos[0], pos[1], c);

            for(i=0; i<8; i++){
                arr.around[i][0] = arr.row[pos[1]-vorz[i][1]][pos[0]-vorz[i][0]];   //Der Wert der Nachbarn von '@'. Die Laenge der Schritte
                arr.around[i][1] = pos[0]-vorz[i][0]*arr.around[i][0];              //Position von '@' am Ende der Schritte
                arr.around[i][2] = pos[1]-vorz[i][1]*arr.around[i][0];
            }

            countSelected = 0;
            direct = 0;

            endPosition(&arr, &countSelected, &vorz[0][0]);         //Die Zahlen werden ausgewaehlt, die weissen Hintergurnd haben muessen

            for(i=0; i<8; i++){                                     //'endPosition' hat diese Werte veraendert, diese werden zurueckgestellt
                arr.around[i][1] = pos[0] + vorz[i][0];
                arr.around[i][2] = pos[1] + vorz[i][1];
            }

            for(i=0; i<=SIZE_Y; i++){
                for(j=0; j<=SIZE_X; j++){
                    if(testSelected(&arr, i, j, countSelected-1)){  //Die passenden Zahlen werden weiss gefaerbt
                        cursorPosition(j, i, c);
                        consoleWhite;
                        if(testAround(&arr, i, j)) {                //Falls ein Nachbar von '@' gefunden wird
                            direct ++;                              //Gibt es um 1 mehrere moegliche Richtungen
                        }
                        printf("%d", arr.row[i][j]);
                        consoleBlack;
                    }
                }
                printf("\n");
            }

            cursorPosition(pos[0], pos[1], c);      //'@' und die Anzahl der geloeschten Felder wird gezeigt
            consoleWhite;
            printf("@");
            cursorPosition(pos[0], 0, c);
            consoleBlack;
            cursorPosition(0, SIZE_Y+2, c);
            consoleBlack;
            printf("%d Punkte", deleted);

            if(!direct){                           //Falls es keine verbleibende Richtungen gibt
                tEnd = time(NULL)-tBegin;
                _getch();
                printResult(tEnd, deleted, c);    //Das Ergebnis wird gezeigt
                addResult(name, deleted, tEnd);   //und gespeichert
                endOfGame = 1;
                _getch();
            }

            if(!endOfGame){                      //Wenn das Spiel weitergeht

                for(i=0; i<8; i++){
                    arr.around[i][1] = pos[0]-vorz[i][0]*arr.around[i][0];  //Position von '@' nach dem Schritt erneut eingestellt
                    arr.around[i][2] = pos[1]-vorz[i][1]*arr.around[i][0];
                    }
                keyPressed(&arr, pos, &deleted, &vorz[0][0], &endOfGame);   //Drueckt man eine Taste, wird ein Schritt gemacht, oder mit dem Spiel aufgehoert
                }
            }
        }
    }

    return 0;
}
