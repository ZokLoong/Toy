//
//  ToyTeapot.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/10.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyTeapot.h"

ToyTeapot::ToyTeapot() {
    
}

ToyTeapot::~ToyTeapot() {
    
}

void ToyTeapot::init() {
    
}

void ToyTeapot::init(int grid, Toymat4 &lidTransform) {
    int verts = 32 * (grid + 1) * (grid + 1);
    faces = grid * grid * 32;
    
    float *v = (float *)malloc(verts * 3 * sizeof(float));
    float *n = (float *)malloc(verts * 3 * sizeof(float));
    float *tex = (float *)malloc(verts * 2 * sizeof(float));
    unsigned int *el = (unsigned int *)malloc(sizeof(unsigned int) * faces * 6);
    
    generatePatches(v, n, tex, el, grid);
    moveLid(grid, v, lidTransform);
    
    glGenBuffers(4, vboHandle);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]); // vertex
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * 3, v, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]); // normal
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * 3, n, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]); // tex
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * 2, tex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]); // elements
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faces * 6, el, GL_STATIC_DRAW);
    
    free(v);
    free(n);
    free(tex);
    free(el);
    
    glGenVertexArraysOES(1, &vaoHandle);
    glBindVertexArrayOES(vaoHandle);
    
    glEnableVertexAttribArray(0); // vertex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1); // normal
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(2); // texture
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]); // elements
    
    glBindVertexArrayOES(0);
}

void ToyTeapot::visit() {
    
}

void ToyTeapot::render() {
    glBindVertexArrayOES(vaoHandle);
    glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, 0);
}

