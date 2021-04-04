#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STATUS_STACK_OVERFLOW 0xC00000FD
#define PRINT_VAR(X)\
    printf("%s is val %d\n", #X, X);

#define getVar(Y) #Y

typedef struct object_name {
    int* value;
    int test;

} Object;

typedef struct {
    int x;
    int *y;
} Object2;


void print_object2(Object2* aptr) {
    printf("x: %d\n", aptr->x);
    printf("y: %d\n", aptr->y);
}


int fun (int a, int b) {
    return a+b;
}

void function1(int arr[], int val, int (*p)(int, int)) {
    for(int i = 0; i < val; i++) {
        arr[i] = (*p)(i, i+1);
        printf("%d\n", arr[i]);
    }
}

int function2(int i) {

    if(i == 20) {
        return i;
    }
    printf("%d\n", i);
    return function2(i+1);

}

union Motor {
    int x;
    unsigned int y;
    char z;
};

int main() {

    int size = 10;
    int *aptr = (int*) calloc(size, sizeof(int));
    for(int i = 0; i < size; i++) {
        aptr[i] = i*2-1;
        printf("%d\n", aptr[i]);
    }
    puts(" ");

    free(aptr);

    Object *object = (Object*) malloc(sizeof(Object));
    object->value = (int*) calloc(2, sizeof(int));
    object->value[0] = 3;
    object->value[1] = 4;
    for(int i = 0; i < 2; i++) {
        printf("%d\n", object->value[i]);
    }

    printf("%x", object);
    free(object->value);
    free(object);

    puts("\n ");

    int (*aptr2)(int, int) = &fun;

    int result = (*aptr2)(10, 10);
    printf("%d\n", result);

    char *aptr3 = (char*) calloc(2, sizeof(char));
    *aptr3 = 'c';
    *(aptr3+1) = 'd';
    printf("%c\n", 1[aptr3]);

    free(aptr3);

    int s = 3;
    int **aptr4;
    int *aptr5 = &s;

    aptr4 = &aptr5;

    //free(aptr5); unlock this and you'll crash your system you moron.

    //printf("%d", *aptr4);

    int *num = (int*) calloc(5, sizeof(int));
    function1(num, 4, &fun);
    free(num);

    puts(" \n");

    int x1 = 3;
    Object2 *aptr_o = (Object2*) malloc(2*sizeof(Object2));
    printf("%d\n", aptr_o);
    printf("%d\n", aptr_o+2);
    aptr_o->x = 3;
    (*aptr_o).y = &x1;
    *((*aptr_o).y) = 4;
    printf("%d", x1);
    /*aptr_o->y = 5;
    (aptr_o+1)->x = 6;
    (aptr_o+1)->y = 10;*/
    /*printf("%d\n", aptr_o[1].x);*/
    //print_object2(aptr_o);
    function2(10);
    union Motor moto;
    union Motor* aptrM = &moto;
    moto.x = 3;
    printf("%d %d\n", moto.x, moto.y);
    moto.y = 2;
    printf("%d %d\n", moto.x, moto.y);
    printf("%0x\n", aptrM);
    union Motor moto2;
    union Motor *moto2aptr = &moto2;
    moto2aptr->x = -83;
    printf("%d\n", moto2aptr->z);
    int x = 3;
    int y = 8;
    PRINT_VAR(x);
    x ^= y ^= x;
    printf("value %d %d\n", x, y);
    FILE *file1 = fopen("main2.c", "r");
    FILE *file2 = fopen("test2.txt", "w");
    char c;
    do {
        c = fgetc(file1);
        if(c == EOF) break;
        fputc(c, file2);
    } while(1); //c != EOF
    fclose(file1);
    fclose(file2);
    printf("%c\n", 64);



    return 0;


}


