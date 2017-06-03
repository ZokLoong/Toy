//
//  ToyScenePreforated.h
//  Toy
//
//  Created by LongZhao on 2017/6/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyScenePreforated_h
#define ToyScenePreforated_h

#include <stdio.h>
#include "../ToyComponents/ToyObject.h"
#include "ToyTeapot.h"
#include "../ToyMain/ToyGLSL/ToyGLProgramCache.h"

class ToyScenePreforated : public ToyObject {
public:
    ToyScenePreforated();
    virtual ~ToyScenePreforated();
    
    static ToyScenePreforated *sharedScene();
    
    virtual void init();
    virtual void render();
    virtual void visit();
    
protected:
    ToyTeapot *teapot;
    ToyGLProgram *program;
};

#endif /* ToyScenePreforated_h */
