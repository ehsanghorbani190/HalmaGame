#include <stdio.h>
#include <math.h>
int isValidMove(int fx , int fy , int tx , int ty){
    return (
        !boardBead[ty][tx] 
        && boardBead[fy][fx] == Role
        && (fx - tx) && (fy - ty) &&
        ((abs(tx-fx) <= 1 && abs(ty-fy) <= 1)
        || (abs(tx-fx) > 1 || abs(ty-fy) > 1 && CheckJump(fx, fy , tx, ty)))
    ) ? 1 : 0 ;
}