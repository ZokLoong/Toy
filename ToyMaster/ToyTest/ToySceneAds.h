//
//  ToySceneAds.h
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToySceneAds_h
#define ToySceneAds_h

#include <stdio.h>
#include "../ToyComponents/ToyObject.h"
#include "../ToyMain/ToyGLSL/ToyGLProgramCache.h"
#include "ToyTorus.h"
#include "ToyTeapot.h"

class ToySceneAds : public ToyObject {
public:
    static ToySceneAds *sharedScene();
    
    ToySceneAds();
    ~ToySceneAds();
    
    virtual void init();
    virtual void visit();
    virtual void render();
    
protected:
    ToyGLProgram *program;
    ToyTorus *torus;
    ToyTeapot *teapot;
};

#endif /* ToySceneAds_h */
