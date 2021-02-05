#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "consts.h"
#include "graphic/graphic.h"
#include "user/user.h"
#include "table/table.h"
#include "play/play.h"
#include "AI/AI.h"
#include "socket/socket.h"



int main()
{
  searchConsts();
  printf("%d",boardSize);
  boardBead = (int **)malloc(boardSize * sizeof(int *));
  for (int i = 0; i < boardSize; i++) boardBead[i] = (int*)malloc(boardSize * sizeof(int));
  SOCKET socket;
  char host[50] = "127.0.0.1";
  struct Client clients[4];
  printf("%s\n", LOGO);
  getch();
  struct User user;
  user = ShowLogin();
  char menus[10][100] = {"New Game", "Continue Game", "Log", "Exit"}, menu, connectionType;

  menu = DrawMenu(menus, 4);

  if (menu == 1)
  {
    strcpy(menus[0], "Single Player");
    strcpy(menus[1], "Two Player");
    strcpy(menus[2], "Multi Player");
    menu = DrawMenu(menus, 3);
    if (menu == 1)
    {
      addBead(playerCount);
      board();
      playWithAI();
      SaveBoard();
    }
    else if (menu == 2)
    {
      if (fopen("save.dat", "rb"))
      {
        system("cls");
        SetColor(12);
        printf("There's a saved game,\nDo You want to start a New Game?(Press Y/y)\nOr continue that one?(Press C/c)\nOr Quit?(Press anything)\n");
        char ch = getch();
        if (ch == 'y' || ch == 'Y')
        {
          addBead(playerCount);
          board();
          play();
          SaveBoard();
        }
        else if (ch == 'c' || ch == 'C')
        {
          ReadBoard();
          board();
          play();
          SaveBoard();
        }
        else
        {
          exit(0);
        }
      }
      else
      {
        addBead(playerCount);
        board();
        play();
        SaveBoard();
      }
    }
    else if (menu == 3)
    {
      strcpy(menus[0], "Play On Localhost");
      strcpy(menus[1], "Play Over The Internet");
      connectionType = DrawMenu(menus, 2);

      if (connectionType == 1)
      {

        strcpy(menus[0], "I Want To Be Server");
        strcpy(menus[1], "I Want To Be Client");
        connectionType = DrawMenu(menus, 2);
        if (connectionType == 1)
        {
          strcpy(menus[0], "Two Player");
          strcpy(menus[1], "Four Player");
          menu = DrawMenu(menus, 2);
          socket = InitServer(8888);

          for (int i = 0; i < 2 * menu - 1; i++)
          {
            clients[i] = WaitForClient(socket);
          }
          for (int i = 0; i < 2 * menu - 1; i++)
          {
            printf("Player %d is: %s \n", i + 1, clients[i].name);
          }
        }
        else
        {

          printf("plz input your host ip [do you want use default setting?(y/n)]:");
          scanf("%s", host);
          if (!strcmp(host, "y") || !strcmp(host, "Y"))
            strcpy(host, "127.0.0.1");

          socket = InititClient(host, 8888);
          Send(socket, user.userName);
        }
      }
    }
  }
  else if (menu == 2)
  {
    ReadBoard();
    board();
    play();
    SaveBoard();
  }
}
