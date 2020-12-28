#include <windows.h>
#include <direct.h>



void SetColor(int ForgC)
{

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    
}

int DrawMenu(char menu [][100], int numOfMenus){


    
    char input;
    
    unsigned int pointer=0,position,pastPosition;
     system("cls");
     
    for(int i=0;i<numOfMenus;i++){
      SetColor(i+1);
    printf("  %s\n",menu[i]);
    }
       while(input!=13)
     {
       
        pastPosition= pointer%3+1;
        gotoxy(0,position);
         printf("  ",position);
        
        if(input==KEY_UP)
            pointer--;
        if(input==KEY_DOWN)
            pointer++;
            
       position=pointer%numOfMenus+1;
          gotoxy(0,position);
          SetColor();
         printf("> ",position);
         gotoxy(0,1000);
         input = getch();
     }
     system("cls");
     input=0;
     return position;
}
