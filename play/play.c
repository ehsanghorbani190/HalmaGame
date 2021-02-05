#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "winner.c"
#include "jump.c"
#include "utilities.c"
#include "surround.c"
#include "moveValidation.c"
#include <time.h>


int posibleCase(int x, int y)
{
    int numOfCases = 0;
    for (int _y = 0; _y < boardSize; _y++)
    {
        for (int _x = 0; _x < boardSize; _x++)
        {
            if (isValidMove(x, y, _x, _y))
                numOfCases++;
        }
    }
    return numOfCases;
}

void playWithAI()
{
    int y = 0, x = 0, temp = boardBead[y][x],
        Aty = 0, Atx = 0, Afy = 0, Afx = 0, //these are used for AI movment
        fx, fy, tx, ty;                     //these are used for movment over the array
    int BeadReplace = 0;
    int numOfCases = 0;
    int random = 0;
     int BeadNumber = (beadType*(beadType+1)/2)+beadType-1 ;
    //int BeadNumber = 2;
    int continues = 0; // with this we will know that player is doing multiple jumps or not
    char ch, tch;      //this vars are for getting keyboard movment and printing the cell's beads
    int moveCount[playerCount];
    for(int h = 0; h < playerCount; h++) moveCount[h] = 0;
    // this vars are for LeaveCampValue type
    /*This Vars are for repeating sequence*/
    int lm[playerCount][2]; //save previous moves
    for(int h = 0; h < playerCount; h++) lm[h][0] = 0 , lm[h][1] =0;
    int lmt[2];                     //save this move
    int RepeatCount = 0, RepeatSwitch = 0, drawOffer = 0;
    /*End of var list*/
    //we want to stop the game if we press esc button
    srand(time(NULL));
    while (ch != 27)
    {
        if (Role == 1)
        {
            while (ch != 13 && ch != 27 && !continues)
            {

                fx = x, fy = y;
                SetColor(15);
                tch = (boardBead[y][x] == Role) ? 240 : 42;
                gotoxy(7 + x * 4, 3 + y * 2);
                printf("\b%c", tch);
                ch = getch();
                keySwitch(&ch, &y, &x);
                //Change color for redrawing beads
                ColorSwitch(temp);
                //redraw the cell we left
                gotoxy(7 + fx * 4, 3 + fy * 2);
                printf("\b%c", (temp) ? 254 : 32);
                temp = boardBead[y][x];
                if (ch == 13 && boardBead[y][x] != Role)
                {
                    ch = '\0';
                    SetColor(12);
                    if (boardBead[y][x])
                        Log("Please Select one of your beads , not others! ;D");
                    else
                        Log("You Cannot move an empty cell :D");
                    continue;
                } // if the playe doesnt select his beads , nothing will happen
            }
            //Remove the bead from the cell it left
            gotoxy(7 + x * 4, 3 + y * 2);
            printf("\b%c", ' ');
            fx = x, fy = y;
            lmt[0] = (fx * 1000) + fy;
            int movingBead = boardBead[y][x];
            boardBead[y][x] = 0;
            ch = (ch == 27) ? ch : '\0';
            while (ch != 13 && ch != 27)
            {
                //We want to move the bead and it's color :D
                ColorSwitch(movingBead);
                tx = x, ty = y;
                int xdistance = fx - tx, ydistance = fy - ty;
                tch = (boardBead[y][x] == 0 && ((abs(xdistance) <= 1 && abs(ydistance) <= 1 && !continues) || CheckJump(fx, fy, tx, ty) || (continues && !ydistance && !xdistance)))
                          ? 254
                          : 42;
                if (tch == 42)
                    SetColor(15);
                gotoxy(7 + x * 4, 3 + y * 2);
                printf("\b%c", tch);
                ch = getch();
                keySwitch(&ch, &y, &x);
                //redraw the cell we left
                ColorSwitch(temp);
                gotoxy(7 + tx * 4, 3 + ty * 2);
                printf("\b%c", (temp) ? 254 : 32);
                temp = boardBead[y][x];
                if (ch == 13)
                {
                    if (boardBead[y][x])
                    {
                        SetColor(12);
                        ch = '\0';
                        Log("Please move your bead in an empty cell! ;D");
                        continue;
                    } //if the player select an unempty cell , he shall select again :D
                    else if ((abs(xdistance) > 1 || abs(ydistance) > 1) && !CheckJump(fx, fy, x, y))
                    {
                        SetColor(12);
                        ch = '\0';
                        Log("You can only go one cell far away ;)");
                        continue;
                    }
                    else if (!xdistance && !ydistance)
                    {
                        ch = '\0';
                        BeadReplace = 1;
                        break;
                    }
                    else if (CheckJump(fx, fy, tx, ty) && !CheckJumpType(fx, fy, tx, ty))
                    {
                        if (CanContinue(tx, ty))
                            continues = 1;
                        else
                            continues = 0;
                        ch = '\0';
                        break;
                    }
                }
                else if (ch == 'f')
                {
                    continues = 0;
                    break;
                }
            }
            if (BeadReplace)
            {
                SetColor(12);
                Log("You Replaced your selected bead , you may now select another");
                boardBead[fy][fx] = Role;
                BeadReplace = 0;
                continue;
            }
            if (ch == 'f')
            {
                boardBead[fy][fx] = movingBead, continues = 0, Role = (Role < playerCount) ? Role + 1 : 1;
                ColorSwitch(boardBead[fy][fx]);
                gotoxy(7 + fx * 4, 3 + fy * 2);
                printf("\b%c", 254);
                continue;
            }
            tx = x, ty = y, boardBead[y][x] = movingBead;
            gotoxy(7 + tx * 4, 3 + ty * 2);
            printf("\b%c", 254);
            if (didSurround(tx, ty))
            {
                gotoxy(0, 5 + (boardSize - 1) * 2);
                printf("Player %d Won! Because he surrounded the opponent bead ! Press anything to exit :D", Role);
                getch();
                exit(0);
            }
            gotoxy(0, 5 + (boardSize - 1) * 2);
            SetColor(15);
            moveCount[Role - 1]++;
            printf("Player %d Moved %d Times Up To Now!", Role, moveCount[Role - 1]);
            for (int w = 1; w <= 50; w++)
                printf(" ");
            int sumMove = 0;
            for (int w = 0; w < playerCount; w++)
                sumMove += moveCount[w];
            if (sumMove >= leaveCampValue)
            {
                if (winnerChecker_type1() == 1 || winnerChecker_type2() == 1)
                    Log("Player 1 Won :]");
                else if (winnerChecker_type1() == 2 || winnerChecker_type2() == 2)
                    Log("Player 2 Won :]");
                else if (playerCount == 4 && winnerChecker_type1() == 3 || winnerChecker_type2() == 3)
                    Log("Player 3 Won :]");
                else if (playerCount == 4 && winnerChecker_type1() == 4 || winnerChecker_type2() == 4)
                    Log("Player 4 Won :]");
            }
            lmt[1] = (tx * 1000) + ty;
            if (lm[Role - 1][0] == 0)
                RepeatSwitch = 0;
            else if (lm[Role - 1][0] == lmt[1] && lm[Role - 1][1] == lmt[0])
                RepeatCount += 1, RepeatSwitch = 0;
            else
                RepeatCount = 0, RepeatSwitch = 0;
            lm[Role - 1][0] = lmt[0], lm[Role - 1][1] = lmt[1];
            RepeatSwitch = (RepeatCount == playerCount) ? 1 : 0;
            if (continues)
            {
                ch = '\0';
                Log("You may move again , For finishing your turn please press F button");
                continue;
            }
            Role = (Role < playerCount) ? Role + 1 : 1;
            ch = (ch == 27) ? ch : '\0';
        }
        else
        {
            do
            {
                numOfCases = 0;
                random = rand() % BeadNumber+1;
                for (Afy = 0; Afy < boardSize && numOfCases != random; Afy++)
                {
                    for (Afx = 0; Afx < boardSize && numOfCases != random; Afx++)
                    {
                        if (boardBead[Afy][Afx] == Role)
                            numOfCases++;
                    }
                }

                numOfCases = posibleCase(Afx-1,Afy-1);

            } while (!numOfCases);
            random = rand() % numOfCases+1;
            numOfCases=0;
            for (Aty = 0; Aty < boardSize && numOfCases < random; Aty++)
            {
                for (Atx = 0; Atx < boardSize && numOfCases < random; Atx++)
                {
                    if (isValidMove(Afx-1, Afy-1, Atx, Aty))
                        numOfCases++;
                }
            }
            char buff[100];
            boardBead[Afy - 1][Afx - 1] = 0;
            gotoxy(7 + (Afx - 1) * 4, 3 + (Afy - 1) * 2);
            printf("\b%c", ' ');
            boardBead[Aty - 1][Atx - 1] = Role;
            ColorSwitch(Role);
            gotoxy(7 + (Atx - 1) * 4, 3 + (Aty - 1) * 2);
            printf("\b%c", 254);
            Role = (Role < playerCount) ? Role + 1 : 1;
            numOfCases = 0;
        }
    }
}

