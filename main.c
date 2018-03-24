#include "main.h"

int malloccheck(void * ptr)
{
    if(ptr == NULL)    //检查内存分配是否成功
        exit(EXIT_FAILURE);
    return 1;
}

int main()
{
    struct arrayint array;
    struct series sr;
    struct normal_distribution nd;
    struct arrayint array_list;

    sr.step = 1000;
    sr.range = 1000000;

    array = create_array(sr.range); //创建100万个数列
    rand_array(&array);   //对数列填充随机数

    sr.array = &array;

    nd.mu = normal_expect(&sr); //数学期望
    nd.sigma = normal_standard_deviation(&sr); //样本偏差


    double ref;
    double x = 3;
    ref = nd.mu + x*nd.sigma;

    struct arrayint array2;

    array2 = array_divide(&array, ref);

  
}

int get_1000()
{
    array = array_divide(array, ref);

    if(array2.size<100) //过少
    {
        array3 = array_divide(array, mu+x*(0.9)*sigma;)
    }
    else if(array.size<1000) //合适
    {

    

    }
    else //过多
    {

    }
}



