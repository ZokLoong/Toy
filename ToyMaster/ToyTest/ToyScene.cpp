//
//  ToyScene.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyScene.h"
#include "../ToyMain/ToyMath/Toymath.h"

static ToyScene s_scene;
ToyScene *ToyScene::sharedScene() {
    return &s_scene;
}

ToyScene::ToyScene()
: program(0) {
    
}

ToyScene::~ToyScene() {
    
}

void ToyScene::init() {
    initTriangle();
}

void ToyScene::visit() {
    visitTriangle();
}

void ToyScene::render() {
    drawTriangle();
}

void ToyScene::initTriangle() {
    std::string vertPath = ToyFileUtils::getHomeDir().append("/ToyShaders/basic.vert");
    std::string fragPath = ToyFileUtils::getHomeDir().append("/ToyShaders/basic.frag");
    unsigned char *vertSource = ToyFileUtils::read(vertPath.c_str(), 0);
    unsigned char *fragSource = ToyFileUtils::read(fragPath.c_str(), 0);
    
    program = ToyGLProgramCache::sharedGLProgramCache()->createProgram("basic", (const char *)vertSource, (const char *)fragSource);
    if (program) {
        program->setAttribLocation("vertPosition", 0);
        program->setAttribLocation("vertColor", 1);
        
        program->link();
        
        float vertPos[] = {
            100.0f, 100.0f, 0.0f,
            150.0f, 150.0f, 0.0f,
            200.0f, 100.0f, 0.0f,
        };
        float color[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        };
        
        GLuint vboHandle[2];
        glGenBuffers(2, vboHandle);
        
        glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertPos), vertPos, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
        
        glGenVertexArraysOES(1, &vaoHandle);
        glBindVertexArrayOES(vaoHandle);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    if (program && program->isLinked()) {
        program->use();
    }
    
    if (vertSource) {
        free(vertSource);
    }
    if (fragSource) {
        free(fragSource);
    }
}

void ToyScene::drawTriangle() {
    glEnableVertexAttribArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ToyScene::visitTriangle() {
    if (program && program->isLinked()) {
        program->use();
        
        Toymat4 modelview, projection;
        
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixGet(&modelview);
        
        ToyGLmatrixMode(TOY_GL_PROJECTION);
        ToyGLmatrixGet(&projection);
        
        program->setUniform("modelview", &modelview);
        program->setUniform("projection", &projection);
    }
}
