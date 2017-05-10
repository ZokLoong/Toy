//
//  ToyDirector.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyDirector.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "ToyGLSL/ToyGLFrameBuffer.h"
#include "ToyMath/Toymath.h"

static ToyDirector s_director;
ToyDirector *ToyDirector::sharedDirector() {
    return &s_director;
}

ToyDirector::ToyDirector()
: mRootObj(0) {
    
}

ToyDirector::~ToyDirector() {
    
}

void ToyDirector::initGL() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    
    setProjection();
    
    dumpGL();
}

void ToyDirector::setProjection() {
    float zFar = sh/1.1566f/16;
    Toymat4 perspective, modelview;
    
    // Set prespective projection
    Toymat4Perspective(&perspective, 60, sw/sh, 0.1f, zFar * 2);
    ToyGLmatrixMode(TOY_GL_PROJECTION);
    ToyGLloadIdentity();
    ToyGLmatrixMul(&perspective);
    
    // Set modelview
    Toyvec3 eye, center, up;
    Toyvec3Fill(&eye, sw/2, sh/2, zFar);
    Toyvec3Fill(&center, sw/2, sh/2, 0.0f);
    Toyvec3Fill(&up, 0.0f, 1.0f, 0.0f);
    Toymat4LookAt(&modelview, &eye, &center, &up);
    
    ToyGLmatrixMode(TOY_GL_MODELVIEW);
    ToyGLloadIdentity();
    ToyGLmatrixMul(&modelview);
}

void ToyDirector::setFrameSize(float sw, float sh) {
    this->sw = sw;
    this->sh = sh;
}

void ToyDirector::dumpGL() {
    const GLubyte *render = glGetString(GL_RENDERER);
    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *version = glGetString(GL_VERSION);
    const GLubyte *glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("Toy: GL_RENDERER:                 %s\n", render);
    printf("Toy: GL_VENDOR:                   %s\n", vendor);
    printf("Toy: GL_VERSION:                  %s\n", version);
    printf("Toy: GL_SHADING_LANGUAGE_VERSION: %s\n", glsl);
    
    GLint param;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &param);
    printf("Toy: GL_MAX_TEXTURE_SIZE:         %d\n", param);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &param);
    printf("Toy: GL_MAX_TEXTURE_IMAGE_UNITS:  %d\n", param);
}

void ToyDirector::mainLoop() {
    ToyGLFrameBuffer::sharedFrameBuffer()->clear();
    
    if (mRootObj) {
        mRootObj->visit();
        
        mRootObj->render();
    }
    
    ToyGLFrameBuffer::sharedFrameBuffer()->swapBuffer();
}

void ToyDirector::pushRootObject(ToyObject *rootObj) {
    mRootObj = rootObj;
}
