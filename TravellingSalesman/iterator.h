#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterable.h>

class Iterator
{
public:
    Iterator();
    void solve(Iterable *);

private:
    int Iter_max = 10;
};

#endif // ITERATOR_H
