//
//  ToyGLProgramCache.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyGLProgramCache.h"

static ToyGLProgramCache s_programcache;
ToyGLProgramCache *ToyGLProgramCache::sharedGLProgramCache() {
    return &s_programcache;
}

ToyGLProgramCache::ToyGLProgramCache() {
    programs.clear();
}

ToyGLProgramCache::~ToyGLProgramCache() {
    destroy();
}

ToyGLProgram *ToyGLProgramCache::getProgram(const char *tag) {
    TOY_GL_PROGRAM_CACHE::iterator iter = programs.find(tag);
    if (iter != programs.end()) {
        return iter->second;
    }
    return 0;
}

ToyGLProgram *ToyGLProgramCache::createProgram(const char *tag, const GLchar *vertSource, const GLchar *fragSource) {
    ToyGLProgram *program = getProgram(tag);
    if (program) {
        printf("Waring: GLSL Program Tag: '%s' was already exist!\n", tag);
        return program;
    }
    program = new ToyGLProgram();
    program->attachShader(vertSource, fragSource);
    // program->use();
    
    programs[tag] = program;
    
    return program;
}

void ToyGLProgramCache::destroy() {
    TOY_GL_PROGRAM_CACHE::iterator iter = programs.begin();
    for ( ; iter != programs.end(); ) {
        if (iter->second) {
            delete iter->second;
            iter->second = 0;
        }
        programs.erase(iter++);
    }
    programs.clear();
}
