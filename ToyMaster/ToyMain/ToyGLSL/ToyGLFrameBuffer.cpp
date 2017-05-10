//
//  ToyGLFrameBuffer.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyGLFrameBuffer.h"

static ToyGLFrameBuffer s_frameBuffer;
ToyGLFrameBuffer *ToyGLFrameBuffer::sharedFrameBuffer() {
    return &s_frameBuffer;
}

ToyGLFrameBuffer::ToyGLFrameBuffer()
: colorBuffer(0)
, depthBuffer(0)
, frameBuffer(0) {
    
}

ToyGLFrameBuffer::~ToyGLFrameBuffer() {
    glDeleteRenderbuffers(1, &colorBuffer);
    glDeleteRenderbuffers(1, &depthBuffer);
    
    glDeleteFramebuffers(1, &frameBuffer);
}

void ToyGLFrameBuffer::setGLBuffer() {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    
    glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
}

void ToyGLFrameBuffer::setGLframeBuffer() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void ToyGLFrameBuffer::setGLcolorBuffer() {
    glGenRenderbuffers(1, &colorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
}

void ToyGLFrameBuffer::setGLdepthBuffer() {
    GLint width;
    GLint height;
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, width, height);
}

void ToyGLFrameBuffer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ToyGLFrameBuffer::setViewport(int x, int y, int w, int h) {
    glViewport(x, y, (GLsizei) w, (GLsizei) h);
}

void ToyGLFrameBuffer::setScissor(int x, int y, int w, int h) {
    glScissor(x, y, (GLsizei) w, (GLsizei) h);
}
