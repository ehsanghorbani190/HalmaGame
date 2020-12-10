#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "graphic/graphic.h"
#include "user/user.h"

// a struct to read and write
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


int main()
{

    char input;
    unsigned int pointer=0,isLogin=0;
    while(input!=13)
    {

        if(input==KEY_UP)
            pointer++;
        if(input==KEY_DOWN)
            pointer--;
        SetColor(4);
        pointer%2 ? printf("  "):printf("> ");
        printf("login\n");
        SetColor(6);
        pointer%2 ? printf("> "):printf("  ");
        printf("register\n");
        input = getch();
        system("cls");

    }

    if(pointer%2)
    {
        struct User user;

        printf("Plz enter your user name:");
        scanf("%s",&user.userName);
        printf("Plz enter your password:");

        user.password=GetPassword();

        save(user);


    }
    else
    {
        char username[50];
        unsigned long password;
        printf("Plz enter your user name:");
        scanf("%s",&username);
        printf("Plz enter your password:");
        password=GetPassword();
        isLogin=login(username,password);
        printf("\n%d",isLogin);


    }
    return 0;
}
