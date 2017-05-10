//
//  Toymat3.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toymat3_h
#define Toymat3_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Toyvec3;

typedef struct Toymat3 {
    float m[9];
} Toymat3;

#ifdef __cplusplus
extern "C" {
#endif
    
extern Toymat3 *Toymat3Fill(Toymat3 *matOut, const float *mat);
extern Toymat3 *Toymat3Identity(Toymat3 *matOut);
extern Toymat3 *Toymat3Transpose(Toymat3 *matOut, const Toymat3 *matIn);
extern Toymat3 *Toymat3Multiply(Toymat3 *matOut, const Toymat3 *matIn0, const Toymat3 *matIn1);
extern Toymat3 *Toymat3Rotatef(Toymat3 *matOut, const float degree);
extern Toymat3 *Toymat3Scalef(Toymat3 *matOut, const float sx, const float sy);
extern Toymat3 *Toymat3Translatef(Toymat3 *matOut, const float tx, const float ty);
    
#ifdef __cplusplus
}
#endif

#endif /* Toymat3_h */
