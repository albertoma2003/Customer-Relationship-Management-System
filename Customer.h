#ifndef _Customer_h
#define _Customer_h

#include "UTString.h"

struct Customer {
    UTString name;
    int bottles;
    int diapers;
    int rattles;

    Customer(UTString);
    Customer(void) { name = "__invalid__"; }
};

#endif /* _Customer_h */
