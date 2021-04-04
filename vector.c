#include <stdio.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAIL -1
#define DEFAULT_CAPACITY 10

typedef struct vector_mk Vector;

struct vector_mk {

    int *items;
    int capacity;
    int total_elements;


    int (*resize_vector)(Vector*, int size);
    int (*add_end_vector)(Vector*, int value);
    int (*add_vector)(Vector*, int index);
    int (*delete_vector)(Vector*, int index);
    int (*free_vector)(Vector*);
    void (*print_vector)(Vector*);

};


int resize_Vector(Vector *v, int size) {

    if(v != NULL) {
        v->items = (int *) realloc(v->items, size);
        v->capacity = size;
        return SUCCESS;
    }
    return FAIL;
}


int add_End_Vector(Vector *v, int value) {
    if(v == NULL) return FAIL;
    if(v->total_elements == v->capacity) {
        int result = v->resize_vector(v, v->capacity*2);
        if(result == SUCCESS) {
            v->items[v->total_elements++] = value;
            return SUCCESS;
        }
    } else {
        v->items[v->total_elements++] = value;
    }
    return SUCCESS;
}


int add_Vector(Vector *v, int index) {
    if(v == NULL) return FAIL;
    if(index < 0 || index > v->capacity) return FAIL;
    if(v->total_elements == v->capacity) {
        int result = v->resize_vector(v, index);
        if(result == SUCCESS) {
            v->items[index] = index;
            v->total_elements++;
            return SUCCESS;
        }
    } else {
        v->items[index] = index;
        v->total_elements++;
    }
    return SUCCESS;
}


int delete_Vector(Vector *v, int index) {
    if(v == NULL) return FAIL;
    if(v->total_elements <= 0) return FAIL;
    if(index < 0 || index > v->capacity) return FAIL;

    v->items[index] = 0; // USE 0 INSTEAD OF NULL.
    for(int i = index; i < v->total_elements; i++) {
        v->items[i] = v->items[i+1];
        v->items[i+1] = 0;
    }
    v->total_elements--;
    if(v->total_elements < (v->capacity)/4) {
        v->resize_vector(v, (v->capacity)/2);
    }
    return SUCCESS;
}

int free_Vector(Vector *v) {
    if(v == NULL) return FAIL;
    free(v->items);
    return SUCCESS;
}

void print_Vector(Vector *v) {
    if(v == NULL) return;
    for(int i = 0; i < v->total_elements; i++) {
        printf("%d\n", v->items[i]);
    }
}

int vector_init(Vector *v, int size) {
    v->items = (int*)malloc(size*sizeof(Vector));
    if(!v->items) return FAIL;

    v->capacity = DEFAULT_CAPACITY;
    v->total_elements = 0;

    v->resize_vector = &resize_Vector;
    v->add_end_vector = &add_End_Vector;
    v->add_vector = &add_Vector;
    v->delete_vector = &delete_Vector;
    v->free_vector = &free_Vector;
    v->print_vector = &print_Vector;

    return SUCCESS;
}

int main() {
    Vector v;
    Vector *ptr_v = &v;

    vector_init(ptr_v, 5);

    printf("Initial capacity, total elements: %d, %d\n", ptr_v->capacity, ptr_v->total_elements);
    ptr_v->add_end_vector(ptr_v, 3);
    ptr_v->add_end_vector(ptr_v, 5);
    ptr_v->add_end_vector(ptr_v, 1);
    ptr_v->add_end_vector(ptr_v, 8);
    ptr_v->add_end_vector(ptr_v, 4);
    ptr_v->add_end_vector(ptr_v, 15);
    ptr_v->add_end_vector(ptr_v, 17);
    ptr_v->add_end_vector(ptr_v, 7);
    ptr_v->add_end_vector(ptr_v, 9);
    ptr_v->add_end_vector(ptr_v, 12);
    ptr_v->add_end_vector(ptr_v, 14);
    /*ptr_v->add_end_vector(ptr_v, 16);*/
    ptr_v->print_vector(ptr_v);
    printf("Capacity, total elements after adding: %d, %d\n", ptr_v->capacity, ptr_v->total_elements);
    /*ptr_v->delete_vector(ptr_v, 0);
    printf("Capacity, total elements after adding: %d, %d\n", ptr_v->capacity, ptr_v->total_elements);
    ptr_v->print_vector(ptr_v);
    ptr_v->free_vector(ptr_v);
    printf("Capacity, total elements after adding: %d, %d\n", ptr_v->capacity, ptr_v->total_elements);
    ptr_v->print_vector(ptr_v);*/
    ptr_v->free_vector(ptr_v);



    return 0;
}
