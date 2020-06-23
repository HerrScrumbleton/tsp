#include "iterator.h"

Iterator::Iterator()
{

}
void Iterator::solve(Iterable *i){
    int n = 0;
    while (n < Iter_max){ //Oder genauigkeit
        i->apply();
    }
}
