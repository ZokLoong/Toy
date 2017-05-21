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
#include "../ToyUtils/ToyMesh.h"

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
    ToyObj *monkey;
};

#endif /* ToySceneAds_h */
