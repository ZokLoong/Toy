//
//  Toyvec2.h
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef Toyvec2_h
#define Toyvec2_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Toyvec2 {
    float x, y;
} Toyvec2;

#ifdef __cplusplus
extern "C" {
#endif
    
extern Toyvec2 *Toyvec2Fill(Toyvec2 *vecOut, float x, float y);
extern float Toyvec2Length(const Toyvec2 *vecIn);
extern float Toyvec2LengthSq(const Toyvec2 *vecIn);
extern Toyvec2 *Toyvec2Normalize(Toyvec2 *vecOut, const Toyvec2 *vecIn);
extern Toyvec2 *Toyvec2Add(Toyvec2 *vecOut, const Toyvec2 *vecIn0, const Toyvec2 *vecIn1);
extern float Toyvec2Dot(const Toyvec2 *vecIn0, const Toyvec2 *vecIn1);
extern Toyvec2 *Toyvec2Sub(Toyvec2 *vecOut, const Toyvec2 *vecIn0, const Toyvec2 *vecIn1);
extern Toyvec2 *Toyvec2Scalef(Toyvec2 *vecOut, const Toyvec2 *vecIn, const float s);
    
#ifdef __cplusplus
}
#endif

#endif /* Toyvec2_h */
