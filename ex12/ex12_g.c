#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    int areas[] = { 10, 12, 13, 14, 20 };
    long lareas[] = { 10, 12, 13, 14, 20 };
    float fareas[] = { 10, 12, 13, 14, 20 };
    double dareas[] = { 10, 12, 13, 14, 20 };
    char name[15] = "Zed";
    char full_name[] =
    {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w', '\0'
    };
    char *name1 = calloc(14, sizeof(char));

    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The size of an long: %ld\n", sizeof(long));
    printf("The size of areas (long[]): %ld\n", sizeof(lareas));
    printf("The size of an float: %ld\n", sizeof(float));
    printf("The size of areas (float[]): %ld\n", sizeof(fareas));
    printf("The size of an double: %ld\n", sizeof(double));
    printf("The size of areas (int[]): %ld\n", sizeof(dareas));
    printf("The number of ints in areas: %ld\n",
           sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

    printf("The size of *name1 (char): %ld\n", sizeof(*name1));
    printf("The size of name1 (char *): %ld\n", sizeof(name1));

    printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld\n",
           sizeof(full_name) / sizeof(char));

    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}
