#include <stdio.h>

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