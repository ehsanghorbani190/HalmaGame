#include <stdio.h>
#include <math.h>

int CheckJump(int x1, int y1, int x2, int y2)
{
    int signX = x2 - x1, signY = y2 - y1, i, j, x = -1, y;
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
        if (boardBead[j][i] && (i != x1 || j != y1))
        {
            if (x != -1)
                return 0;

            x = i;
            y = j;
        }

    if (x == (abs(x2 + x1) / 2) && y == (abs(y2 + y1) / 2))
        return 1;

    return 0;
}
int CheckJumpType(int x1, int y1, int x2, int y2)
{
    if (abs(x2 - x1) > 2 || abs(y2 - y1) > 2)
        return 1;
    else
        return 0;
}
int CanContinue(int x, int y)
{

    for (int i = y - 2; i <= y + 2; i += 4)
    {
        for (int j = x - 2; j <= x + 2; j += 2)
        {
            if (CheckJump(x, y, j, i) && j >= 0 && j < boardSize && i >= 0 && i < boardSize)
                return 1;
        }
    }
    return ((CheckJump(x, y, x - 2, y) && x - 2 >= 0) || (CheckJump(x, y, x + 2, y) && x + 2 < boardSize)) ? 1 : 0;

    return 0;
}