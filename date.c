
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sysexits.h>
#include <errno.h>

void print_date()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = localtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error found is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s %s %02d %02d:%02d:%02d %s %d\n", buf1, buf2, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, buf3, ptm->tm_year + 1900);
}

void print_date_U()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error found is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = gmtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error found is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s %s %02d %02d:%02d:%02d UTC %d\n", buf1, buf2, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, ptm->tm_year + 1900);
}

void print_date_R()
{
    time_t rawtime = time(NULL);
    if (rawtime == -1)
    {
        perror("Error found is");
        return;
    }
    struct tm *ptm;
    char buf1[4], buf2[4], buf3[6];
    ptm = localtime(&rawtime);
    if (ptm == NULL)
    {
        perror("Error found is");
        return;
    }
    strftime(buf1, 4, "%a", ptm);
    strftime(buf2, 4, "%b", ptm);
    strftime(buf3, 6, "%z", ptm);
    printf("%s, %02d %s %d %02d:%02d:%02d %s\n", buf1, ptm->tm_mday, buf2, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, buf3);
}

int main(int argc, char *argv[])
{
    char command_Name[10] = "";
    char flag[10] = "";
    char *token = strtok(argv[1], " ");
    strcpy(command_Name, token);
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        strcpy(flag, token);
    }
    if (strcmp(flag, "") == 0)
    {
        print_date();
    }
    else if (flag[1] == 'u')
    {
        print_date_U();
    }
    else if (flag[1] == 'R')
    {
        print_date_R();
    }
    else
    {
        printf("Invalid input found -- %s\n", flag);
        return 1;
    }
    return 0;
}