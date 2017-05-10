//
//  ToyGLmatrix.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyGLmatrix_h
#define ToyGLmatrix_h

#include <stdio.h>
#include "Toymatstack.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Toymat4;
typedef enum eToyGLmode {
    TOY_GL_MODELVIEW,
    TOY_GL_PROJECTION,
    TOY_GL_TEXTURE,
} eToyGLmode;

extern void ToyGLmatrixMode(eToyGLmode mode);
extern void ToyGLmatrixPush();
extern void ToyGLmatrixPop();
extern void ToyGLloadIdentity();
extern void ToyGLmatrixMul(const struct Toymat4 *mat);
extern void ToyGLtranslatef(float x, float y, float z);
extern void ToyGLrotatef(float x, float y, float z, float degree);
extern void ToyGLscalef(float x, float y, float z);
extern void ToyGLmatrixGet(struct Toymat4 *mat);
extern void ToyGLmatrixLoad(struct Toymat4 *mat);

#ifdef __cplusplus
}
#endif

#endif /* ToyGLmatrix_h */
