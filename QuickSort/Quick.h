//
//  Quick.h
//  QuickSort
//
//  Created by kim jong soo on 2016. 12. 6..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include <stdio.h>

#define swap(x, y)      {int t; t = x; x = y; y = t;}
#define order(x, y)     if (x > y) swap(x, y)
#define o2(x, y)        order(x, y)
#define o3(x, y, z)     o2(x, y); o2(x, z); o2(y, z);
#define N   12

typedef enum {yes, no} yes_no;

void quicksort(int *left, int *right);
