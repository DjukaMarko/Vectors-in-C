#include <stdio.h>
#include <stdlib.h>
#define HEADER 10

int d()
{
    int age;

    a:
        printf("less goo\n");

    b:
        printf("i am dababy\n");

    printf("How old are you?: \n");
    scanf("%d", &age);

    if(age >= 18) {
        printf("%d", HEADER);
        goto a;
    } else {
        goto b;
    }

    printf("end!\n");
    return 0;
}
