//
//  main.c
//  PolishNotation
//
//  Created by kim jong soo on 2016. 12. 15..
//  Copyright © 2016년 kim jong soo. All rights reserved.
//

#include "polish.h"

int main(int argc, const char * argv[]) {
    char str[] = "13, 4, -, 2, 3, *, +";
    stack polish;
    
    printf("\n%s%s\n\n", "Polish expression: ", str);
    fill(&polish, str);
    prn_stack(&polish);
    printf("\n%s%d\n\n", "Polish evaluation: ", evaluate(&polish));
    

    return 0;
}
