#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "winner.c"
#include "jump.c"
#include "utilities.c"
#include "surround.c"
void play()
{
    int i = 1, j = 1, temp = boardBead[i - 1][j - 1], x, y, fx, fy, tx, ty, BeadReplace = 0 , continues = 0;
    char ch, tch;
    int moveCount[playerCount] = {0}, swTurn = 1;
    int lm[playerCount][2]={{0}};
    int lmt[2];
    int RepeatCount = 0 , RepeatSwitch = 0 , drawOffer = 0;
    //we want to stop the game if we press esc button
    while (ch != 27)
    {
        //getting the bead the player wants to move
        if(RepeatSwitch) {
            RepeatSwitch = 0;
            gotoxy(0,5+(boardSize-1)*2);
            printf("Dear Player %d The board is in a repeating sequence ! Do you want to offer Draw to your opponent ?(Y:yes / Anything else : No)", Role);
            char ans =getch();
            if(ans== 'y' || ans =='Y') {
                drawOffer= 1;
                Role = (Role < playerCount) ? Role + 1 : 1;
                continue;
            }
            else{
                drawOffer =0 ;
            }
        }
        if(drawOffer){
            drawOffer = 0;
            gotoxy(0,5+(boardSize-1)*2);
            printf("Dear Player %d Your opponent is offering draw to you , due to board state is repeating. Do You Accept ?(Y:yes / Anything else : No)" , Role);
            char ans =getch();
            if(ans == 'y' || ans =='Y'){
                if(playerCount == 2){
                    Log("The Game is A DRAW :D , Thanks for playing , press any button to exit :D");
                    getch();
                    exit(0);
                }
            }
            else {
                Role = (Role < playerCount) ? Role + 1 : 1;
                for(int k = 0 ; k <100; k++) printf("\b");
                printf("Dear Player %d , Your opponent declined your offer :D" , Role);
                continue;
                }
        }
        while (ch != 13 && ch != 27 && !continues)
        {
            x = j - 1, y = i - 1;
            SetColor(15);
            tch = (boardBead[i - 1][j - 1] == Role) ? 240 : 42;
            gotoxy(7 + (j - 1) * 4, 3 + (i - 1) * 2);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &i, &j);
            //Change color for redrawing beads
            ColorSwitch(temp);
            //redraw the cell we left
            gotoxy(7 + x * 4, 3 + y * 2);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[i - 1][j - 1];
        }
        if (ch == 13 && boardBead[i - 1][j - 1] != Role)
        {
            ch = '\0';
            SetColor(12);
            if (boardBead[i - 1][j - 1])
                Log("Please Select one of your beads , not others! ;D");
            else
                Log("You Cannot move an empty cell :D");
            continue;
        } // if the playe doesnt select his beads , nothing will happen
        //Remove the bead from the cell it left
        gotoxy(7 + (j - 1) * 4, 3 + (i - 1) * 2);
        printf("\b%c", ' ');
        fx = j, fy = i;
        lmt[0] = (fx*1000) + fy;
        int movingBead = boardBead[i - 1][j - 1];
        boardBead[i - 1][j - 1] = 0;
        ch = (ch == 27) ? ch : '\0';
        while (ch != 13 && ch != 27)
        {
            //We want to move the bead and it's color :D
            ColorSwitch(movingBead);
            x = j - 1, y = i - 1;
            int xdistance = fx - x - 1, ydistance = fy - y - 1;
            tch = (boardBead[i - 1][j - 1] == 0
            && ((xdistance >= -1 && ydistance >= -1 && xdistance <= 1 && ydistance <= 1 && !continues)
            ||  CheckJump(fx-1 , fy -1 , x , y)
            || (continues && !ydistance && !xdistance)))
            ? 254 : 42;
            if (tch == 42)
                SetColor(15);
            gotoxy(7 + (j - 1) * 4, 3 + (i - 1) * 2);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &i, &j);
            //redraw the cell we left
            ColorSwitch(temp);
            gotoxy(7 + x * 4, 3 + y * 2);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[i - 1][j - 1];
            if (ch == 13 && boardBead[i - 1][j - 1])
            {
                SetColor(12);
                ch = '\0';
                Log("Please move your bead in an empty cell! ;D");
                continue;
            } //if the player select an unempty cell , he shall select again :D
            if ((ch == 13) && (xdistance > 1 || xdistance < -1 || ydistance > 1 || ydistance < -1) && !CheckJump(fx-1 , fy -1 , x , y))
            {
                SetColor(12);
                ch = '\0';
                Log("You can only go one cell far away ;)");
                continue;
            }
            if (ch == 13 && !xdistance && !ydistance)
            {
                ch = '\0';
                BeadReplace = 1;
                break;
            }
            if(ch == 13 && CheckJump(fx-1 , fy -1 , x , y) && !CheckJumpType(fx-1 , fy -1 , x , y)){
                if(CanContinue(x , y)) continues = 1;
                else continues = 0;
                ch = '\0';
                break;
            }
            if(ch == 'f') { continues = 0; break;}
        }
        if (BeadReplace)
        {
            SetColor(12);
            Log("You Replaced your selected bead , you may now select another");
            boardBead[fy - 1][fx - 1] = Role;
            BeadReplace = 0;
            continue;
        }
        if(ch == 'f') { 
            boardBead[fy - 1][fx - 1] = movingBead;
            ColorSwitch(boardBead[fy - 1][fx - 1]);
            gotoxy(7 + (fx - 1) * 4, 3 + (fy - 1) * 2);
            printf("\b%c", 254);
            continues = 0;
            Role = (Role < playerCount) ? Role + 1 : 1;
            continue;}
        tx = j, ty = i;
        boardBead[i - 1][j - 1] = movingBead;
        gotoxy(7 + (tx - 1) * 4, 3 + (ty - 1) * 2);
        printf("\b%c", 254);
        if(didSurround(tx-1, ty-1)){
            gotoxy(0,5+(boardSize-1)*2);
            printf("Player %d Won! Because he surrounded the opponent bead ! Press anything to exit :D", Role);
            getch();
            exit(0);
        }
        gotoxy(0,5+(boardSize-1)*2);
        SetColor(15);
        moveCount[swTurn - 1]++;
        printf("Player %d Moved %d Times Up To Now!", swTurn, moveCount[swTurn - 1]);
        for (int w = 1; w <= 50; w++)
            printf(" ");
        if (swTurn < playerCount)
            swTurn++;
        else
            swTurn = 1;
        int sumMove = 0;
        for (int w = 0; w < playerCount;w++) sumMove += moveCount[w]; 
        if(sumMove>=leaveCampValue){
            if (winnerChecker_type1() == 1)
                printf("Player 1 Won :]");
            else if (winnerChecker_type1() == 2)
                printf("Player 2 Won :]");
            else if (winnerChecker_type1() == 3)
                printf("Player 3 Won :]");
            else if (winnerChecker_type1() == 4)
                printf("Player 4 Won :]");
            else if (winnerChecker_type1() == 0);
        }
        if(sumMove >= leaveCampValue){
            if (winnerChecker_type2() == 1)
                printf("Player 1 Won :]");
            else if (winnerChecker_type2() == 2)
                printf("Player 2 Won :]");
            else if (winnerChecker_type2() == 3)
                printf("Player 3 Won :]");
            else if (winnerChecker_type2() == 4)
                printf("Player 4 Won :]");
            else if (winnerChecker_type2() == 0);
        }
        lmt[1] = (tx*1000) + ty;
        if(lm[Role-1][0] == 0) RepeatSwitch = 0;
        else if(lm[Role-1][0] == lmt[1] && lm[Role-1][1] == lmt[0]) {
            RepeatCount++;
            RepeatSwitch = 0;
            }
        else {RepeatCount = 0; RepeatSwitch = 0;}
            lm[Role-1][0] = lmt[0];
            lm[Role-1][1] = lmt[1];
        if(RepeatCount == playerCount) RepeatSwitch = 1;
        else RepeatSwitch=0;
        if(continues){
                ch = '\0';
                Log("You may move again , For finishing your turn please press F button");
                continue;
            }
        Role = (Role < playerCount) ? Role + 1 : 1;
        ch = (ch == 27) ? ch : '\0';
    }
}