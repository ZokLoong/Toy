//
//  ToyDirector.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyDirector_h
#define ToyDirector_h

#include <stdio.h>
#include "../ToyComponents/ToyObject.h"

class ToyDirector {
public:
    static ToyDirector *sharedDirector();
    
    ToyDirector();
    virtual ~ToyDirector();
    
    void initGL();
    void setProjection();
    void dumpGL();
    
    void setFrameSize(float sw, float sh);
    float getFrameWidth() { return sw; }
    float getFrameHeight() { return sh; }
    
    void mainLoop();
    
    void pushRootObject(ToyObject *rootObj);
    
protected:
    float sw;
    float sh;
    ToyObject *mRootObj;
};

#endif /* ToyDirector_h */
