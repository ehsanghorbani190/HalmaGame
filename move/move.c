#include <stdio.h>
#include <conio.h>
int move(){
    int i = 1 , j = 1,temp=boardBead[i-1][j-1];
    char ch;
    boardBead[i-1][j-1] = -1;
    while(ch != 13){
        printf("\nMove your position on Table");
        board();
        ch = getch();
        boardBead[i-1][j-1] = temp;
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
        temp=boardBead[i-1][j-1];
        boardBead[i-1][j-1]= -1;
    }
    printf("You have Moved :D");
}