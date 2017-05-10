//
//  ToyGLmatrix.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyGLmatrix.h"
#include "Toyvec3.h"
#include "Toymat4.h"
#include "Toymathcommon.h"

static Toymatstack s_modelview;
static Toymatstack s_projection;
static Toymatstack s_texture;
static Toymatstack *s_current = 0;
static char s_initialized = 0;

static void ToyGLmatrixInit() {
    if (!s_initialized) {
        Toymat4 identity;
        
        ToymatAlloc(&s_modelview);
        ToymatAlloc(&s_projection);
        ToymatAlloc(&s_texture);
        
        Toymat4Identity(&identity);
        s_current = &s_modelview;
        
        ToymatPush(&s_modelview, &identity);
        ToymatPush(&s_projection, &identity);
        ToymatPush(&s_texture, &identity);
        
        s_initialized = 1;
    }
}

void ToyGLmatrixMode(eToyGLmode mode) {
    ToyGLmatrixInit();
    
    switch (mode) {
        case TOY_GL_MODELVIEW: s_current = &s_modelview; break;
        case TOY_GL_PROJECTION: s_current = &s_projection; break;
        case TOY_GL_TEXTURE: s_current = &s_texture; break;
        default: printf("Error: Invalide GL mode\n"); break;
    }
}

void ToyGLmatrixPush() {
    if (s_initialized) {
        Toymat4 top;
        
        Toymat4Assign(&top, s_current->top);
        ToymatPush(s_current, &top);
    } else {
        printf("Error: GL matrix must be set mode before PUSH opt.\n");
    }
}

void ToyGLmatrixPop() {
    if (s_initialized) {
        ToymatPop(s_current, 0);
    } else {
        printf("Error: GL matrix must be set mode before POP opt.\n");
    }
}

void ToyGLloadIdentity() {
    if (s_initialized) {
        Toymat4Identity(s_current->top);
    } else {
        printf("Error: GL matrix must be set mode before IDENTITY opt.\n");
    }
}

void ToyGLmatrixMul(const struct Toymat4 *mat) {
    if (s_initialized) {
        Toymat4Multiply(s_current->top, s_current->top, mat);
    } else {
        printf("Error: GL matrix must be set mode before MUL opt.\n");
    }
}

void ToyGLtranslatef(float x, float y, float z) {
    if (s_initialized) {
        Toymat4 transf;
        
        Toymat4Translatef(&transf, x, y, z);
        Toymat4Multiply(s_current->top, s_current->top, &transf);
    } else {
        printf("Error: GL matrix must be set mode before TRANSLATE opt.\n");
    }
}

void ToyGLrotatef(float x, float y, float z, float degree) {
    if (s_initialized) {
        Toymat4 rotatef;
        Toyvec3 axis;
        
        Toyvec3Fill(&axis, x, y, z);
        Toymat4Rotatef(&rotatef, &axis, degree);
        Toymat4Multiply(s_current->top, s_current->top, &rotatef);
    } else {
        printf("Error: GL matrix must be set mode before ROTATE opt.\n");
    }
}

void ToyGLscalef(float x, float y, float z) {
    if (s_initialized) {
        Toymat4 scalef;
        
        Toymat4Scalef(&scalef, x, y, z);
        Toymat4Multiply(s_current->top, s_current->top, &scalef);
    } else {
        printf("Error: GL marix must be set mode before SCALE opt.\n");
    }
}

void ToyGLmatrixGet(struct Toymat4 *mat) {
    if (s_initialized) {
        Toymat4Assign(mat, s_current->top);
    } else {
        printf("Error: GL marix must be set mode before GET opt.\n");
    }
}

void ToyGLmatrixLoad(struct Toymat4 *mat) {
    if (s_initialized) {
        Toymat4Assign(s_current->top, mat);
    } else {
        printf("Error: GL marix must be set mode before LOAD opt.\n");
    }
}
