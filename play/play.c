#include <stdio.h>
#include <conio.h>
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
int winnerChecker_type1(){
// check the station player 1 for other players 
    int winner1=0,winner2=0,winner3=0,winner4=0;
        for (int i = 0; i < beadType; i++) 
        for (int j = beadType - 1 - i; j >= 0; j--)
            if(boardBead[i][j] == 2) winner2++;
            else if(boardBead[i][j] == 3) winner3++;    
            else if(boardBead[i][j] == 4) winner4++;   
        for (int i = 1, j = beadType - 1; i < beadType, j > 0; i++, j--)
            if(boardBead[i][j] == 2) winner2++;
            else if(boardBead[i][j] == 3) winner3++;    
            else if(boardBead[i][j] == 4) winner4++; 
        if((beadType==4&&winner2==13)||(beadType==5&&winner2==19)) return 2;
        if((beadType==4&&winner3==13)||(beadType==5&&winner3==19)) return 3;
        if((beadType==4&&winner4==13)||(beadType==5&&winner4==19)) return 4;
// check the station player 2 for other players 
    winner1=0;winner3=0;winner4=0;
        for (int i = boardSize - beadType ; i < boardSize ; i++) 
        for (int j = boardSize - 1 ; j > boardSize - beadType - 1; j--)
            if(boardBead[i][j] == 1) winner1++;
            else if(boardBead[i][j] == 3) winner3++;    
            else if(boardBead[i][j] == 4) winner4++;   
        for (int i = boardSize-2, j = boardSize-beadType; i >= boardSize-beadType, j <= boardSize-2; i--, j++)
            if(boardBead[i][j] == 1) winner1++;
            else if(boardBead[i][j] == 3) winner3++;    
            else if(boardBead[i][j] == 4) winner4++; 
        if((beadType==4&&winner1==13)||(beadType==5&&winner1==19)) return 1;
        if((beadType==4&&winner3==13)||(beadType==5&&winner3==19)) return 3;
        if((beadType==4&&winner4==13)||(beadType==5&&winner4==19)) return 4;
if(playerCount==4){
// check the station player 3 for other players
    winner1=0;winner2=0;winner4=0;
        int k = 0;
        for (int i = boardSize - beadType; i < boardSize ; i++){
            for (int j = 0; j <= k; j++)
                if(boardBead[i][j] == 1) winner1++;
                else if(boardBead[i][j] == 2) winner2++;    
                else if(boardBead[i][j] == 4) winner4++;   
            k++;    
        }
        for (int i = boardSize - 2, j = beadType-1; i >= boardSize - beadType, j > 0; i--, j--) 
            if(boardBead[i][j] == 1) winner1++;
            else if(boardBead[i][j] == 2) winner2++;    
            else if(boardBead[i][j] == 4) winner4++;   
        if((beadType==4&&winner1==13)||(beadType==5&&winner1==19)) return 1;
        if((beadType==4&&winner2==13)||(beadType==5&&winner2==19)) return 2;
        if((beadType==4&&winner4==13)||(beadType==5&&winner4==19)) return 4;
// check the station player 4 for other players
    winner1=0;winner2=0;winner3=0;
        for (int i = beadType - 1; i >= 0; i--)
        for (int j = boardSize-1 ; j > boardSize-beadType-1; j--)
            if(j - i > boardSize-beadType-1)
               if(boardBead[i][j] == 1) winner1++;
               else if(boardBead[i][j] == 2) winner2++;    
               else if(boardBead[i][j] == 3) winner3++;   
        for (int i = 1, j = boardSize - beadType; i < beadType-1, j < boardSize -1; i++, j++)
               if(boardBead[i][j] == 1) winner1++;
               else if(boardBead[i][j] == 2) winner2++;    
               else if(boardBead[i][j] == 3) winner3++;
        if((beadType==4&&winner1==13)||(beadType==5&&winner1==19)) return 1;
        if((beadType==4&&winner2==13)||(beadType==5&&winner2==19)) return 2;
        if((beadType==4&&winner3==13)||(beadType==5&&winner3==19)) return 3;
} 

return 0;
}
void play()
{
    int i = 1, j = 1, temp = boardBead[i - 1][j - 1], x, y, fx, fy, tx, ty , BeadReplace = 0;
    char ch, tch;
    int moveCount[playerCount] = {0},swTurn = 1;
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
            int xdistance =fx -x -1 , ydistance =fy -y -1;
            tch = (boardBead[i - 1][j - 1] == 0 && xdistance >= -1 && ydistance >=-1 && xdistance <= 1 && ydistance <= 1) ? 254 : 42;
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
            if((ch == 13) && (xdistance >1 || xdistance < -1 || ydistance > 1 || ydistance < -1)){
                SetColor(12);
                ch = '\0';
                Log("You can only go one cell far away ;)");
                continue;
            }
            if(ch == 13 && !xdistance && !ydistance){
                ch = '\0';
               BeadReplace = 1;
               break;
            }
        }
        if(BeadReplace) {
            SetColor(12);
            Log("You Replaced your selected bead , you may now select another");
            boardBead[fy - 1][fx - 1] = Role;
            continue;}
        tx = j, ty = i;
        boardBead[i - 1][j - 1] = movingBead;
        gotoxy(9 + (tx - 1) * 6, 5 + (ty - 1) * 3);
        printf("\b%c", 254);
        gotoxy(0, 50);
        for (int w = 1; w <= 50; w++)
            printf("\b");
        SetColor(15);
        printf("Player %d Moved From %d %d to %d %d\n", Role, fy, fx, ty, tx);
        moveCount[swTurn-1]++;
        printf("!Player %d Moved %d Times Up To Now!",swTurn,moveCount[swTurn-1]);
        if(swTurn<playerCount)
           swTurn++;
        else
           swTurn=1;

        if(winnerChecker_type1()==1)
            printf("Player 1 Won :]");
        else if(winnerChecker_type1()==2)
            printf("Player 2 Won :]");
        else if(winnerChecker_type1()==3)
            printf("Player 3 Won :]");
        else if(winnerChecker_type1()==4)
            printf("Player 4 Won :]");
        else if(winnerChecker_type1()==0)

           
        Role = (Role < 4) ? Role + 1 : 1;
        ch = (ch == 27) ? ch : '\0';
    }
}