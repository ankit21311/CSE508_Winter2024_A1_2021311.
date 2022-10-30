
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void rm_File(char file_Name[1000])
{
    if (unlink(file_Name) != 0)
    {
        perror(file_Name);
    }
}

void rm_File_D(char file_Name[1000])
{
    if (rmdir(file_Name) != 0)
    {
        perror(file_Name);
    }
}

void rm_File_V(char file_Name[1000])
{
    if (unlink(file_Name) == 0)
    {
        printf(" File removed '%s'\n", file_Name);
    }
    else
    {
        perror(file_Name);
    }
}

int main(int argc, char *argv[])
{
    char command_Name[10] = "";
    char flag[10] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command_Name, token);
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flag, token);
        token = strtok(NULL, " ");
    }
    while (token != NULL)
    {
        char file_Name[1000] = "";
        strcpy(file_Name, token);
        if (flag[0] == '\0')
        {
            rm_File(file_Name);
        }
        else if (flag[1] == 'd')
        {
            rm_File_D(file_Name);
        }
        else if (flag[1] == 'v')
        {
            rm_File_V(file_Name);
        }
        else
        {
            printf("Invalid Input Found -- %s\n", flag);
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}