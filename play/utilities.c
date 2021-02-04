void keySwitch(char *ch, int *y, int *x)
{
    switch (*ch)
    {
    case KEY_UP:
        *y = (*y > 0) ? *(y)-1 : boardSize-1;
        break;
    case KEY_DOWN:
        *y = (*y < boardSize-1) ? *(y) + 1 : 0;
        break;
    case KEY_LEFT:
        *x = (*x > 0) ? *(x)-1 : boardSize-1;
        break;
    case KEY_RIGHT:
        *x = (*x < boardSize-1) ? *(x) + 1 : 0;
        break;
    }
}
void ColorSwitch(int x)
{
    switch (x)
    {
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
}