void play()
{
    int y = 0, x = 0, temp = boardBead[y][x],
        fx, fy, tx, ty; //these are used for movment over the array
    int BeadReplace = 0;
    int continues = 0; // with this we will know that player is doing multiple jumps or not
    char ch, tch;      //this vars are for getting keyboard movment and printing the cell's beads
    int moveCount[playerCount];
    for(int h = 0; h < playerCount; h++) moveCount[h] = 0;
    // this vars are for LeaveCampValue type
    /*This Vars are for repeating sequence*/
    int lm[playerCount][2]; 
    for(int h = 0; h < playerCount; h++) lm[h][0] = 0 , lm[h][1] =0; //save previous moves
    int lmt[2];                     //save this move
    int RepeatCount = 0, RepeatSwitch = 0, drawOffer = 0;
    /*End of var list*/
    //we want to stop the game if we press esc button
    while (ch != 27)
    {
        //getting the bead the player wants to move
        if (RepeatSwitch)
        {
            RepeatSwitch = 0;
            gotoxy(0, 5 + (boardSize - 1) * 2);
            printf("Dear Player %d The board is in a repeating sequence ! Do you want to offer Draw to your opponent ?(Y:yes / Anything else : No)", Role);
            char ans = getch();
            if (ans == 'y' || ans == 'Y')
            {
                drawOffer = 1;
                Role = (Role < playerCount) ? Role + 1 : 1;
                continue;
            }
            else
                drawOffer = 0;
        }
        if (drawOffer)
        {
            drawOffer = 0;
            gotoxy(0, 5 + (boardSize - 1) * 2);
            printf("Dear Player %d Your opponent is offering draw to you , due to board state is repeating. Do You Accept ?(Y:yes / Anything else : No)", Role);
            char ans = getch();
            if (ans == 'y' || ans == 'Y')
            {
                if (playerCount == 2)
                {
                    Log("The Game is A DRAW :D , Thanks for playing , press any button to exit :D");
                    getch();
                    exit(0);
                }
            }
            else
            {
                Role = (Role < playerCount) ? Role + 1 : 1;
                for (int k = 0; k < 100; k++)
                    printf("\b");
                printf("Dear Player %d , Your opponent declined your offer :D", Role);
                continue;
            }
        }
        while (ch != 13 && ch != 27 && !continues)
        {
            fx = x, fy = y;
            SetColor(15);
            tch = (boardBead[y][x] == Role) ? 240 : 42;
            gotoxy(7 + x * 4, 3 + y * 2);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &y, &x);
            //Change color for redrawing beads
            ColorSwitch(temp);
            //redraw the cell we left
            gotoxy(7 + fx * 4, 3 + fy * 2);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[y][x];
            if (ch == 13 && boardBead[y][x] != Role)
            {
                ch = '\0';
                SetColor(12);
                if (boardBead[y][x])
                    Log("Please Select one of your beads , not others! ;D");
                else
                    Log("You Cannot move an empty cell :D");
                continue;
            } // if the playe doesnt select his beads , nothing will happen
        }
        //Remove the bead from the cell it left
        gotoxy(7 + x * 4, 3 + y * 2);
        printf("\b%c", ' ');
        fx = x, fy = y;
        lmt[0] = (fx * 1000) + fy; 
        int movingBead = boardBead[y][x];
        boardBead[y][x] = 0;
        ch = (ch == 27) ? ch : '\0';
        while (ch != 13 && ch != 27)
        {
            //We want to move the bead and it's color :D
            ColorSwitch(movingBead);
            tx = x, ty = y;
            int xdistance = fx - tx, ydistance = fy - ty;
            tch = (boardBead[y][x] == 0 && ((abs(xdistance) <= 1 && abs(ydistance) <= 1 && !continues) || CheckJump(fx, fy, tx, ty) || (continues && !ydistance && !xdistance)))
                      ? 254
                      : 42;
            if (tch == 42)
                SetColor(15);
            gotoxy(7 + x * 4, 3 + y * 2);
            printf("\b%c", tch);
            ch = getch();
            keySwitch(&ch, &y, &x);
            //redraw the cell we left
            ColorSwitch(temp);
            gotoxy(7 + tx * 4, 3 + ty * 2);
            printf("\b%c", (temp) ? 254 : 32);
            temp = boardBead[y][x];
            if (ch == 13)
            {
                if (boardBead[y][x])
                {
                    SetColor(12);
                    ch = '\0';
                    Log("Please move your bead in an empty cell! ;D");
                    continue;
                } //if the player select an unempty cell , he shall select again :D
                else if ((abs(xdistance) > 1 || abs(ydistance) > 1) && !CheckJump(fx, fy, x, y))
                {
                    SetColor(12);
                    ch = '\0';
                    Log("You can only go one cell far away ;)");
                    continue;
                }
                else if (!xdistance && !ydistance)
                {
                    ch = '\0';
                    BeadReplace = 1;
                    break;
                }
                else if (CheckJump(fx, fy, tx, ty) && !CheckJumpType(fx, fy, tx, ty))
                {
                    if (CanContinue(tx, ty))
                        continues = 1;
                    else
                        continues = 0;
                    ch = '\0';
                    break;
                }
                else if(continues && (!CheckJump(fx, fy, tx, ty) ||(CheckJump(fx, fy, tx, ty) && CheckJumpType(fx, fy, tx, ty)))){
                    
                        Log("You can just have multiple normal jumps.\n");
                        ch = '\0';
                        continue;
                    
                }
            }
            else if (continues && ch == 'f' || ch == 'F')
            {
                continues = 0;
                break;
            }
        }
        if (BeadReplace)
        {
            SetColor(12);
            Log("You Replaced your selected bead , you may now select another");
            boardBead[fy][fx] = Role;
            BeadReplace = 0;
            continue;
        }
        if (ch == 'f' || ch == 'F')
        {
            boardBead[fy][fx] = movingBead, continues = 0, Role = (Role < playerCount) ? Role + 1 : 1;
            ColorSwitch(boardBead[fy][fx]);
            gotoxy(7 + fx * 4, 3 + fy * 2);
            printf("\b%c", 254);
            continue;
        }
        tx = x, ty = y, boardBead[y][x] = movingBead;
        gotoxy(7 + tx * 4, 3 + ty * 2);
        printf("\b%c", 254);
        if (didSurround(tx, ty))
        {
            gotoxy(0, 5 + (boardSize - 1) * 2);
            printf("Player %d Won! Because he surrounded the opponent bead ! Press anything to exit :D", Role);
            getch();
            exit(0);
        }
        gotoxy(0, 5 + (boardSize - 1) * 2);
        SetColor(15);
        moveCount[Role - 1]++;
        printf("Player %d Moved %d Times Up To Now!", Role, moveCount[Role - 1]);
        for (int w = 1; w <= 50; w++)
            printf(" ");
        int sumMove = 0;
        for (int w = 0; w < playerCount; w++)
            sumMove += moveCount[w];
        if (sumMove >= leaveCampValue)
        {
            if (winnerChecker_type1() == 1 || winnerChecker_type2() == 1){
                Log("Player 1 Won :] press anything to exit");
                getch();
                exit(0);
            }
            else if (winnerChecker_type1() == 2 || winnerChecker_type2() == 2){
                Log("Player 2 Won :] press anything to exit");
                getch();
                exit(0);
            }
            else if (playerCount == 4 && winnerChecker_type1() == 3 || winnerChecker_type2() == 3){
                Log("Player 3 Won :] press anything to exit");
                getch();
                exit(0);
                }
            else if (playerCount == 4 && winnerChecker_type1() == 4 || winnerChecker_type2() == 4){
                Log("Player 4 Won :] press anything to exit");
                getch();
                exit(0);
            }
        }
        lmt[1] = (tx * 1000) + ty;
        if (lm[Role - 1][0] == 0)
            RepeatSwitch = 0;
        else if (lm[Role - 1][0] == lmt[1] && lm[Role - 1][1] == lmt[0])
            RepeatCount += 1, RepeatSwitch = 0;
        else
            RepeatCount = 0, RepeatSwitch = 0;
        lm[Role - 1][0] = lmt[0], lm[Role - 1][1] = lmt[1];
        RepeatSwitch = (RepeatCount == playerCount) ? 1 : 0;
        if (continues)
        {
            ch = '\0';
            Log("You may move again , For finishing your turn please press F button");
            continue;
        }
        Role = (Role < playerCount) ? Role + 1 : 1;
        ch = (ch == 27) ? ch : '\0';
    }
}