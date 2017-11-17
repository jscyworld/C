//
//  fill.c
//  PolishNotation
//
//  Created by kim jong soo on 2016. 12. 15..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include "polish.h"

void fill(stack *stk, const char *str) {
    const char *p = str;
    char c1, c2;
    boolean b1, b2;
    data d;
    stack temp;
    
    initialize(stk);
    initialize(&temp);
    
    while (*p != '\0') {
        while(isspace(*p) || *p == ',')
            ++p;
        b1 = (boolean) ((c1 = *p) == '+' || c1 == '-' || c1 == '*');
        b2 = (boolean) ((c2 = *(p+1)) == ',' || c2 == '\0');
        if (b1 && b2) {
            d.kind = operator;
            d.u.op = c1;
        } else {
            d.kind = value;
            assert(sscanf(p, "%d", &d.u.val) == 1);
        }
        if (!full(&temp))
            push(d, &temp);
        while (*p != ',' && *p != '\0')
            ++p;
    }
    while (!empty(&temp)) {
        d = pop(&temp);
        if (!full(&temp))
            push(d, stk);
    }
}

