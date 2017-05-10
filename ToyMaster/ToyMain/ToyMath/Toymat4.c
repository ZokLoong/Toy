//
//  Toymat4.c
//  Toy
//
//  Created by LongZhao on 2017/4/29.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "Toymat4.h"
#include "Toyvec3.h"
#include "Toymathcommon.h"

Toymat4 *Toymat4Fill(Toymat4 *matOut, const float *mat) {
    memcpy(matOut->m, mat, sizeof(float)*16);
    return matOut;
}

Toymat4 *Toymat4Identity(Toymat4 *matOut) {
    memset(matOut->m, 0, sizeof(float)*16);
    matOut->m[0] = matOut->m[5] = matOut->m[10] = matOut->m[15] = 1.0f;
    return matOut;
}

Toymat4 *Toymat4Transpose(Toymat4 *matOut, const Toymat4 *matIn) {
    int x, z;
    for (z = 0; z < 4; ++z)
        for (x = 0; x < 4; ++x)
            matOut->m[(z * 4) + x] = matIn->m[(x * 4) + z];
    return matOut;
}

Toymat4 *Toymat4Multiply(Toymat4 *matOut, const Toymat4 *matIn0, const Toymat4 *matIn1) {
    float mat[16];
    
    const float *m1 = matIn0->m, *m2 = matIn1->m;
    
    mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
    mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
    mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];
    
    mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
    mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
    mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];
    
    mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
    mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
    mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];
    
    mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
    mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
    mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
    
    memcpy(matOut->m, mat, sizeof(mat));
    return matOut;
}

Toymat4 *Toymat4Rotatef(Toymat4 *matOut, const Toyvec3 *axis, const float degree) {
    float radians = DEGREE_TO_RADIAN(degree);
    
    float rcos = cosf(radians);
    float rsin = sinf(radians);
    
    Toyvec3 normalizedAxis;
    Toyvec3Normalize(&normalizedAxis, axis);
    
    matOut->m[0] = rcos + normalizedAxis.x * normalizedAxis.x * (1 - rcos);
    matOut->m[1] = normalizedAxis.z * rsin + normalizedAxis.y * normalizedAxis.x * (1 - rcos);
    matOut->m[2] = -normalizedAxis.y * rsin + normalizedAxis.z * normalizedAxis.x * (1 - rcos);
    matOut->m[3] = 0.0f;
    
    matOut->m[4] = -normalizedAxis.z * rsin + normalizedAxis.x * normalizedAxis.y * (1 - rcos);
    matOut->m[5] = rcos + normalizedAxis.y * normalizedAxis.y * (1 - rcos);
    matOut->m[6] = normalizedAxis.x * rsin + normalizedAxis.z * normalizedAxis.y * (1 - rcos);
    matOut->m[7] = 0.0f;
    
    matOut->m[8] = normalizedAxis.y * rsin + normalizedAxis.x * normalizedAxis.z * (1 - rcos);
    matOut->m[9] = -normalizedAxis.x * rsin + normalizedAxis.y * normalizedAxis.z * (1 - rcos);
    matOut->m[10] = rcos + normalizedAxis.z * normalizedAxis.z * (1 - rcos);
    matOut->m[11] = 0.0f;
    
    matOut->m[12] = 0.0f;
    matOut->m[13] = 0.0f;
    matOut->m[14] = 0.0f;
    matOut->m[15] = 1.0f;
    
    return matOut;
}

Toymat4 *Toymat4Scalef(Toymat4 *matOut, const float sx, const float sy, const float sz) {
    memset(matOut->m, 0, sizeof(float) * 16);
    matOut->m[0] = sx;
    matOut->m[5] = sy;
    matOut->m[10] = sz;
    matOut->m[15] = 1.0f;
    return matOut;
}

Toymat4 *Toymat4Translatef(Toymat4 *matOut, const float tx, const float ty, const float tz) {
    memset(matOut->m, 0, sizeof(float) * 16);
    
    matOut->m[0] = 1.0f;
    matOut->m[5] = 1.0f;
    matOut->m[10] = 1.0f;
    
    matOut->m[12] = tx;
    matOut->m[13] = ty;
    matOut->m[14] = tz;
    matOut->m[15] = 1.0f;
    
    return matOut;
}

Toymat4 *Toymat4Perspective(Toymat4 *matOut, float fovY, float aspect, float zNear, float zFar) {
    float r = DEGREE_TO_RADIAN(fovY / 2);
    float deltaZ = zFar - zNear;
    float s = sin(r);
    float cotangent = 0;
    
    if (deltaZ == 0 || s == 0 || aspect == 0) {
        return NULL;
    }
    
    //cos(r) / sin(r) = cot(r)
    cotangent = cos(r) / s;
    
    Toymat4Identity(matOut);
    matOut->m[0] = cotangent / aspect;
    matOut->m[5] = cotangent;
    matOut->m[10] = -(zFar + zNear) / deltaZ;
    matOut->m[11] = -1;
    matOut->m[14] = -2 * zNear * zFar / deltaZ;
    matOut->m[15] = 0;
    
    return matOut;
}

Toymat4 *Toymat4Ortho(Toymat4 *matOut, float left, float right, float bottom, float top, float near, float far) {
    float tx = -((right + left) / (right - left));
    float ty = -((top + bottom) / (top - bottom));
    float tz = -((far + near) / (far - near));
    
    Toymat4Identity(matOut);
    matOut->m[0] = 2 / (right - left);
    matOut->m[5] = 2 / (top - bottom);
    matOut->m[10] = -2 / (far - near);
    matOut->m[12] = tx;
    matOut->m[13] = ty;
    matOut->m[14] = tz;
    
    return matOut;
}

Toymat4 *Toymat4LookAt(Toymat4 *matOut, const Toyvec3 *pEye, const Toyvec3 *pCenter, const Toyvec3 *pUp) {
    Toyvec3 f, up, s, u;
    Toymat4 translate;
    
    Toyvec3Sub(&f, pCenter, pEye);
    Toyvec3Normalize(&f, &f);
    
    Toyvec3Assign(&up, pUp);
    Toyvec3Normalize(&up, &up);
    
    Toyvec3Cross(&s, &f, &up);
    Toyvec3Normalize(&s, &s);
    
    Toyvec3Cross(&u, &s, &f);
    Toyvec3Normalize(&s, &s);
    
    Toymat4Identity(matOut);
    
    matOut->m[0] = s.x;
    matOut->m[4] = s.y;
    matOut->m[8] = s.z;
    
    matOut->m[1] = u.x;
    matOut->m[5] = u.y;
    matOut->m[9] = u.z;
    
    matOut->m[2] = -f.x;
    matOut->m[6] = -f.y;
    matOut->m[10] = -f.z;
    
    Toymat4Translatef(&translate, -pEye->x, -pEye->y, -pEye->z);
    Toymat4Multiply(matOut, matOut, &translate);
    
    return matOut;
}

Toymat4 *Toymat4Assign(Toymat4 *matOut, const Toymat4 *matIn) {
    memcpy(matOut->m, matIn->m, sizeof(float)*16);
    return matOut;
}
