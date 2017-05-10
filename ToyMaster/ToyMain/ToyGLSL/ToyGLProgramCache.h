//
//  ToyGLProgramCache.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyGLProgramCache_h
#define ToyGLProgramCache_h

#include <stdio.h>
#include <iostream>
#include <map>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "ToyGLProgram.h"

typedef std::map< std::string, ToyGLProgram* > TOY_GL_PROGRAM_CACHE;

class ToyGLProgramCache {
public:
    static ToyGLProgramCache *sharedGLProgramCache();
    
    ToyGLProgramCache();
    virtual ~ToyGLProgramCache();
    
    ToyGLProgram *getProgram(const char *tag);
    ToyGLProgram *createProgram(const char *tag, const GLchar *vertSource, const GLchar *fragSource);
    
    void destroy();
    
protected:
    TOY_GL_PROGRAM_CACHE programs;
};

#endif /* ToyGLSLProgramCache_h */
