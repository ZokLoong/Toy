//
//  Toyvec2.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toyvec2.h"

Toyvec2 *Toyvec2Fill(Toyvec2 *vecOut, float x, float y) {
    vecOut->x = x;
    vecOut->y = y;
    return vecOut;
}

float Toyvec2Length(const Toyvec2 *vecIn) {
    return sqrtf(vecIn->x * vecIn->x + vecIn->y * vecIn->y);
}

float Toyvec2LengthSq(const Toyvec2 *vecIn) {
    return vecIn->x * vecIn->x + vecIn->y * vecIn->y;
}

Toyvec2 *Toyvec2Normalize(Toyvec2 *vecOut, const Toyvec2 *vecIn) {
    float l = 1.0f / Toyvec2Length(vecIn);
    vecOut->x = vecIn->x * l;
    vecOut->y = vecIn->y * l;
    
    return vecOut;
}

Toyvec2 *Toyvec2Add(Toyvec2 *vecOut, const Toyvec2 *vecIn0, const Toyvec2 *vecIn1) {
    vecOut->x = vecIn0->x + vecIn1->x;
    vecOut->y = vecIn0->y + vecIn1->y;
    
    return vecOut;
}

float Toyvec2Dot(const Toyvec2 *vecIn0, const Toyvec2 *vecIn1) {
    return vecIn0->x * vecIn1->x + vecIn0->y * vecIn1->y;
}

Toyvec2 *Toyvec2Sub(Toyvec2 *vecOut, const Toyvec2 *vecIn0, const Toyvec2 *vecIn1) {
    vecOut->x = vecIn0->x - vecIn1->x;
    vecOut->y = vecIn0->y - vecIn1->y;
    
    return vecOut;
}

Toyvec2 *Toyvec2Scalef(Toyvec2 *vecOut, const Toyvec2 *vecIn, const float s) {
    vecOut->x = vecIn->x * s;
    vecOut->y = vecIn->y * s;
    
    return vecOut;
}
