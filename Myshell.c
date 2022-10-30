
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>

char commands[10][10] = {"cmnd", "echo", "pwd", "ls", "cat", "date", "rm", "mkdir"};
stateic char history_array[1000][1024];
stateic int counter = 0;
int nextLine;

void cmnd1(char **input_array)
{
    char cwd_inputnew2[1024];

    if (input_array[2] != NULL)
    {

        strcpy(cwd_inputnew2, input_array[2]);
        char *pt = strtok(cwd_inputnew2, "\n");
        char buf[PATH_MAX];
        char *res = realpath(pt, buf);
        if (!res)
        {
            perror("realpath error:");
        }
        else
        {
            int value23 = chdir(res);
            printf("physical source directory : %s\n", buf);
            printf("%s\n", res);
            if (value23 != 0)
            {
                perror("Error found in your command - ");
            }
            else
            {
                char cwd5[200];
                char *cwd35 = getcwd(cwd5, sizeof(cwd5));
            }
        }
    }
    else
    {
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
        {
            perror("Error found in your command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cmnd2(char **input_array)
{
    if (input_array[2] != NULL)
    {
        char cwd_inputnew2[1024];
        strcpy(cwd_inputnew2, input_array[2]);
        char *inputnew3 = "";
        char *inputnew4 = "hi";
        // printf("yo");
        char *pt = strtok(cwd_inputnew2, "\n");
        int id = chdir(pt);
        if (id != 0)
        {
            perror("Error found in -L command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
    else
    {
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
        {
            perror("Error found in your command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cmnd(char **input_array)
{
    int flaggers1 = INT_MAX;
    int flaggers2 = INT_MAX;
    int flaggers3 = INT_MAX;
    int flaggers4 = INT_MAX;
    int flaggers5 = INT_MAX;
    int flaggers6 = INT_MAX;
    int flaggers7 = INT_MAX;

    char cwd_inputnew1[1024];

    if (input_array[1] != NULL)
    {

        strcpy(cwd_inputnew1, input_array[1]);
        flaggers1 = strcmp(cwd_inputnew1, "~");
        flaggers2 = strcmp(cwd_inputnew1, "--");
        flaggers3 = strcmp(cwd_inputnew1, "-");
        flaggers4 = strcmp(cwd_inputnew1, "-P");
        flaggers5 = strcmp(cwd_inputnew1, "-L");
        flaggers6 = strcmp(cwd_inputnew1, "--help");
    }
    else
    {
        flaggers7 = 0;
    }
    if (flaggers3 == 0)
    {
        int flag3 = chdir("..");
        if (flag3 != 0)
        {
            perror("Error found in your command - ");
        }
        else
        {
            char cwd2[200];
            char *cwd32 = getcwd(cwd2, sizeof(cwd2));
            printf("%s", cwd32);
        }
    }
    else if (flaggers1 == 0 || flaggers2 == 0 || flaggers7 == 0)
    {
        int flag127 = chdir(getenv("HOME"));
        if (flag127 != 0)
        {
            perror("Error found in your command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }

    else if (flaggers6 == 0)
    {
        printf("%s", "This Command is used to change the directory for given input");
    }
    else if (flaggers4 == 0)
    {
        cmnd1(input_array);
    }
    else if (flaggers5 == 0)
    {
        cmnd2(input_array);
    }
    else
    {
        char *pt = strtok(cwd_inputnew1, "\n");
        int value = chdir(pt);
        if (value != 0)
        {
            perror("Error found in your Commands - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void echo1(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}

void echo2(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}

void echo(char **input_array, int size)
{
    int flagger4 = INT_MAX;
    int flagger5 = INT_MAX;
    int flagger6 = INT_MAX;
    char echo_input[10];
    if (input_array[1] != NULL)
    {
        strcpy(echo_input, input_array[1]);
        flagger4 = strcmp(echo_input, "-n");
        flagger5 = strcmp(echo_input, "-E");
        flagger6 = strcmp(echo_input, "--help");
    }
    else
    {
        return;
    }
    if (flagger4 == 0)
    {
        nextLine = 1;
        echo1(input_array, size);
    }
    else if (flagger5 == 0)
    {
        echo2(input_array, size);
    }
    else if (flagger6 == 0)
    {
        printf("%s", "This command prints the input given after echo");
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (input_array[i] != NULL)
            {
                printf("%s ", input_array[i]);
            }
        }
    }
}



void pwd1()
{
    char new_arr[1024];
    char *cwd2 = getcwd(new_arr, sizeof(new_arr));
    printf("%s", cwd2);
}

void pwd2()
{
    char buf[PATH_MAX];
    char new_arr[1024];
    char *res = realpath(new_arr, buf);
    char *cwd2 = getcwd(new_arr, sizeof(new_arr));
    printf("%s", cwd2);
}

void pwd(char **input_array)
{
    int newflag = 0;
    char cwd_input[10];
    char arr[1024];
    int flagger2 = INT_MAX;
    int flagger3 = INT_MAX;
    int flagger4 = INT_MAX;

    if (input_array[1] != NULL)
    {
        strcpy(cwd_input, input_array[1]);
        newflag = 1;
    }

    char *cwd = getcwd(arr, sizeof(arr));
    if (cwd == NULL)
    {
        perror("Error:");
    }
    else
    {
        if (newflag == 1)
        {
            flagger2 = strcmp(cwd_input, "-P");
            flagger3 = strcmp(cwd_input, "--help");
            flagger4 = strcmp(cwd_input, "-L");
            if (flagger3 == 0)
            {
                printf("%s", "This command prints the current working directory");
                exit;
            }
            else if (flagger2 == 0)
            {
                pwd1();
            }
            else if (flagger4 == 0)
            {
                pwd2();
            }
        }
        else
        {
            printf("%s", cwd);
        }
    }
}

int main()
{
    printf("*******************************YOU ARE IN ANKIT'S SHELL***********************************\n\n");
    printf("Only following commands are accepted  -----> 'cmnd' \n 'pwd' \n 'echo' \n 'rm' \n 'ls' \n 'mkdir' \n 'cat' \n 'date' " ) ;
    char cwd[100];
    while (1)
    {
        nextLine = 0;

        char command[1024];
        printf("$ ");

        scanf("%[^\n]%*c", command);

        if (command[0] != 0)
        {
            int size = 0;
            char func[10];
            int flagger = -1;
            int func_num = -1;
            char new_command[1024];
            char **input_array = (char **)malloc(500 * sizeof(char *));

            strcpy(new_command, command);
            if (counter > 999)
            {
                counter = 0;
            }
            strcpy(history_array[counter++], new_command);

            char *token = strtok(command, " ");

            while (token != NULL)
            {
                input_array[size] = (char *)malloc(500 * sizeof(char));
                strcpy(input_array[size], token);
                token = strtok(NULL, " ");
                size++;
            }

            int i = 0;
            while (i < 10)
            {
                int ctr = 0;

                int flag = 0;

                while (commands[i][ctr] != '\0' && input_array[0][ctr] != '\0')
                {
                    if (commands[i][ctr] != input_array[0][ctr])
                    {
                        flag = 1;
                        break;
                    }
                    ctr++;
                }

                if (commands[i][ctr] != '\0' || input_array[0][ctr] != '\0')
                {
                    flag = 1;
                }

                if (flag != 1)
                {
                    func_num = i;
                    break;
                }
                i++;
            }

            if (func_num == 0)
            {
                cmnd(input_array);
            }
            else if (func_num == 1)
            {
                echo(input_array, size);
            }
           
            else if (func_num == 2)
            {
                pwd(input_array);
            }
            
            else if (func_num == 3)
            {
                pid_t id;
                int state;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./ls", new_command, NULL};
                    execvp("./ls", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&state);
                }
            }
            else if (func_num == 4)
            {
                pid_t id;
                int state;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./cat", new_command, NULL};
                    execvp("./cat", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&state);
                }
            }
            else if (func_num == 5)
            {
                pid_t id;

                int state;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./date", new_command, NULL};
                    execvp("./date", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&state);
                }
            }
            else if (func_num == 6)
            {
                pid_t id;
                int state;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./rm", new_command, NULL};
                    execvp("./rm", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&state);
                }
            }
            else if (func_num == 7)
            {
                pid_t id;
                int state;
                if ((id = fork()) == 0)
                {

                    char *args[] = {"./mkdir", new_command, NULL};
                    execvp("./mkdir", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&state);
                }
            }
            else
            {
                printf("%s", "Error: Unavailable Command");
            }
            if (nextLine == 0)
            {
                printf("%s\n", "");
            }
        }
        else
        {
            printf("%s\n", "PLEASE RUN AGAIN, NO INPUT FOUND");
        }
    }
    return 0;
}