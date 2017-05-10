//
//  ToyScene.h
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyScene_h
#define ToyScene_h

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "../ToyMain/ToyPlatform/ToyFileUtils.h"
#include "../ToyComponents/ToyObject.h"
#include "../ToyMain/ToyGLSL/ToyGLProgramCache.h"
#include "ToyCube.h"

class ToyScene: public ToyObject {
public:
    static ToyScene *sharedScene();
    
    ToyScene();
    virtual ~ToyScene();
    
    virtual void init();
    virtual void visit();
    virtual void render();
    
protected:
    ToyGLProgram *program;
    
    // First test single triangle
    virtual void initTriangle();
    virtual void drawTriangle();
    virtual void visitTriangle();
};

#endif /* ToyScene_h */
