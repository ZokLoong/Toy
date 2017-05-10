//
//  Toymatstack.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toymatstack.h"
#include "Toymat4.h"

#define TOY_MAT_STACK_INIT_SIZE     32
#define TOY_MAT_STACK_INCREMENT     64

void ToymatAlloc(Toymatstack *stack) {
    stack->stack = (Toymat4 *)malloc(sizeof(Toymat4) * TOY_MAT_STACK_INIT_SIZE);
    stack->top = 0;
    stack->capacity = TOY_MAT_STACK_INIT_SIZE;
    stack->current = 0;
}

void ToymatPush(Toymatstack *stack, const struct Toymat4 *mat) {
    stack->top = &stack->stack[stack->current];
    Toymat4Assign(stack->top, mat);
    stack->current++;
    
    if (stack->current == stack->capacity) {
        Toymat4 *newstack = (Toymat4 *)malloc(sizeof(Toymat4) * (stack->capacity + TOY_MAT_STACK_INCREMENT));
        memcpy(newstack, stack->stack, sizeof(Toymat4) * stack->capacity);
        stack->capacity += TOY_MAT_STACK_INCREMENT;
        free(stack->stack);
        stack->stack = newstack;
        stack->top = &stack->stack[stack->current - 1];
    }
}

void ToymatPop(Toymatstack *stack, struct Toymat4 *mat) {
    if (stack->current == 0) {
        return;
    }
    
    if (mat) {
        Toymat4Assign(mat, stack->top);
    }
    stack->current--;
    stack->top = stack->current > 0 ? &stack->stack[stack->current - 1] : 0;
}

void ToymatFree(Toymatstack *stack) {
    if (stack->stack) {
        free(stack->stack);
        stack->stack = 0;
    }
    stack->top = 0;
    stack->capacity = stack->current = 0;
}
