#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_DIDNT_OPEN_ERROR -1
#define EXIT_SUCCESS 0
#define MAX_LINE 1024
#define MAX_FILE_NAME 256
#define MAXLENGTH 30

typedef struct
{
    char name[MAXLENGTH];
    char lastname[MAXLENGTH];
    int score;
}STUDENT;

int countStudentsFromFile(char*);
int EnterStudents(char*, int, STUDENT*);
int PrintStudents(int, STUDENT*, int);
int FindMax(int, STUDENT*);


int main()
{
    char filename[MAX_FILE_NAME] = { 0 };
    int m = 0, n = 0, max = 0;
    printf("Insert filename:\n");
    scanf(" %s", filename);
    STUDENT* st = NULL;
    int result = 0;
    result = countStudentsFromFile(filename);
    printf("Number of students in file %s is %d\n", filename, result);

    st = (STUDENT*)malloc(result * sizeof(STUDENT));
    if (st == NULL)
    {
        printf("Failed in dynamic allocation!");
        return -1;
    }
    m = EnterStudents(filename, result, st);

    if (m != EXIT_SUCCESS)
        return FILE_DIDNT_OPEN_ERROR;

    max = FindMax(result, st);
    n = PrintStudents(result, st, max);
    free(st);

    return EXIT_SUCCESS;
}



int countStudentsFromFile(char* filename)
{
    FILE* fp = NULL;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Failed in file opening!\r\n");
        return FILE_DIDNT_OPEN_ERROR;
    }
    while (fgets(buffer, MAX_LINE, fp) != NULL)
    {
        if (strcmp(buffer, "\n") != 0)
            count++;
    }
    fclose(fp);  
    return count;
}
int EnterStudents(char* filename, int number, STUDENT* s)
{
    int i = 0;
    FILE* f = NULL;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Failed in file opening!");
        return FILE_DIDNT_OPEN_ERROR;
    }

    for (i = 0; i < number; i++)
        fscanf(f, "%s %s %d", (s + i)->name, (s + i)->lastname, &(s + i)->score);

    fclose(f);
    return EXIT_SUCCESS;
}

int FindMax(int number, STUDENT* s)
{
    int i = 0, max = 0;
    for (i = 0; i < number; i++)
    {
        if ((s + i + 1)->score > (s + i)->score)
            max = (s + i + 1)->score;
    }

    return max;
}

int PrintStudents(int number, STUDENT* s, int max)
{
    int i;
    for (i = 0; i < number; i++)
        printf("Student: %s %s\nAbsolutely score %d\nRelative score: %f\n", (s + i)->name, (s + i)->lastname, (s + i)->score, ((double)(s + i)->score / max) * 100);
    return EXIT_SUCCESS;
}

