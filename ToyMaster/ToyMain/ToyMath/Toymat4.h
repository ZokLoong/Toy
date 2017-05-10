//
//  Toymat4.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toymat4_h
#define Toymat4_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Toyvec3;

typedef struct Toymat4 {
    float m[16];
} Toymat4;

#ifdef __cplusplus
extern "C" {
#endif
    
extern Toymat4 *Toymat4Fill(Toymat4 *matOut, const float *mat);
extern Toymat4 *Toymat4Identity(Toymat4 *matOut);
extern Toymat4 *Toymat4Transpose(Toymat4 *matOut, const Toymat4 *matIn);
extern Toymat4 *Toymat4Multiply(Toymat4 *matOut, const Toymat4 *matIn0, const Toymat4 *matIn1);
extern Toymat4 *Toymat4Rotatef(Toymat4 *matOut, const struct Toyvec3 *axis, const float degree);
extern Toymat4 *Toymat4Scalef(Toymat4 *matOut, const float sx, const float sy, const float sz);
extern Toymat4 *Toymat4Translatef(Toymat4 *matOut, const float tx, const float ty, const float tz);
extern Toymat4 *Toymat4Perspective(Toymat4 *matOut, float fovY, float aspect, float zNear, float zFar);
extern Toymat4 *Toymat4Ortho(Toymat4 *matOut, float left, float right, float bottom, float top, float near, float far);
extern Toymat4 *Toymat4LookAt(Toymat4 *matOut, const struct Toyvec3 *pEye, const struct Toyvec3 *pCenter, const struct Toyvec3 *pUp);
extern Toymat4 *Toymat4Assign(Toymat4 *matOut, const Toymat4 *matIn);
    
#ifdef __cplusplus
}
#endif

#endif /* Toymat4_h */
