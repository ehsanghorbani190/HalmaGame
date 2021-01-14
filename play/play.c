#include <stdio.h>
#include <conio.h>
#include <math.h>
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
int winnerChecker_type1()
{
    // check the station player 1 for other players
    int winner1 = 0, winner2 = 0, winner3 = 0, winner4 = 0;
    for (int i = 0; i < beadType; i++)
        for (int j = beadType - 1 - i; j >= 0; j--)
            if (boardBead[i][j] == 2)
                winner2++;  
    for (int i = 1, j = beadType - 1; i<beadType, j> 0; i++, j--)
        if (boardBead[i][j] == 2)
            winner2++;
    if ((beadType == 4 && winner2 == 13) || (beadType == 5 && winner2 == 19))
        return 2;
    
    // check the station player 2 for other players
    winner1 = 0;
    for (int i = boardSize - beadType; i < boardSize; i++)
        for (int j = boardSize - 1; j > boardSize - beadType - 1; j--)
            if (boardBead[i][j] == 1)
                winner1++;
    for (int i = boardSize - 2, j = boardSize - beadType; i >= boardSize - beadType, j <= boardSize - 2; i--, j++)
        if (boardBead[i][j] == 1)
            winner1++;
    if ((beadType == 4 && winner1 == 13) || (beadType == 5 && winner1 == 19))
        return 1;

    if (playerCount == 4)
    {
        // check the station player 3 for other players
        winner4 = 0;
        int k = 0;
        for (int i = boardSize - beadType; i < boardSize; i++) {
            for (int j = 0; j <= k; j++)
                if (boardBead[i][j] == 4)
                    winner4++;
            k++;
        }
        for (int i = boardSize - 2, j = beadType - 1; i >= boardSize - beadType, j > 0; i--, j--)
            if (boardBead[i][j] == 4)
                winner4++;
        if ((beadType == 4 && winner4 == 13) || (beadType == 5 && winner4 == 19))
            return 4;
        // check the station player 4 for other players
        winner3 = 0;
        for (int i = beadType - 1; i >= 0; i--)
            for (int j = boardSize - 1; j > boardSize - beadType - 1; j--)
                if (j - i > boardSize - beadType - 1)
                    if (boardBead[i][j] == 3)
                        winner3++;
        for (int i = 1, j = boardSize - beadType; i < beadType - 1, j < boardSize - 1; i++, j++)
            if (boardBead[i][j] == 3)
                winner3++;
        if ((beadType == 4 && winner3 == 13) || (beadType == 5 && winner3 == 19))
            return 3;
    }
    return 0;
}
int winnerChecker_type2(){ // check the stations for leave camp value
// check the station 1 || ? there should free of player one : player 2 won
    int counter1 = 0;
    for (int i = 0; i < beadType; i++)
        for (int j = beadType - 1 - i; j >= 0; j--)
            if (boardBead[i][j] == 1)
                counter1++;  
    for (int i = 1, j = beadType - 1; i<beadType, j> 0; i++, j--)
        if (boardBead[i][j] == 1)
            counter1++;
    if (counter1!=0)
        return 2;
// check the station 2 || ? there should free of player 2 : player 1 won
    int counter2 = 0;
     for (int i = boardSize - beadType; i < boardSize; i++)
        for (int j = boardSize - 1; j > boardSize - beadType - 1; j--)
            if (boardBead[i][j] == 2)
                counter2++;
    for (int i = boardSize - 2, j = boardSize - beadType; i >= boardSize - beadType, j <= boardSize - 2; i--, j++)
        if (boardBead[i][j] == 2)
            counter2++;
    if (counter2!=0)
        return 1;
// check the station 3 || ? there should free of player 3 : player 4 won
    int counter3 = 0,k=0;
    for (int i = boardSize - beadType; i < boardSize; i++) {
            for (int j = 0; j <= k; j++)
                if (boardBead[i][j] == 3)
                    counter3++;
            k++;
        }
        for (int i = boardSize - 2, j = beadType - 1; i >= boardSize - beadType, j > 0; i--, j--)
            if (boardBead[i][j] == 3)
                counter3++;
    if (counter3!=0)
        return 4;
// check the station 4 || ? there should free of player 4 : player 3 won
        int counter4 = 0;
        for (int i = beadType - 1; i >= 0; i--)
            for (int j = boardSize - 1; j > boardSize - beadType - 1; j--)
                if (j - i > boardSize - beadType - 1)
                    if (boardBead[i][j] == 4)
                        counter4++;
        for (int i = 1, j = boardSize - beadType; i < beadType - 1, j < boardSize - 1; i++, j++)
            if (boardBead[i][j] == 4)
                counter4++;
    if (counter4!=0)
        return 3;

    return 0;    
}
int CheckJump( int x1, int y1, int x2, int y2)
{
    int signX = x2 - x1 , signY = y2 - y1 , i, j , x = -1, y;
    if ((signX % 2) || (signY % 2))
        return 0;

    if (signX > 0)
        signX = 1;
    else if (signX < 0)
        signX = -1;
    if (signY > 0)
        signY = 1;
    else if (signY < 0)
        signY = -1;

    for (i = x1, j = y1; j != y2 || i != x2; i += signX, j += signY)
        if (boardBead[j][i])
            {
               if(x != -1){
                   return 0;
               }
               x = i , y = j;
            }
    
    if ( x == (abs(x2 + x1) / 2) && y == (abs(y2 + y1) / 2))
        return 1;
    else
        return 0;
}
int CheckJumpType(int x1, int y1, int x2, int y2)
{
    if (abs(x2 - x1) > 2 || abs(y2 - y1) > 2)
        return 1;
    else
        return 0;
}
int CanContinue(int x , int y){
    
    for (int i = y-2;  i <= y+2; i += 4)
    {
        for (int j = x-2 ;  j <= x+2; j+=2)
        {
            if(CheckJump(x , y , j , i) && j >= 0 && j < boardSize &&i >= 0 && i < boardSize) return 1;
        }
    }
    return ((CheckJump(x , y , x-2 , y)&& x-2 >= 0) ||(CheckJump(x , y , x+2 , y) && x+ 2 < boardSize)) ? 1 : 0;

return 0;
}
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
            gotoxy(0,50);
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
            gotoxy(0,50);
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
            Role = (Role < 4) ? Role + 1 : 1;
            continue;}
        tx = j, ty = i;
        boardBead[i - 1][j - 1] = movingBead;
        gotoxy(7 + (tx - 1) * 4, 3 + (ty - 1) * 2);
        printf("\b%c", 254);
        gotoxy(0, 50);
        SetColor(15);
        moveCount[swTurn - 1]++;
        printf("Player %d Moved %d Times Up To Now!\n", swTurn, moveCount[swTurn - 1]);
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
            if(continues){
                ch = '\0';
                Log("You may move again , For finishing your turn please press F button");
                continue;
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
        Role = (Role < playerCount) ? Role + 1 : 1;
        ch = (ch == 27) ? ch : '\0';
    }
}