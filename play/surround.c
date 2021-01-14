int isSurrounded(int x, int y){
    for (int i = y-1; i <= y+1; i++)
    {
        for (int j = x-1; j <= x+1; j++)
        {
            if(j>= 0 && j < boardSize && i>= 0 && i < boardSize 
            &&
            (boardBead[i][j] ==0 || (i != y && j != x && boardBead[i][j] == boardBead[y][x]))) return 0;
        }        
    }
    for (int i = y-2;  i <= y+2; i += 2)
    {
        for (int j = x-2; j <= x+2; j += 2)
        {
            if(j>= 0 && j < boardSize && i>= 0 && i < boardSize 
            &&
            boardBead[i][j] ==0 ) return 0;
        
        }
        
    }
    
    return 1;
}
int didSurround(int x, int y){
  for (int i = y-2; i <= y+2; i++)
    {
        for (int j = x-2; j <= x+2; j++)
        {
            if(j>= 0 && j < boardSize && i>= 0 && i < boardSize && boardBead[i][j]!=0 && boardBead[i][j] != boardBead[y][x] && isSurrounded(j , i)) return 1;
        }        
    }
    return 0;  
}