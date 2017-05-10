//
//  ToyCube.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyCube_h
#define ToyCube_h

#include <stdio.h>
#include <stdlib.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "../ToyComponents/ToyObject.h"

class ToyCube : public ToyObject {
public:
    ToyCube();
    ToyCube(float side);
    virtual ~ToyCube();
    
    virtual void init();
    virtual void visit();
    virtual void render();
    
protected:
    float side;
    GLuint vboHandle[4];
};

#endif /* ToyCube_h */
