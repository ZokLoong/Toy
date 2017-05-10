//
//  ToyTorus.h
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyTorus_h
#define ToyTorus_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ToyComponents/ToyObject.h"

class ToyTorus : public ToyObject {
public:
    ToyTorus();
    virtual ~ToyTorus();
    
    virtual void init();
    virtual void init(float outerRadius, float innerRadius, int nsides, int nrings);
    virtual void visit();
    virtual void render();
    
protected:
    GLuint vboHandle[4];
    float outerRadius;
    float innerRadius;
    int sides;
    int rings;
    int faces;
    
    void generateVerts(float *verts, float *norms, float *tex, unsigned int *el, float outerRadius, float innerRadius);
};

#endif /* ToyTorus_h */
