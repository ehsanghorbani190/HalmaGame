#include <stdio.h>
#include <conio.h>
#define playerCount 4
void keySwitch(char *ch, int *i, int *j)
{
    switch (*ch)
    {
    case KEY_UP:
        *i = (*i > 1) ? *(i)-1 : boardSize;
        break;
    case KEY_DOWN:
        *i = (*i < boardSize) ? *(i) + 1 : 1;
        break;
    case KEY_LEFT:
        *j = (*j > 1) ? *(j)-1 : boardSize;
        break;
    case KEY_RIGHT:
        *j = (*j < boardSize) ? *(j) + 1 : 1;
        break;
    }
}
void ColorSwitch(int x)
{
    switch (x)
    {
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
}
void play()
{
    int i = 1, j = 1, temp = boardBead[i - 1][j - 1], x, y, fx, fy, tx, ty;
    char ch, tch;
    int moveCount[playerCount] = {0},swTurn=0;
    //we want to stop the game if we press esc button
    while (ch != 27)
    {
        //getting the bead the player wants to move
        while (ch != 13 && ch != 27)
        {
            x = j - 1, y = i - 1;
            SetColor(15);
            tch = (boardBead[i - 1][j - 1] == Role || boardBead[i - 1][j - 1] == 0) ? 240 : 42;
            gotoxy(9 + (j - 1) * 6, 5 + (i - 1) * 3);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &i, &j);
            //Change color for redrawing beads
            ColorSwitch(temp);
            //redraw the cell we left
            gotoxy(9 + x * 6, 5 + y * 3);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[i - 1][j - 1];
        }
        if(ch==13 && boardBead[i - 1][j - 1] != Role) {
            ch ='\0';
            SetColor(12);
            if(boardBead[i - 1][j - 1]) Log("Please Select one of your beads , not others! ;D");
            else Log("You Cannot move an empty cell :D");
            continue;
            } // if the playe doesnt select his beads , nothing will happen
        //Remove the bead from the cell it left
        gotoxy(9 + (j - 1) * 6, 5 + (i - 1) * 3);
        printf("\b%c", ' ');
        fx = j, fy = i;
        int movingBead = boardBead[i - 1][j - 1];
        boardBead[i - 1][j - 1] = 0;
        ch = (ch == 27) ? ch : '\0';
        while (ch != 13 && ch != 27)
        {
            //We want to move the bead and it's color :D
            ColorSwitch(movingBead);
            x = j - 1, y = i - 1;
            tch = (boardBead[i - 1][j - 1] == 0) ? 254 : 42;
            if (tch == 42)
                SetColor(15);
            gotoxy(9 + (j - 1) * 6, 5 + (i - 1) * 3);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &i, &j);
            //redraw the cell we left
            ColorSwitch(temp);
            gotoxy(9 + x * 6, 5 + y * 3);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[i - 1][j - 1];
            if(ch == 13 && boardBead[i-1][j-1]){
                SetColor(12);
                ch = '\0';
                Log("Please move your bead in an empty cell! ;D");
                continue;
                }//if the player select an unempty cell , he shall select again :D
        }
        tx = j, ty = i;
        boardBead[i - 1][j - 1] = movingBead;
        gotoxy(9 + (tx - 1) * 6, 5 + (ty - 1) * 3);
        printf("\b%c", 254);
        gotoxy(0, 50);
        for (int w = 1; w <= 50; w++)
            printf("\b");
        SetColor(15);
        printf("Player %d Moved From %d %d to %d %d", Role, fy, fx, ty, tx);
        moveCount[swTurn]++;
        swTurn = (swTurn<4) ? swTurn+1 : 0;
        Role = (Role < 4) ? Role + 1 : 1;
        ch = (ch == 27) ? ch : '\0';
    }
}