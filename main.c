#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "consts.h"
#include "graphic/graphic.h"
#include "user/user.h"
#include "table/table.h"
#include "move/move.h"

int main()
{
  printf("%s\n", LOGO);
  getch();
  ShowLogin();

  char menus[10][100] = {"New Game", "Continue Game", "Log", "Exit"}, menu;

  menu = DrawMenu(menus, 4);

  if (menu == 4)
    printf("%d", menu);
  if (menu == 1)
  {
    printf("%d", 1);
    strcpy(menus[0], "Single Player");
    strcpy(menus[1], "Multi Player");
    menu = DrawMenu(menus, 2);
    if (menu == 1)
    {
      addBead(4);
      board();
      move();
    }
    else
    {
      strcpy(menus[0], "Play On Localhost");
      strcpy(menus[1], "Play Over The Internet");
      menu = DrawMenu(menus, 2);
    }
  }
}
