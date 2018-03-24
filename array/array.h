#ifndef ARRAY_H_INCLUDED

#define ARRAY_H_INCLUDED

#ifndef ARRAY_C_
    #define ARRAY_EXTREN extern
#else
    #define ARRAY_EXTREN
#endif

struct item_int
{
    int data;
    struct item_int* next;
    struct item_int* last;
};

struct arrayint
{
    struct item_int *head;
    struct item_int *tail;
    struct item_int *current;
    unsigned size;
};

ARRAY_EXTREN struct arrayint create_array(unsigned size);
ARRAY_EXTREN int rand_array(struct arrayint * array);
ARRAY_EXTREN struct arrayint array_divide(struct arrayint *array, double ref);
ARRAY_EXTREN int insert_item_behind(struct arrayint * array, 
    struct item_int* item, struct item_int* last_item);

ARRAY_EXTREN void array_adjust(struct arrayint *array);
ARRAY_EXTREN int array_jump(struct arrayint *array, unsigned size);
ARRAY_EXTREN int array_get(struct arrayint * array);

#endif
