#include <stdio.h>
#include <conio.h>
int move(){
    int i = 1 , j = 1, temp =  boardBead[i-1][j-1] , x, y;
    char ch ;
    board();
    while(ch != 13){
        x = j-1 , y = i-1;
        SetColor(15);
        gotoxy(9 + (j-1)*6,5 +(i-1)*3);
        printf("\b%c" , 240);
        ch = getch();
        switch(ch){
            case KEY_UP:
            if(i>1) i--;
            break;
            case KEY_DOWN:
            if(i<boardSize) i++;
            break;
            case KEY_LEFT:
            if(j>1) j--;
            break;
            case KEY_RIGHT:
            if(j<boardSize) j++;
            break;
        }
        switch(temp){
                case 1: 
                SetColor(1);
                break;
                case 2:
                SetColor(4);
                break;
                case 3:
                SetColor(2);
                break;
                case 4:
                SetColor(14);
                break;
            }
        gotoxy(9 + x*6,5 +y*3);
        printf("\b%c" , (temp) ? 254 : 32);
        temp =  boardBead[i-1][j-1];
    }
    printf("You have Moved :D");
}