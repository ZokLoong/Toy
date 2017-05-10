//
//  Toyvec3.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toyvec3.h"
#include "Toymat4.h"
#include "Toymat3.h"

Toyvec3 *Toyvec3Fill(Toyvec3 *vecOut, float x, float y, float z) {
    vecOut->x = x;
    vecOut->y = y;
    vecOut->z = z;
    return vecOut;
}

float Toyvec3Length(const Toyvec3 *vecIn) {
    return sqrtf(vecIn->x * vecIn->x + vecIn->y * vecIn->y + vecIn->z * vecIn->z);
}

float Toyvec3LengthSq(const Toyvec3 *vecIn) {
    return vecIn->x * vecIn->x + vecIn->y * vecIn->y + vecIn->z * vecIn->z;
}

Toyvec3 *Toyvec3Normalize(Toyvec3 *vecOut, const Toyvec3 *vecIn) {
    float l = 1.0f / Toyvec3Length(vecIn);
    vecOut->x = vecIn->x * l;
    vecOut->y = vecIn->y * l;
    vecOut->z = vecIn->z * l;
    
    return vecOut;
}

Toyvec3 *Toyvec3Cross(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1) {
    Toyvec3 vec;
    vec.x = (vecIn0->y * vecIn1->z) - (vecIn0->z * vecIn1->y);
    vec.y = (vecIn0->z * vecIn1->x) - (vecIn0->x * vecIn1->z);
    vec.z = (vecIn0->x * vecIn1->y) - (vecIn0->y * vecIn1->x);
    
    vecOut->x = vec.x;
    vecOut->y = vec.y;
    vecOut->z = vec.z;
    
    return vecOut;
}

float Toyvec3Dot(const Toyvec3 *vecIn0, const Toyvec3 *vecIn1) {
    return vecIn0->x * vecIn1->x + vecIn0->y * vecIn1->y + vecIn0->z * vecIn1->z;
}

Toyvec3 *Toyvec3Add(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1) {
    vecOut->x = vecIn0->x + vecIn1->x;
    vecOut->y = vecIn0->y + vecIn1->y;
    vecOut->z = vecIn0->z + vecIn1->z;
    
    return vecOut;
}

Toyvec3 *Toyvec3Sub(Toyvec3 *vecOut, const Toyvec3 *vecIn0, const Toyvec3 *vecIn1) {
    vecOut->x = vecIn0->x - vecIn1->x;
    vecOut->y = vecIn0->y - vecIn1->y;
    vecOut->z = vecIn0->z - vecIn1->z;
    
    return vecOut;
}

Toyvec3 *Toyvec3Transform(Toyvec3 *vecOut, const Toyvec3 *vecIn, const Toymat4 *matIn) {
    Toyvec3 vec;
    vec.x = vecIn->x * matIn->m[0] + vecIn->y * matIn->m[4] + vecIn->z * matIn->m[8] + matIn->m[12];
    vec.y = vecIn->x * matIn->m[1] + vecIn->y * matIn->m[5] + vecIn->z * matIn->m[9] + matIn->m[13];
    vec.z = vecIn->x * matIn->m[2] + vecIn->y * matIn->m[6] + vecIn->z * matIn->m[10] + matIn->m[14];
    
    vecOut->x = vec.x;
    vecOut->y = vec.y;
    vecOut->z = vec.z;
    
    return vecOut;
}

Toyvec3 *Toyvec3MulMat3(Toyvec3 *vecOut, const Toyvec3 *vecIn, const Toymat3 *matIn) {
    Toyvec3 vec;
    vec.x = vecIn->x * matIn->m[0] + vecIn->y * matIn->m[3] + vecIn->z * matIn->m[6];
    vec.y = vecIn->x * matIn->m[1] + vecIn->y * matIn->m[4] + vecIn->z * matIn->m[7];
    vec.z = vecIn->x * matIn->m[2] + vecIn->y * matIn->m[5] + vecIn->z * matIn->m[8];
    
    vecOut->x = vec.x;
    vecOut->y = vec.y;
    vecOut->z = vec.z;
    
    return vecOut;
}

Toyvec3 *Toyvec3Scalef(Toyvec3 *vecOut, const Toyvec3 *vecIn, const float s) {
    vecOut->x = vecIn->x * s;
    vecOut->y = vecIn->y * s;
    vecOut->z = vecIn->z * s;
    
    return vecOut;
}

Toyvec3 *Toyvec3Assign(Toyvec3 *vecOut, const Toyvec3 *vecIn) {
    vecOut->x = vecIn->x;
    vecOut->y = vecIn->y;
    vecOut->z = vecIn->z;
    return vecOut;
}

Toyvec3 *Toyvec3Invese(Toyvec3 *vecOut, const Toyvec3 *vecIn) {
    vecOut->x = -vecIn->x;
    vecOut->y = -vecIn->y;
    vecOut->z = -vecIn->z;
    return vecOut;
}