void ToyTeapot::generatePatches(float * v, float * n, float * tc, unsigned int* el, int grid) {
    float * B = new float[4*(grid+1)];  // Pre-computed Bernstein basis functions
    float * dB = new float[4*(grid+1)]; // Pre-computed derivitives of basis functions
    
    int idx = 0, elIndex = 0, tcIndex = 0;
    
    // Pre-compute the basis functions  (Bernstein polynomials)
    // and their derivatives
    computeBasisFunctions(B, dB, grid);
    
    // Build each patch
    // The rim
    buildPatchReflect(0, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The body
    buildPatchReflect(1, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(2, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The lid
    buildPatchReflect(3, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(4, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The bottom
    buildPatchReflect(5, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The handle
    buildPatchReflect(6, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(7, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    // The spout
    buildPatchReflect(8, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(9, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    
    delete [] B;
    delete [] dB;
}

void ToyTeapot::moveLid(int grid, float *v, const Toymat4 &lidTransform) {
    
    int start = 3 * 12 * (grid+1) * (grid+1);
    int end = 3 * 20 * (grid+1) * (grid+1);
    
    for (int i = start; i < end; i+=3) {
        Toyvec4 vert;
        Toyvec4Fill(&vert, v[i], v[i+1], v[i+2], 1.0f);
        Toyvec4Transform(&vert, &vert, &lidTransform);
        v[i] = vert.x;
        v[i+1] = vert.y;
        v[i+2] = vert.z;
    }
}

void ToyTeapot::buildPatchReflect(int patchNum,
                                  float *B, float *dB,
                                  float *v, float *n,
                                  float *tc, unsigned int *el,
                                  int &index, int &elIndex, int &tcIndex, int grid,
                                  bool reflectX, bool reflectY) {
    Toyvec3 patch[4][4];
    Toyvec3 patchRevV[4][4];
    getPatch(patchNum, patch, false);
    getPatch(patchNum, patchRevV, true);
    
    // Patch without modification
    Toymat3 mat;
    Toymat3Identity(&mat);
    buildPatch(patch, B, dB, v, n, tc, el,
               index, elIndex, tcIndex, grid, mat, true);
    
    // Patch reflected in x
    if( reflectX ) {
        float m[] = { -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        Toymat3Fill(&mat, m);
        buildPatch(patchRevV, B, dB, v, n, tc, el,
                   index, elIndex, tcIndex, grid, mat, false );
    }
    
    // Patch reflected in y
    if( reflectY ) {
        float m[] = { 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        Toymat3Fill(&mat, m);
        buildPatch(patchRevV, B, dB, v, n, tc, el,
                   index, elIndex, tcIndex, grid, mat, false );
    }
    
    // Patch reflected in x and y
    if( reflectX && reflectY ) {
        float m[] = { -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        Toymat3Fill(&mat, m);
        buildPatch(patch, B, dB, v, n, tc, el,
                   index, elIndex, tcIndex, grid, mat, true );
    }
}

void ToyTeapot::buildPatch(Toyvec3 patch[][4],
                           float *B, float *dB,
                           float *v, float *n, float *tc,
                           unsigned int *el,
                           int &index, int &elIndex, int &tcIndex, int grid, Toymat3 reflect,
                           bool invertNormal) {
    int startIndex = index / 3;
    float tcFactor = 1.0f / grid;
    
    for (int i = 0; i <= grid; i++) {
        for (int j = 0 ; j <= grid; j++) {
            Toyvec3 pt = evaluate(i,j,B,patch);
            Toyvec3MulMat3(&pt, &pt, &reflect);
            Toyvec3 norm = evaluateNormal(i,j,B,dB,patch);
            Toyvec3MulMat3(&norm, &norm, &reflect);
            
            if (invertNormal)
                Toyvec3Invese(&norm, &norm);
            
            v[index] = pt.x;
            v[index+1] = pt.y;
            v[index+2] = pt.z;
            
            n[index] = norm.x;
            n[index+1] = norm.y;
            n[index+2] = norm.z;
            
            tc[tcIndex] = i * tcFactor;
            tc[tcIndex+1] = j * tcFactor;
            
            index += 3;
            tcIndex += 2;
        }
    }
    
    for (int i = 0; i < grid; i++) {
        int iStart = i * (grid+1) + startIndex;
        int nextiStart = (i+1) * (grid+1) + startIndex;
        for (int j = 0; j < grid; j++) {
            el[elIndex] = iStart + j;
            el[elIndex+1] = nextiStart + j + 1;
            el[elIndex+2] = nextiStart + j;
            
            el[elIndex+3] = iStart + j;
            el[elIndex+4] = iStart + j + 1;
            el[elIndex+5] = nextiStart + j + 1;
            
            elIndex += 6;
        }
    }
}

void ToyTeapot::getPatch(int patchNum, Toyvec3 patch[][4], bool reverseV) {
    for (int u = 0; u < 4; u++) {          // Loop in u direction
        for (int v = 0; v < 4; v++) {     // Loop in v direction
            if (reverseV) {
                Toyvec3Fill(&patch[u][v],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+(3-v)]][0],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+(3-v)]][1],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+(3-v)]][2]);
            } else {
                Toyvec3Fill(&patch[u][v],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+v]][0],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+v]][1],
                            ToyTeapotNS::cpdata[ToyTeapotNS::patchdata[patchNum][u*4+v]][2]);
            }
        }
    }
}

void ToyTeapot::computeBasisFunctions(float * B, float * dB, int grid) {
    float inc = 1.0f / grid;
    for (int i = 0; i <= grid; i++) {
        float t = i * inc;
        float tSqr = t * t;
        float oneMinusT = (1.0f - t);
        float oneMinusT2 = oneMinusT * oneMinusT;
        
        B[i*4 + 0] = oneMinusT * oneMinusT2;
        B[i*4 + 1] = 3.0f * oneMinusT2 * t;
        B[i*4 + 2] = 3.0f * oneMinusT * tSqr;
        B[i*4 + 3] = t * tSqr;
        
        dB[i*4 + 0] = -3.0f * oneMinusT2;
        dB[i*4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
        dB[i*4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
        dB[i*4 + 3] = 3.0f * tSqr;
    }
}


Toyvec3 ToyTeapot::evaluate(int gridU, int gridV, float *B, Toyvec3 patch[][4]) {
    Toyvec3 p;
    Toyvec3Fill(&p, 0.0f, 0.0f, 0.0f);
    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < 4; j++) {
            Toyvec3 t;
            Toyvec3Scalef(&t, &patch[i][j], B[gridU*4+i] * B[gridV*4+j]);
            Toyvec3Add(&p, &p, &t);
        }
    }
    return p;
}

Toyvec3 ToyTeapot::evaluateNormal(int gridU, int gridV, float *B, float *dB, Toyvec3 patch[][4]) {
    Toyvec3 du;
    Toyvec3Fill(&du, 0.0f,0.0f,0.0f);
    Toyvec3 dv;
    Toyvec3Fill(&dv, 0.0f,0.0f,0.0f);
    
    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < 4; j++) {
            Toyvec3 t;
            
            Toyvec3Scalef(&t, &patch[i][j], dB[gridU*4+i] * B[gridV*4+j]);
            Toyvec3Add(&du, &du, &t);
            
            Toyvec3Scalef(&t, &patch[i][j], B[gridU*4+i] * dB[gridV*4+j]);
            Toyvec3Add(&dv, &dv, &t);
        }
    }
    
    Toyvec3 norm;
    Toyvec3Cross(&norm, &du, &dv);
    Toyvec3Normalize(&norm, &norm);
    
    return norm;
}
