#ifndef SHARLIN_PCARDLIB_H
#define SHARLIN_PCARDLIB_H
#include <assert.h>
#include "utilsfun.h"
struct pcard{
    char type;
    int number;
};
struct pcard _pcard(char _type, int _number);
#endif //SHARLIN_PCARDLIB_H
int pcard_comparator(void *pc1, void *pc2);