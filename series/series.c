#define SERIES_C_

#include "main.h"

double transform_self(int data, struct series *sr)
{
    return data;
}

double transform_int_div_square(int data, struct series *sr)
{
    double item;
    item = data - sr->average;
    return item*item/(sr->range/sr->step);
}

long double series_sum(struct series *sr, double(*transform)(int a,struct series *sr))
{
    long double sum=0;
    int data;
    unsigned long i;

    array_adjust(sr->array);

    for(i=0; i<sr->range; i+=sr->step)
    {
        array_jump(sr->array, sr->step);
        data = array_get(sr->array); 
        sum += transform(data, sr);
    }
    return sum;
}

double average(long double sum, unsigned long size)
{
    return sum/size;
}

double normal_expect(struct series* sr)
{
    long double sum;
    sum = series_sum(sr,transform_self);
    sr->sum = sum;
    sr->average = average(sr->sum, sr->range/sr->step+1);
    return sr->average;
}

double normal_standard_deviation(struct series* sr)
{
    long double mean_square_deviation;
    double sigma;

    mean_square_deviation = series_sum(sr, transform_int_div_square);
    sigma = sqrt(mean_square_deviation);
    return sigma;
}
