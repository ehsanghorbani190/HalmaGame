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

