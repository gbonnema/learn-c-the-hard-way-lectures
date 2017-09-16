#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name1[10];
    char name2[11] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', '\0'};

    char *res = strncpy(name1, name2, sizeof(name2));
    if (!res)
    {
        perror("Copy failed.");
        exit(-1);
    }
    printf("printed name1 = %s\n", name1);
    printf("name1 hex per char:\n");
    for(int i=0; i<20; i++)
    {
        printf(i == 0 ? "" : i%6 == 0 ? "\n" : "/");
        printf("'%8x'", name1[i]);
    }
    printf("\n");
    printf("name1 display per char:\n");
    for(int i=0; i<20; i++)
    {
        printf(i == 0 ? "" : i%6 == 0 ? "\n" : "/");
        printf("'%8c'", name1[i]);
    }
    printf("\n");

    return 0;
}
