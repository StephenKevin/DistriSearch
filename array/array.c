#ifndef ARRAY_C_
    #define ARRAY_C_
#endif

#include "main.h"

struct arrayint create_array(unsigned size)
{
    struct item_int *item,*last_item,*head,*tail;
    struct arrayint array;
    int i;

    array.head = malloc(sizeof(struct item_int));
    malloccheck(array.head);
    array.head->last = NULL;
    array.head->next = NULL;
    array.current = array.head;
    
    for(i=1;i<size;i++)
    {
        item = malloc(sizeof(struct item_int));
        malloccheck(item);
        insert_item_behind(&array, item, array.current);
        array.current = item; 
    }
    array.tail = item;
    array.size = size;
    return array;
}

int array_get(struct arrayint * array)
{
    return array->current->data;
}

int array_jump(struct arrayint *array, unsigned size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(array->current!=NULL)
        {
            array->current = array->current->next;
            return 1;
        }
        else return 0;
    }
}

int array_jump_to_item(struct arrayint *array, struct item_int* item)
{
    //
}

/**将 array 的调整头尾部和游标**/
void array_adjust(struct arrayint *array)
{
    if(array->head!=NULL)
    {
        while(array->head->last!=NULL)
            array->head = array->head->last;
    }
    if(array->tail!=NULL)
    {
        while(array->tail->next!=NULL)
            array->tail = array->tail->next;
    }
    array->current = array->head;
}

int array_count(struct arrayint *array)
{
    array_adjust(array); //可能删除

    array->current = array->head;
    while(array->current!=NULL)
    {
        array->current = array->current->next;
        array->size++;
    }
    array->current = array->head;

    return array->size;
}

int rand_array(struct arrayint * array)
{
    array->current = array->head;
    while(array->current->next!=NULL)
    {
        array->current->data = rand();
    }
}

int item_join(struct arrayint * array, 
    struct item_int* item_x, struct item_int* item_y)
{
    if(item_x!=NULL) //
        item_x->next = item_y;
    else
        array->head = item_y;

    if(item_y!=NULL)
        item_y->last = item_x;
    else
        array->tail = item_x;
}

/*补充一个项的上下(它已经指向了上下)链接*/
int item_connect(struct arrayint * array,struct item_int* item)
{
    if(item!=NULL)
    {
        if(item->last!=NULL)
            item->last->next = item;
        else array->head = item;

        if(item->next!=NULL)
            item->next->last = item;
        else array->tail = item;
    }
}

/** 弹出一个 **/
/**如果是当前项，则当前项会往下移动。如果是弹出尾部则往上移动。
**/
struct item_int* pop_item(struct arrayint * array, struct item_int* item)
{
    if(item!=NULL)
    {
        if(item==array->current)
            array->current = item->next; //

        item_join(array, item->last, item->next);
        array->size--;
    }
    return item;
}

int delete_item(struct arrayint * array, struct item_int* item)
{
    pop_item(array,item);
    free(item);
}


int replace_item(struct arrayint * array, 
    struct item_int *replaced, struct item_int *replace)
{
    if(replaced!=NULL)
    {
        if(replace!=NULL)
        {
            item_join(array, replaced->last,replace);
            item_join(array, replace, replaced->next);
            return 1;
        }
    }
    return 0;
}


int insert_item_before(struct arrayint * array, 
    struct item_int* item, struct item_int* next_item)
{
    if(item!=NULL)
    {
        if(next_item!=NULL)
            item_join(array, next_item->last, item);
        item_join(array, item, next_item);
        array->size++;
        return 1;
    }
    else return 0;
}

int insert_item_behind(struct arrayint * array, 
    struct item_int* item, struct item_int* last_item)
{
    if(item!=NULL)
    {
        item_join(array, last_item, item);
        if(last_item!=NULL)
            item_join(array, item, last_item->next);
        array->size++;
        return 1;
    }
    else return 0;
    //current尚未自动调整
}

int item_compare(struct item_int* item_x, struct item_int* item_y)
{
    return (item_x->data)>(item_y->data);
}

void item_swap_data(struct item_int* item_x, struct item_int* item_y)
{
    int temp;
    if(item_x!=NULL && item_y!=NULL)
    {
        temp = item_x->data;
        item_x->data = item_y->data;
        item_y->data = temp;
    }
}

void item_swap_position(struct arrayint * array, 
    struct item_int* item_x, struct item_int* item_y)
{
    struct item_int temp;
    temp = *item_y;

    replace_item(array, item_x, item_y);
    item_join(array, temp.last, item_x);
    item_join(array, item_x, temp.next);
}

/***剪断**/
struct arrayint array_cut_behind(struct arrayint *array, struct item_int *item)
{
    struct arrayint array_new={NULL,NULL,NULL,0};
    if(item!=NULL)
    {
        if(item->next!=NULL)
        {
            item->next->last = NULL;
            array_new.head = item->next;
            array_new.current = array_new.head;
            array_new.tail = array->tail;
        }
        item->next = NULL;
        array->tail = item;

        array->size = array->size - array_count(&array_new); //调整两链的项数
        return array_new;
    }
}

struct arrayint* array_connect(struct arrayint *array_x, struct arrayint *array_y)
{
    if(array_x->tail == NULL)
        return array_y;
    else if(array_y->head==NULL)
        return array_x;
    else
    {
        item_join(array_x, array_x->tail, array_y->head);
        return array_x;
    }
}
/***划分***/
struct arrayint array_divide(struct arrayint *array, double ref)
{
    struct item_int *item;
    struct arrayint array_big={NULL,NULL,NULL,0};

    array_adjust(array);
    
    while(array->current!=NULL)
    {
        if((array->current->data) > ref)
        {
            item = pop_item(array, array->current);
            insert_item_behind(&array_big, item, array_big.tail);
        }
        else array_jump(array, 1);
    }
    return array_big;
}
