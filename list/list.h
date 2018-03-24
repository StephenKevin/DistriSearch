struct item_array
{
    struct arrayint* array;
    struct item_array *last;
    struct item_array *next;
};

//由 array 组成的 list
struct array_list
{
    struct item_array * head;
    struct item_array * tail;
    struct item_array * current;
};