#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "consts.h"
#include "graphic/graphic.h"
#include "user/user.h"
#include "table/table.h"
#include "play/play.h"
#include "AI/AI.h"
//#include "socket/socket.h"
void resetTemp(int boardtemp[boardSize][boardSize])
{
  for (int y = 0; y < boardSize; y++)
    for (int x = 0; x < boardSize; x++)
      boardtemp[y][x] = boardBead[y][x];
}
void swap(int _x, int _y, int x, int y)
{
  boardBead[_y][_x] = 0;
  boardBead[y][x] = 2;
}
void getNeighbor(struct Node *node,int depth);

void addNodeForBead(struct Node *node,int depth)
{
  struct Node *n= (struct Node*)malloc(sizeof(struct Node));
  if (untility(node->position.x, node->position.y, 0, 2))
    return;

  for (int y = 0; y < boardSize; y++){
    for (int x = 0; x < boardSize; x++)
      if (isValidMove(node->position.x, node->position.y, x, y))
      {

        if (node->left == NULL)
          n=addChild(node, untility(x, y, 0, 2), x, y);
        else
          n=addCase(node->left, untility(x, y, 0, 2), x, y);
          getNeighbor(n,depth+1);
      }
  }
    
}

void getNeighbor(struct Node *node,int depth)
{
  if(depth>2)
  return;
  int x = node->position.x, y = node->position.y;
  do
  {
    swap(x, y, node->position.x, node->position.y);
    addNodeForBead(node,depth);
    x = node->position.x;
    y = node->position.y;

    node = node->right;

  } while (node != NULL);
  addBeadA(playerCount);
}

int main()
{
  addBeadA(playerCount);
  struct Node *fnode = (struct Node *)malloc(sizeof(struct Node));
  fnode->value = 0;
  fnode->position.x = 19;
  fnode->position.y = 19;
  fnode->left = NULL;
  fnode->right = NULL;
  addNodeForBead(fnode,0);
 
  structure(fnode, 0);

  //board();
  exit(0);
  // SOCKET socket;
  // char host[50] = "127.0.0.1";
  // struct Client clients[4];
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
      addBeadA(playerCount);
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

      // if (connectionType == 1)
      // {

      //   strcpy(menus[0], "I Want To Be Server");
      //   strcpy(menus[1], "I Want To Be Client");
      //   connectionType = DrawMenu(menus, 2);
      //   if (connectionType == 1)
      //   {
      //     strcpy(menus[0], "Two Player");
      //     strcpy(menus[1], "Four Player");
      //     menu = DrawMenu(menus, 2);
      //     socket = InitServer(8888);

      //     for (int i = 0; i < 2 * menu - 1; i++)
      //     {
      //       clients[i] = WaitForClient(socket);
      //     }
      //     for (int i = 0; i < 2 * menu - 1; i++)
      //     {
      //       printf("Player %d is: %s \n", i + 1, clients[i].name);
      //     }
      //   }
      //   else
      //   {

      //     printf("plz input your host ip [do you want use default setting?(y/n)]:");
      //     scanf("%s", host);
      //     if (!strcmp(host, "y") || !strcmp(host, "Y"))
      //       strcpy(host, "127.0.0.1");

      //     socket = InititClient(host, 8888);
      //     Send(socket, user.userName);
      //   }
      // }
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
