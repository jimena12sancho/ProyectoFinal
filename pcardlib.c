#include "pcardlib.h"
struct pcard _pcard(char _type, int _number){
    char T[4] = {'P', 'C', 'D', 'T'};
    bool is_type = false;

    for (int i = 0; i < 4; ++i)
        is_type = is_type || (_type == T[i]);

    assert(inRange(1, 13,  _number));
    assert(is_type);

    struct pcard s;
    s.type = _type;
    s.number = _number;

    return s;
}

int pcard_comparator(void *pc1, void *pc2){
    int l = ((struct pcard *)pc1)->number;
    int r = ((struct pcard *)pc2)->number;
    return (l - r);
}