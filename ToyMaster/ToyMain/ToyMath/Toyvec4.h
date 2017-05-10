//
//  Toyvec4.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toyvec4_h
#define Toyvec4_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Toymat4;

typedef struct Toyvec4 {
    float x, y, z, w;
} Toyvec4;

#ifdef __cplusplus
extern "C" {
#endif
    
extern Toyvec4 *Toyvec4Fill(Toyvec4 *vecOut, float x, float y, float z, float w);
extern Toyvec4 *Toyvec4Add(Toyvec4 *vecOut, const Toyvec4 *vecIn0, const Toyvec4 *vecIn1);
extern float Toyvec4Dot(const Toyvec4 *vecIn0, const Toyvec4 *vecIn1);
extern float Toyvec4Length(const Toyvec4 *vecIn);
extern float Toyvec4LengthSq(const Toyvec4 *vecIn);
extern Toyvec4 *Toyvec4Normalize(Toyvec4 *vecOut, const Toyvec4 *vecIn);
extern Toyvec4 *Toyvec4Scalef(Toyvec4 *vecOut, const Toyvec4 *vecIn, const float s);
extern Toyvec4 *Toyvec4Sub(Toyvec4 *vecOut, const Toyvec4 *vecIn0, const Toyvec4 *vecIn1);
extern Toyvec4 *Toyvec4Transform(Toyvec4 *vecOut, const Toyvec4 *vecIn, const struct Toymat4 *matIn);
    
#ifdef __cplusplus
}
#endif

#endif /* Toyvec4_h */
