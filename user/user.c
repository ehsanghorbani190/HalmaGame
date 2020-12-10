#include <stdio.h>
#include <string.h>

struct User
{
    char userName[50];
    unsigned long password;
};

void save(struct User record)
{
    FILE *outfile;

    // open file for writing
    outfile = fopen ("User.dat", "w+");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
    }

    // write struct to file
    fwrite (&record, sizeof(struct User), 1, outfile);

    if(fwrite != 0)
        printf("\ndata was saved !\n");
    else
        printf("\nerror while saving !\n");

    // close file
    fclose (outfile);
}


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int login(char *username, unsigned long password)
{
    FILE *infile;
    struct User input;

    // Open User.dat for reading
    infile = fopen ("User.dat", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&input, sizeof(struct User), 1, infile))
        if( !strcmp(input.userName,username) && input.password==password)
        {
            fclose (infile);
            return 1;
        }
    // close file
    fclose (infile);
    return 0;
}
unsigned long GetPassword()
{
    int input=0,i=0;
    char temp[50]="";
    while(input!=13)
    {
        input =getch();
        if(input!=13)
        {
            temp[i]=input;
            i++;

            if(input==8)
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