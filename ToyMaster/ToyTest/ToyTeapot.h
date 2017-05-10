//
//  ToyTeapot.h
//  Toy
//
//  Created by LongZhao on 2017/5/10.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyTeapot_h
#define ToyTeapot_h

#include <stdio.h>
#include <stdlib.h>
#include "../ToyComponents/ToyObject.h"
#include "../ToyMain/ToyMath/Toymath.h"
#include "ToyTeapotData.h"

class ToyTeapot : public ToyObject {
public:
    ToyTeapot();
    virtual ~ToyTeapot();
    
    void init(int grid, Toymat4 &transf);
    virtual void init();
    virtual void visit();
    virtual void render();
    
    void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
    void buildPatchReflect(int patchNum,
                           float *B, float *dB,
                           float *v, float *n, float *tc, unsigned int *el,
                           int &index, int &elIndex, int &tcIndex, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(Toyvec3 patch[][4],
                    float *B, float *dB,
                    float *v, float *n,float *, unsigned int *el,
                    int &index, int &elIndex, int &tcIndex, int grid, Toymat3 reflect, bool invertNormal);
    void getPatch(int patchNum, Toyvec3 patch[][4], bool reverseV);
    
    void computeBasisFunctions(float * B, float * dB, int grid);
    Toyvec3 evaluate(int gridU, int gridV, float *B, Toyvec3 patch[][4]);
    Toyvec3 evaluateNormal(int gridU, int gridV, float *B, float *dB, Toyvec3 patch[][4]);
    void moveLid(int grid, float *v, const Toymat4 &lidTransform);
    
protected:
    GLuint vboHandle[4];
    int faces;
};

#endif /* ToyTeapot_h */
