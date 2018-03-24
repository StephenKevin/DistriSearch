#ifndef SERIES_H_INCLUDED
#define SERIES_H_INCLUDED

#ifndef SERIES_C_
    #define SERIES_EXTREN extern
#else
    #define SERIES_EXTREN
#endif

struct series
{
    struct arrayint* array;
    unsigned step;
    unsigned long range;
    double average;
    long double sum;
};


struct normal_distribution
{
    double mu;
    double sigma;
};

SERIES_EXTREN double normal_expect(struct series* sr);
SERIES_EXTREN double normal_standard_deviation(struct series* sr);

#endif