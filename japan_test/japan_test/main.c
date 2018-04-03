//
//  main.c
//  japan_test
//
//  Created by 종수수 on 2018. 3. 28..
//  Copyright © 2018년 종수수. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int start = 0, end = 0, input = 0;
    
    printf("enter start time: ");
    scanf("%d", &start);
    printf("enter end time: ");
    scanf("%d", &end);
    printf("enter wanted time: ");
    scanf("%d", &input);
    
    if (start != end) {
        if (end > start) {
            if ((input > start) && (input < end)) {
                printf("correct!\n");
            } else {
                printf("no!\n");
            }
        } else {
            if ((input > start) || (input < end)) {
                printf("correct!\n");
            } else {
                printf("no!\n");
            }
        }
    } else {
        printf("correct!\n");
    }
    
    return 0;
}
