#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "greed_struct.h"
#include "greed_display.h"

void printFrame(COORD c){       //Rahmen von '#'

    int i, j;

    cursorPosition(0, 0, c);

    for(i=0; i<82; i++){
        printf("#");
    }
    printf("\n");

    for(i=0; i<23; i++){
        printf("#");
        for(j=0; j<80; j++){
        printf(" ");
        }
        printf("#\n");
    }

    for(i=0; i<82; i++){
        printf("#");
    }

}

void printRank(results* person, int n, COORD c, WORD saved_attributes){     //Rangliste

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int i;

    consoleBlack;
    printFrame(c);
    cursorPosition(25, 3, c);

    if(n>8) n = 8;                          //Hoechstens 8 Ergebnisse

    printf("Die besten %d Ergebnisse", n);
    cursorPosition(10, 6, c);
    printf("Name\t\t\tPunkte\t\t\tZeit");

    for(i=0; i<n; i++){
        cursorPosition(10, 8+2*i, c);
        printf("%s", person[i].name);
        cursorPosition(33, 8+2*i, c);
        printf("%d", person[i].points);
        cursorPosition(56, 8+2*i, c);
        printTime(person[i].time);
    }
}

int menu(COORD c, WORD saved_attributes){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int option = 0;
    int state = 0;  //Aktuell ausgewaehlte Menue-Option

    while(1){

        switch(abs(option%3)){

        case 0:
            cursorPosition(30, 11, c);
            consoleWhite;
            printf("Neues Spiel anfangen");
            cursorPosition(28, 14, c);
            consoleBlack;
            printf("Leztes Spiel fortsetzen");
            cursorPosition(35, 17, c);
            printf("Rangliste");
            state = 0;
            break;

        case 1:
            cursorPosition(30, 11, c);
            consoleBlack;
            printf("Neues Spiel anfangen");
            cursorPosition(28, 14, c);
            consoleWhite;
            printf("Leztes Spiel fortsetzen");
            cursorPosition(35,17, c);
            consoleBlack;
            printf("Rangliste");
            state = 1;
            break;

        case 2:
            cursorPosition(30, 11, c);
            consoleBlack;
            printf("Neues Spiel anfangen");
            cursorPosition(28, 14, c);
            printf("Leztes Spiel fortsetzen");
            cursorPosition(35, 17, c);
            consoleWhite;
            printf("Rangliste");
            state = 2;
            break;
        }

        switch (getch()){       //Wechseln zwischen den Menue-Optionen
            case 72:
                option ++;
                break;
            case 80:
                option --;
                break;
            case 13:
                return state;
                break;
            }

        }
}

void cursorPosition(int x, int y, COORD c){     //Einstellug der Cursor-Position

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



void printLogo(COORD c){        //Logo zeichnen

    cursorPosition(16, 2, c);
    printf("  _ __   _ __   ___    ___        _   ___  ");
    cursorPosition(16, 3, c);
    printf(" / _  | |  __/ / _ \\  / _ \\    __| | / __| ");
    cursorPosition(16, 4, c);
    printf("| (_| | | |   |  __/ |  __/   / _  | \\__ \\ ");
    cursorPosition(16, 5, c);
    printf(" \\__, | |_|    \\___/  \\___ / | (_| | |___/ ");
    cursorPosition(16, 6, c);
    printf(" |___/                        \\__,_|       ");
}

void printSmallFrame(COORD c){      //Kleiner Rahmen aus '#'

    int i, j;

    printLogo(c);
    cursorPosition(18, 10, c);

    for(i=0; i<37; i++){
        printf("#");
    }

    for(i=0; i<8; i++){
        cursorPosition(18, 11+i, c);
        printf("#");
        for(j=0; j<35; j++){
            printf(" ");
        }
        printf("#");
    }
    cursorPosition(18, 10+i, c);

    for(i=0; i<37; i++){
        printf("#");
    }
}

void print(int n){      //Faerbige Zahlen des Spielbretts darstellen

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

switch (n){

    case 0:
        printf(" ");
        break;
    case 1:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%d", n);
        break;
    case 2:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
        printf("%d", n);
        break;
    case 3:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("%d", n);
        break;
    case 4:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        printf("%d", n);
        break;
    case 5:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("%d", n);
        break;
    case 6:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("%d", n);
        break;
    case 7:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("%d", n);
        break;
    case 8:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("%d", n);
        break;
    case 9:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("%d", n);
        break;
    }
}

void printTime(time_t tEnd){    //Spielzeit

    if(tEnd<60){                //Sekunden
        printf("%ld", (long int)tEnd);
    }else if(tEnd>=60 && tEnd<3600){    //Minuten und Sekunden
        printf("%ld:%ld", (long int)tEnd/60, (long int)tEnd%60);
    }else printf("Das hat zu lange geaduert :(");   //Stunden :)
}

void printResult(time_t tEnd, int deleted, COORD c){    //Ergebnis am Ende des Spiels

    system("cls");
    printSmallFrame(c);
    cursorPosition(22, 13, c);
    printf("Du hast %d Zahlen geloescht", deleted);
    cursorPosition(28, 15, c);
    printf("(");
    printTime(tEnd);
    printf(" Sekunden)");
}
