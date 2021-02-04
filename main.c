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

int getColor(char ch){
  switch(ch){
    case 'g':
      return 2;
      break;
    case 'y':
      return 14;
      break;
    case 'b':
      return 1;
      break;
    case 'r':
      return 4;
      break;      
  }
}
void searchConsts()
{
  FILE *constsFile;
  constsFile = fopen("config.txt","r");
  if(!constsFile) {printf("Couldn't read setting from file , using default configuration"); return;}
  char tmp1[20],tmp2[20];
  int tmp3;
  fscanf(constsFile,"%s" , tmp1);
  do{   // find beadtype
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Size")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          boardSize = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"Size")!=0);
  rewind(constsFile);
  do {// find playerCount
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Player_Num")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          playerCount = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"Player_Num")!=0);
  rewind(constsFile);
  do{ // find leavecamp value
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"leave_camp_value")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fscanf(constsFile,"%d",&tmp3);
          leaveCampValue = tmp3;
      }else
          fscanf(constsFile,"\n");
  } while (strcmp(tmp1,"leave_camp_value")!=0);
  rewind(constsFile);
  do{ // find beadtype
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"Beads_order")==0){ 
          fscanf(constsFile,"%s",tmp2);
          fgets(tmp2,20,constsFile);
          int l2 = strlen(tmp2);
          beadType = tmp2[l2-2] - '0';
          beadType++;
      }else
          fscanf(constsFile,"\n");
   } while (strcmp(tmp1,"Beads_order")!=0);
   rewind(constsFile);
   do{ // find Colors
    fscanf(constsFile,"%s",tmp1);
      if(strcmp(tmp1,"First_Color")==0){ 
          fscanf(constsFile," = %s",tmp2);
          FPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Second_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          SPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Third_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          TPC = getColor(tmp2[0]);
      }
      else if(strcmp(tmp1,"Forth_Color")==0){
          fscanf(constsFile," = %s",tmp2);
          FoPC = getColor(tmp2[0]);
      }
      else
          fscanf(constsFile,"\n");
  } while (!feof(constsFile));
  fclose(constsFile);
}
int main()
{
  searchConsts();
  boardBead = (int **)malloc(boardSize * sizeof(int **));
  for (int i = 0; i < boardSize; i++) boardBead[i] = (int*)malloc(boardSize * sizeof(int*));
  // addBeadA(playerCount);
  // struct Node *fnode = (struct Node *)malloc(sizeof(struct Node));
  // fnode->value = 0;
  // fnode->position.x = 19;
  // fnode->position.y = 19;
  // fnode->left = NULL;
  // fnode->right = NULL;
  // addNodeForBead(fnode,0);
 
  // structure(fnode, 0);
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
