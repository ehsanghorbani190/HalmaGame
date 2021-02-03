#include <stdio.h>
#include <math.h>
int isValidMove(int fx , int fy , int tx , int ty){
    int sw;
    sw= (
        !boardBead[ty][tx] 
        && boardBead[fy][fx] 
        //&& boardBead[fy][fx] == Role
        && ( (fx - tx) || (fy - ty) )
        && ((abs(tx-fx) <= 1 && abs(ty-fy) <= 1)
        || ((abs(tx-fx) > 1 || abs(ty-fy) > 1) && CheckJump(fx, fy , tx, ty)))
    ) ;
    if(sw)
    return sw;
    else{
        for(int y=fy-2;y<fy+2;y++){
            for(int x=fx-2;y<fx+2;y++){
                if(x<boardSize && y<boardSize){
                    if(CheckJump(fx,fy,x,y))
                        isValidMove(x,y,tx,ty);
                }
            }
        }
    }
    return 0;
}