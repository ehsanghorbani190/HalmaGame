#include <stdio.h>
#include <string.h>

struct User
{
    int id;
    char userName[50];
    unsigned long password;
};

long int numOfUsers(FILE *input)
{
    long int size;
    fseek(input, 0, SEEK_END); // seek to end of file
    size = ftell(input)/sizeof(struct User);       // get current file pointer
    fseek(input, 0, SEEK_SET);
    
    return size;
}

int checkUnique(char *username)
{
    FILE *infile;
    struct User input;

    // Open User.dat for reading
    infile = fopen("User.dat", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    // read file contents till end of file
    while (fread(&input, sizeof(struct User), 1, infile))
        if (!strcmp(input.userName, username))
        {
            fclose(infile);
            return 1;
        }
    // close file
    fclose(infile);
    return  0;
}
struct User save(struct User record)
{
    FILE *outfile;
    if(checkUnique(record.userName)){
        record.id=-1;
        return record;
    }
    // open file for writing
    outfile = fopen("User.dat", "a+b");
    long int NOM=numOfUsers(outfile);
    record.id=NOM+1;
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
    }
    
    // write struct to file
    fwrite(&record, sizeof(struct User), 1, outfile);

    if (fwrite != 0)
        printf("\ndata was saved !\n");
    else
        printf("\nerror while saving !\n");

    // close file
    fclose(outfile);

    return record;
}


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

struct User login(char *username, unsigned long password)
{
    FILE *infile;
    struct User input;

    // Open User.dat for reading
    infile = fopen("User.dat", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    // read file contents till end of file
    while (fread(&input, sizeof(struct User), 1, infile))
        if (!strcmp(input.userName, username) && input.password == password)
        {
            fclose(infile);
            return input;
        }
    input.id=-1;
    // close file
    fclose(infile);
    return  input;
}
unsigned long GetPassword()
{
    int input = 0, i = 0;
    char temp[50] = "";
    while (input != 13)
    {
        input = getch();
        if (input != 13)
        {
            temp[i] = input;
            i++;

            if (input == 8)
            {
                i--;
                printf("\b");
            }
            else
                printf("X");
        }
    };

    return hash(temp);
}
struct User ShowLogin()
{

    char input;
    unsigned int pointer = 0, isLogin = 0;
    char menus[2][100] = {"login", "register"};
    struct User user;
    int i = 4;
    pointer = DrawMenu(menus, 2);
    if (pointer == 2)
    {
        
        do{
        printf("Plz enter your user name:");
        scanf("%s", &user.userName);
        printf("Plz enter your password:");

        user.password = GetPassword();

        user =save(user);
        if (user.id==-1)
                printf("\nYour username is used by another user :D [%d tries remaining]\n", i);
            i--;
            if (i == -1)
                exit(0);
        } while ( user.id==-1 && i >= 0);
    }
    else
    {
        char username[50];
        unsigned long password;
        
        do
        {
            printf("Plz enter your user name:");
            scanf("%s", &username);
            printf("Plz enter your password:");
            password = GetPassword();
            user =login(username, password);
            if (user.id==-1)
                printf("\nInvalid username or password! Please retry :D [%d tries remaining]\n", i);
            i--;
            if (i == -1)
                exit(0);
        } while ( user.id==-1 && i >= 0);
    }
    return user;
}