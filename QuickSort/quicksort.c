//
//  quicksort.c
//  QuickSort
//
//  Created by kim jong soo on 2016. 12. 6..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include "Quick.h"

static yes_no   find_pivot(int *left, int *right, int *pivot_ptr);
static int      *partition(int *left, int *right, int pivot);

void quicksort(int *left, int *right) {
    int *p, pivot;
    
    if (find_pivot(left, right, &pivot) == yes) {
        p = partition(left, right, pivot);
        quicksort(left, p-1);
        quicksort(p, right);
    }
}

static yes_no find_pivot(int *left, int *right, int *pivot_ptr) {
    int a, b, c, *p;
    
    a = *left;
    b = *(left + (right - left) / 2);
    c = *right;
    o3(a, b, c);
    if (a < b) {
        *pivot_ptr = b;
        return yes;
    }
    if (b < c) {
        *pivot_ptr = c;
        return yes;
    }
    for (p = left+1; p<=right; ++p) {
        if (*p != *left) {
            *pivot_ptr = (*p < *left) ? *left : *p;
            return yes;
        }
    }
    return no;
}

static int *partition(int *left, int *right, int pivot) {
    while (left <= right) {
        while (*left < pivot)
            ++left;
        while (*right >= pivot)
            --right;
        if (left < right) {
            swap(*left, *right);
            ++left; --right;
        }
    }
    return left;
}
