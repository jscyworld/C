//
//  print.c
//  PolishNotation
//
//  Created by kim jong soo on 2016. 12. 15..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include "polish.h"

void prn_data(data *dp) {
    switch (dp -> kind) {
        case operator:
            printf("%s%3c\n", "kind: operator   op: ", dp -> u.op);
            break;
        case value:
            printf("%s%3d\n", "kind: value      val:", dp -> u.val);
            break;
    }
}

void prn_stack(stack *stk) {
    data d;
    
    printf("stack count:%3d%s", stk -> cnt, (stk->cnt==0)? "\n":"       ");
    if (!empty(stk)) {
        d = pop(stk);
        prn_data(&d);
        prn_stack(stk);
        push(d, stk);
    }
}
