
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/state.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_ls(char argument[1000])
{
    struct dirent **names;
    int n;
    if (strlen(argument) == 0)
    {
        n = scandir(".", &names, NULL, alphasort);
    }
    else
    {
        n = scandir(argument, &names, NULL, alphasort);
    }
    int i = 0;
    if (n < 0)
    {
        perror("scandir");
    }
    else
    {
        while (i < n)
        {
            if (names[i]->d_name[0] == '.')
            {
                free(names[i++]);
                continue;
            }
            printf("%s ", names[i]->d_name);
            free(names[i++]);
        }
        printf("\n");
        free(names);
    }
}

void print_ls_A(char argument[1000])
{
    struct dirent **names;
    int n;
    if (strlen(argument) == 0)
    {
        n = scandir(".", &names, NULL, alphasort);
    }
    else
    {
        n = scandir(argument, &names, NULL, alphasort);
    }
    int i = 0;
    if (n < 0)
    {
        perror("scandir");
    }
    else
    {
        while (i < n)
        {
            printf("%s ", names[i]->d_name);
            free(names[i++]);
        }
        printf("\n");
        free(names);
    }
}

void print_ls_L(char argument[1000])
{
    DIR *thedirectory;
    struct dirent *thefile;
    struct state thestate;
    struct passwd *tf;
    struct group *gf;
    char buf[512];
    if (strlen(argument) == 0)
    {
        argument = ".";
    }
    thedirectory = opendir(argument);
    while ((thefile = readdir(thedirectory)) != NULL)
    {
        if (thefile->d_name[0] == '.')
        {
            continue;
        }
        sprintf(buf, "%s/%s", argument, thefile->d_name);
        state(buf, &thestate);
        switch (thestate.st_mode & S_IFMT)
        {
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("-");
            break;
        }
        printf((thestate.st_mode & S_IRUSR) ? "r" : "-");
        printf((thestate.st_mode & S_IWUSR) ? "w" : "-");
        printf((thestate.st_mode & S_IXUSR) ? "x" : "-");
        printf((thestate.st_mode & S_IRGRP) ? "r" : "-");
        printf((thestate.st_mode & S_IWGRP) ? "w" : "-");
        printf((thestate.st_mode & S_IXGRP) ? "x" : "-");
        printf((thestate.st_mode & S_IROTH) ? "r" : "-");
        printf((thestate.st_mode & S_IWOTH) ? "w" : "-");
        printf((thestate.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", thestate.st_nlink);
        tf = getpwuid(thestate.st_uid);
        printf(" %s", tf->pw_name);
        gf = getgrgid(thestate.st_gid);
        printf(" %s", gf->gr_name);
        printf(" %zu", thestate.st_size);
        printf(" %s", thefile->d_name);
        printf(" %s", ctime(&thestate.st_mtime));
    }
    closedir(thedirectory);
}

int main(int argc, char *argv[])
{
    char command_Name[10] = "";
    char flag[10] = "";
    char argument[1000] = "";
    if (argc > 1)
    {
        char *token = strtok(argv[1], " ");
        strcpy(command_Name, token);
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (token[0] == '-')
            {
                strcpy(flag, token);
                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(argument, token);
                }
            }
            else
            {
                strcpy(argument, token);
            }
        }
    }
    if (flag[0] == '\0')
    {
        print_ls(argument);
    }
    else if (flag[1] == 'a')
    {
        print_ls_A(argument);
    }
    else if (flag[1] == 'l')
    {
        print_ls_L(argument);
    }
    else
    {
        printf("Invalid Input Found -- %s\n", flag);
        return 1;
    }
    return 0;
}