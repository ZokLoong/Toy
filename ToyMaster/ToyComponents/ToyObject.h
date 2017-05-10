//
//  ToyObject.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyObject_h
#define ToyObject_h

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

class ToyObject {
public:
    ToyObject();
    virtual ~ToyObject();
    
    virtual void init() = 0;
    virtual void visit() = 0;
    virtual void render() = 0;
    
protected:
    GLuint vaoHandle;
};

#endif /* ToyObject_h */
