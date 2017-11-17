//
//  polish.h
//  PolishNotation
//
//  Created by kim jong soo on 2016. 12. 15..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY   0
#define FULL    10000

typedef struct data {
    enum {operator, value}  kind;
    union {
        char op;
        int val;
    } u;
} data;

typedef enum {false, true} boolean;

typedef struct elem {
    data    d;
    struct elem* next;
} elem;

typedef struct stack {
    int cnt;
    elem* top;
} stack;

boolean empty(const stack *stk);
int evaluate(stack *polish);
void fill(stack *stk, const char *str);
boolean full(const stack *stk);
void initialize(stack *stk);
data pop(stack *stk);
data top(stack *stk);
void prn_data(data *dp);
void prn_stack(stack *stk);
void push(data d, stack *stk);
