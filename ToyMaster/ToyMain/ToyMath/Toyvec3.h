//
//  Toyvec3.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toyvec3_h
#define Toyvec3_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Toymat4;
struct Toymat3;

typedef struct Toyvec3 {
    float x, y, z;
} Toyvec3;

#ifdef __cplusplus
extern "C" {
#endif
    
extern Toyvec3 *Toyvec3Fill(Toyvec3 *vecOut, float x, float y, float z);
extern float Toyvec3Length(const Toyvec3 *vecIn);
extern float Toyvec3LengthSq(const Toyvec3 *vecIn);
extern Toyvec3 *Toyvec3Normalize(Toyvec3 *vecOut, const Toyvec3 *vecIn);
extern Toyvec3 *Toyvec3Cross(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1);
extern float Toyvec3Dot(const Toyvec3 *vecIn0, const Toyvec3 *vecIn1);
extern Toyvec3 *Toyvec3Add(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1);
extern Toyvec3 *Toyvec3Sub(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1);
extern Toyvec3 *Toyvec3Transform(Toyvec3 *vecOut, const Toyvec3 *vecIn, const struct Toymat4 *matIn);
extern Toyvec3 *Toyvec3Scalef(Toyvec3 *vecOut, const Toyvec3 *vecIn, const float s);
extern Toyvec3 *Toyvec3Assign(Toyvec3 *vecOut, const Toyvec3 *vecIn);
extern Toyvec3 *Toyvec3MulMat3(Toyvec3 *vecOut, const Toyvec3 *vecIn, const struct Toymat3 *matIn);
extern Toyvec3 *Toyvec3Invese(Toyvec3 *vecOut, const Toyvec3 *vecIn);
    
#ifdef __cplusplus
}
#endif

#endif /* Toyvec3_h */
