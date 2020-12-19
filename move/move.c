#include <stdio.h>
#include <conio.h>
int move(){
    int i = 1 , j = 1, temp =  boardBead[i-1][j-1] , x, y;
    char ch ,tch ;
    while(ch != 13){
        x = j-1 , y = i-1;
        SetColor(15);
        tch = (boardBead[i-1][j-1] == Role || boardBead[i-1][j-1] == 0) ? 240 : 42;
        gotoxy(9 + (j-1)*6,5 +(i-1)*3);
        printf("\b%c" , tch);
        ch = getch();
        switch(ch){
            case KEY_UP:
            if(i>1) i--;
            else i= boardSize;
            break;
            case KEY_DOWN:
            if(i<boardSize) i++;
            else i= 1;
            break;
            case KEY_LEFT:
            if(j>1) j--;
            else j= boardSize;
            break;
            case KEY_RIGHT:
            if(j<boardSize) j++;
            else j= 1;
            break;
        }
        //Change color for redrawing beads
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
            //redraw the cell we left
        gotoxy(9 + x*6,5 +y*3);
        printf("\b%c" , (temp) ? 254 : 32);
        temp =  boardBead[i-1][j-1];
    }
    printf("You have Moved :D");
}