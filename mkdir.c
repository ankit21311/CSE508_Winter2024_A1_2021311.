
#include <sys/types.h>
#include <sys/state.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void makDir(char file_Name[1000])
{
    int check = mkdir(file_Name, 0777);
    if (check == -1)
    {
        perror(file_Name);
    }
}

void mkDir_V(char file_Name[1000])
{
    int check = mkdir(file_Name, 0777);
    if (check == -1)
    {
        perror(file_Name);
    }
    else
    {
        printf("mkdir: created directory '%s'\n", file_Name);
    }
}

void mkDir_M(char file_Name[1000], int mode)
{
    int check = mkdir(file_Name, mode);
    if (check == -1)
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
            makDir(file_Name);
        }
        else
        {
            if (flag[1] == 'v')
            {
                mkDir_V(file_Name);
            }
            else if (flag[1] == 'm' && flag[2] == '=')
            {
                if (strlen(flag) < 6)
                {
                    printf("Invalid Input -- %s\n", flag);
                    return 1;
                }
                if (strlen(flag) == 7)
                {
                    char modeStr[5];
                    for (int i = 0; i < 4; i++)
                    {
                        modeStr[i] = flag[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    mkDir_M(file_Name, mode);
                }
                else
                {
                    char modeStr[4];
                    for (int i = 0; i < 3; i++)
                    {
                        modeStr[i] = flag[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d' entered \n", mode);
                        return 1;
                    }
                    mkDir_M(file_Name, mode);
                }
            }
            else
            {
                printf("Invalid Input -- %s\n", flag);
                return 1;
            }
        }
        token = strtok(NULL, " ");
    }
    return 0;
}