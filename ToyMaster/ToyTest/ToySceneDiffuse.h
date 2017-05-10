//
//  ToySceneDiffuse.h
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToySceneDiffuse_h
#define ToySceneDiffuse_h

#include <stdio.h>
#include <iostream>
#include "../ToyComponents/ToyObject.h"
#include "../ToyMain/ToyGLSL/ToyGLProgramCache.h"
#include "ToyCube.h"
#include "ToyTorus.h"
#include "ToyTeapot.h"

class ToySceneDiffuse :public ToyObject {
public:
    static ToySceneDiffuse *sharedScene();
    
    ToySceneDiffuse();
    virtual ~ToySceneDiffuse();
    
    virtual void init();
    virtual void visit();
    virtual void render();
    
protected:
    ToyGLProgram *program;
    ToyCube *cube;
    ToyTorus *torus;
    ToyTeapot *teapot;
};

#endif /* ToySceneDiffuse_h */
