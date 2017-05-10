//
//  Toymatstack.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toymatstack_h
#define Toymatstack_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Toymat4;
typedef struct Toymatstack {
    struct Toymat4 *top;
    struct Toymat4 *stack;
    int current;
    int capacity;
} Toymatstack;

extern void ToymatAlloc(Toymatstack *stack);
extern void ToymatPush(Toymatstack *stack, const struct Toymat4 *mat);
extern void ToymatPop(Toymatstack *stack, struct Toymat4 *mat);
extern void ToymatFree(Toymatstack *stack);

#ifdef __cplusplus
}
#endif

#endif /* Toymatstack_h */
