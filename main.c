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
  ShowLogin();
  addBead(4);
  board();
  move();
}
