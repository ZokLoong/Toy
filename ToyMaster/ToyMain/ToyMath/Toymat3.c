//
//  Toymat3.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toymat3.h"
#include "Toyvec3.h"
#include "Toymathcommon.h"

Toymat3 *Toymat3Fill(Toymat3 *matOut, const float *mat) {
    memcpy(matOut->m, mat, sizeof(float) * 9);
    return matOut;
}

Toymat3 *Toymat3Identity(Toymat3 *matOut) {
    memset(matOut->m, 0, sizeof(float) * 9);
    matOut->m[0] = matOut->m[4] = matOut->m[8] = 1.0f;
    return matOut;
}

Toymat3 *Toymat3Transpose(Toymat3 *matOut, const Toymat3 *matIn) {
    int z, x;
    for (z = 0; z < 3; ++z)
        for (x = 0; x < 3; ++x)
            matOut->m[(z * 3) + x] = matIn->m[(x * 3) + z];
    return matOut;
}

Toymat3 *Toymat3Multiply(Toymat3 *matOut, const Toymat3 *matIn0, const Toymat3 *matIn1) {
    float m[9];
    const float *m1 = matIn0->m, *m2 = matIn1->m;
    
    m[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
    m[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
    m[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];
    
    m[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
    m[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
    m[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];
    
    m[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
    m[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
    m[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];
    
    memcpy(matOut->m, m, sizeof(float)*9);
    
    return matOut;
}

Toymat3 *Toymat3Rotatef(Toymat3 *matOut, const float degree) {
    float radians = DEGREE_TO_RADIAN(degree);
    
    matOut->m[0] = cosf(radians);
    matOut->m[1] = sinf(radians);
    matOut->m[2] = 0.0f;
    
    matOut->m[3] = -sinf(radians);;
    matOut->m[4] = cosf(radians);
    matOut->m[5] = 0.0f;
    
    matOut->m[6] = 0.0f;
    matOut->m[7] = 0.0f;
    matOut->m[8] = 1.0f;
    
    return matOut;
}

Toymat3 *Toymat3Scalef(Toymat3 *matOut, const float sx, const float sy) {
    Toymat3Identity(matOut);
    matOut->m[0] = sx;
    matOut->m[4] = sy;
    return matOut;
}

Toymat3 *Toymat3Translatef(Toymat3 *matOut, const float tx, const float ty) {
    Toymat3Identity(matOut);
    matOut->m[6] = tx;
    matOut->m[7] = ty;
    return matOut;
}
