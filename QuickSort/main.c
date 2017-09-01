//
//  main.c
//  QuickSort
//
//  Created by kim jong soo on 2016. 12. 6..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//
#include "Quick.h"

int main(int argc, const char * argv[]) {
    int a[N] = {7, 4, 3, 5, 2, 5, 8, 2, 1, 9, -6, -3};
    
    printf("Before Quick Sort: ");
    for (int i=0; i<N; ++i)
        printf("%d ",a[i]);
    putchar('\n');
    
    quicksort(a, a+N-1);
    printf(" After Quick Sort: ");
    for (int i=0; i<N; ++i)
        printf("%d ",a[i]);
    putchar('\n');
    putchar('\n');
    return 0;
}
