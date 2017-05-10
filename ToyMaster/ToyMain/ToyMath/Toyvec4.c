//
//  Toyvec4.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toyvec4.h"
#include "Toymat4.h"

Toyvec4 *Toyvec4Fill(Toyvec4 *vecOut, float x, float y, float z, float w) {
    vecOut->x = x;
    vecOut->y = y;
    vecOut->z = z;
    vecOut->w = w;
    return vecOut;
}

Toyvec4 *Toyvec4Add(Toyvec4 *vecOut, const Toyvec4 *vecIn0, const Toyvec4 *vecIn1) {
    vecOut->x = vecIn0->x + vecIn1->x;
    vecOut->y = vecIn0->y + vecIn1->y;
    vecOut->z = vecIn0->z + vecIn1->z;
    vecOut->w = vecIn0->w + vecIn1->w;
    
    return vecOut;
}

float Toyvec4Dot(const Toyvec4 *vecIn0, const Toyvec4 *vecIn1) {
    return vecIn0->x * vecIn1->x + vecIn0->y * vecIn1->y + vecIn0->z * vecIn1->z + vecIn0->w * vecIn1->w;
}

float Toyvec4Length(const Toyvec4 *vecIn) {
    return sqrtf(vecIn->x * vecIn->x + vecIn->y * vecIn->y + vecIn->z * vecIn->z + vecIn->w * vecIn->w);
}

float Toyvec4LengthSq(const Toyvec4 *vecIn) {
    return vecIn->x * vecIn->x + vecIn->y * vecIn->y + vecIn->z * vecIn->z + vecIn->w * vecIn->w;
}

Toyvec4 *Toyvec4Normalize(Toyvec4 *vecOut, const Toyvec4 *vecIn) {
    float l = 1.0f / Toyvec4Length(vecIn);
    vecOut->x = vecIn->x * l;
    vecOut->y = vecIn->y * l;
    vecOut->z = vecIn->z * l;
    vecOut->w = vecIn->w * l;
    
    return vecOut;
}

Toyvec4 *Toyvec4Scalef(Toyvec4 *vecOut, const Toyvec4 *vecIn, const float s) {
    vecOut->x = vecIn->x * s;
    vecOut->y = vecIn->y * s;
    vecOut->z = vecIn->z * s;
    vecOut->w = vecIn->w * s;
    
    return vecOut;
}

Toyvec4 *Toyvec4Sub(Toyvec4 *vecOut, const Toyvec4 *vecIn0, const Toyvec4 *vecIn1) {
    vecOut->x = vecIn0->x - vecIn1->x;
    vecOut->y = vecIn0->y - vecIn1->y;
    vecOut->z = vecIn0->z - vecIn1->z;
    vecOut->w = vecIn0->w - vecIn1->w;
    
    return vecOut;
}

Toyvec4 *Toyvec4Transform(Toyvec4 *vecOut, const Toyvec4 *vecIn, const Toymat4 *matIn) {
    Toyvec4 vec;
    vec.x = vecIn->x * matIn->m[0] + vecIn->y * matIn->m[4] + vecIn->z * matIn->m[8] + vecIn->w * matIn->m[12];
    vec.y = vecIn->x * matIn->m[1] + vecIn->y * matIn->m[5] + vecIn->z * matIn->m[9] + vecIn->w * matIn->m[13];
    vec.z = vecIn->x * matIn->m[2] + vecIn->y * matIn->m[6] + vecIn->z * matIn->m[10] + vecIn->w * matIn->m[14];
    vec.w = vecIn->x * matIn->m[3] + vecIn->y * matIn->m[7] + vecIn->z * matIn->m[11] + vecIn->w * matIn->m[15];
    
    vecOut->x = vec.x;
    vecOut->y = vec.y;
    vecOut->z = vec.z;
    vecOut->w = vec.w;
    
    return vecOut;
}
