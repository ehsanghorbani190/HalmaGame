#include <stdio.h>

int addBead(int PlayerCount)
{
    // 0 >> empty house
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
          boardBead[i][j] = 0;
    // 1 >> player 1
    for (int i = 0; i < beadType; i++)
        for (int j = beadType - 1 - i; j >= 0; j--)
            boardBead[i][j] = 1;
    for (int i = 1, j = beadType - 1; i < beadType, j > 0; i++, j--)
        boardBead[i][j] = 1;
    // 2 >> player 2
    for (int i = boardSize - beadType ; i < boardSize ; i++)
        for (int j = boardSize - 1 ; j > boardSize - beadType - 1; j--)
            if(i + j  > 2 * boardSize - beadType - 2)
               boardBead[i][j] = 2;
    for (int i = boardSize -2, j = boardSize-beadType; i >= boardSize-beadType, j <= boardSize-2; i--, j++)
        boardBead[i][j] = 2;
    if(PlayerCount==4){
    // 3 >> player 3
        int k = 0;
    for (int i = boardSize - beadType; i < boardSize ; i++)
    {
        for (int j = 0; j <= k; j++)
            boardBead[i][j] = 3;
        k++;    
    }
    for (int i = boardSize - 2, j = beadType-1; i >= boardSize - beadType, j > 0; i--, j--)
        boardBead[i][j] = 3;     
    // 4 >> player 4
    for (int i = beadType - 1; i >= 0; i--)
        for (int j = boardSize-1 ; j > boardSize-beadType-1; j--)
            if(j - i > boardSize-beadType-1)
               boardBead[i][j] = 4;
    for (int i = 1, j = boardSize - beadType; i < beadType-1, j < boardSize -1; i++, j++)
        boardBead[i][j] = 4;     
    }
}
int addBeadA(int PlayerCount)
{
     for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
          boardBead[i][j] = 0;
    boardBead[0][0] = 1;  
    
    boardBead[19][19] = 2;
}
void board()
{
    system("cls");
    SetColor(12);
    printf("%s\n" , Note);
    printf("PLEASE MAKE THIS WINDOW FULLSCREEN IN ORDER TO GAME FUNTIONS CORRECTLY :D\nThen press anything to start the game ;)");
    getch();
    system("cls");
    // top numbers
    printf("   ");
    SetColor(8);  
    for (int i = 0; i < boardSize; i++){
        if (i> 8) printf(" %d %d",(i + 1 - (i+1)%10)/10 , (i+1)%10 ); 
        else printf("  %d ", i+1);
    }
    SetColor(15);  
    printf("\n    ");
    for (int j = 0; j < boardSize ; j++)
        {
            printf("___");
            if (j < boardSize -1) printf("_");
        } 
        printf("\n"); 
    // for for rows >> start the first row
    for (int i = 0; i < boardSize; i++)
    {
    // print row i part 2
            SetColor(8);  
            printf("%d",i+1);
            if(i<= 8) printf(" ");
            SetColor(15);  
        for (int j = 0; j < boardSize; j++)
        {
            char ch;
            if(boardBead[i][j] > 0) ch = 254;
            else if(boardBead[i][j] == 0) ch = 32;
            //else if(boardBead[i][j] == -1) ch = 240; 
            printf(" | ");
            switch(boardBead[i][j]){
                case 1: 
                SetColor(FPC);
                break;
                case 2:
                SetColor(SPC);
                break;
                case 3:
                SetColor(TPC);
                break;
                case 4:
                SetColor(FoPC);
                break;
            }
            printf("%c" , ch);
            SetColor(15);
            if(j == boardSize -1) printf(" |");  
        }
        printf("\n");
        
    // print row i part 3
        for (int j = 0; j < boardSize ; j++)
        {
            if(!j) printf("   |___"); 
            else printf("|___");
            if(j == boardSize - 1) printf("|");
        }
        printf("\n");           
    }
}
void SaveBoard(){
    SetColor(9);
    system("cls");
    printf("Do you want to save this game ?(Y/y: Yes , anything else: No)\n");
    char ch = getch();
    if(ch == 'y' || ch =='Y'){
    FILE * out;
    out = fopen("save.dat" , "wb");
    fwrite(boardBead , sizeof(int) , boardSize * boardSize , out);
    fwrite(&Role , sizeof(int) ,1 , out);
    fclose(out);
    SetColor(2);
    printf("Game Save Successfully! Press anything to exit:D");
    getch();
    }
    else{
        SetColor(3);
        printf("Press anything to exit:D");
        getch(); 
    }
}
void ReadBoard(){
    FILE * in;
    in = fopen("save.dat" , "rb");
    fread(boardBead , sizeof(int) , boardSize * boardSize , in);
    fread(&Role , sizeof(int) ,1 , in);
    Role--;
    fclose(in);
}

