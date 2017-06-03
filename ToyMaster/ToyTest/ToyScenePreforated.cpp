//
//  ToyScenePreforated.cpp
//  Toy
//
//  Created by LongZhao on 2017/6/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyScenePreforated.h"
#include "../ToyMain/ToyPlatform/ToyFileUtils.h"
#include "../ToyMain/ToyMath/Toymath.h"
#include "../ToyMain/ToyDirector.h"

static ToyScenePreforated inst;
ToyScenePreforated *ToyScenePreforated::sharedScene() {
    return &inst;
}

ToyScenePreforated::ToyScenePreforated()
: teapot(0) {
    
}

ToyScenePreforated::~ToyScenePreforated() {
    if (teapot) {
        delete teapot;
        teapot = 0;
    }
}

void ToyScenePreforated::init() {
    unsigned char *vert = ToyFileUtils::read(ToyFileUtils::getHomeDir().append("/ToyShaders/preforated.vert").c_str(), 0);
    unsigned char *frag = ToyFileUtils::read(ToyFileUtils::getHomeDir().append("/ToyShaders/preforated.frag").c_str(), 0);
    
    if (vert && frag) {
        program = ToyGLProgramCache::sharedGLProgramCache()->createProgram("preforated", (const GLchar *)vert, (const GLchar *)frag);
    }
    if (program) {
        program->setAttribLocation("vertPosition", 0); // vertex position
        program->setAttribLocation("vertNormal", 1); // vertex normal
        program->setAttribLocation("vertTexcoords", 2); // vertex texcoord
        
        program->link();
        
        Toymat4 transf;
        Toymat4Identity(&transf);
        Toymat4Translatef(&transf, 0.5f, 0.8f, 0.3f);
        teapot = new ToyTeapot();
        teapot->init(13, transf);
    }
    if (program && program->isLinked()) {
        program->use();
        
        Toyvec3 light;
        Toyvec3Fill(&light, 500.0f, 500.0f, 500.0f);
        
        Toymat4 modelview;
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixGet(&modelview);
        Toyvec3Transform(&light, &light, &modelview);
        
        program->setUniform("material.Kd", 0.9f, 0.5f, 0.3f);
        program->setUniform("light.Ld", 1.0f, 1.0f, 1.0f);
        program->setUniform("material.Ka", 0.9f, 0.5f, 0.3f);
        program->setUniform("light.La", 0.4f, 0.4f, 0.4f);
        program->setUniform("material.Ks", 0.8f, 0.8f, 0.8f);
        program->setUniform("light.Ls", 0.2f, 0.2f, 0.2f);
        program->setUniform("materials.shininess", 100.0f);
        
        program->setUniform("light.Position", light.x, light.y, light.z);
    }
    
    if (vert) {
        free(vert);
        vert = 0;
    }
    if (frag) {
        free(frag);
        frag = 0;
    }
}

void ToyScenePreforated::visit() {
    if (program && program->isLinked()) {
        program->use();
        
        static float degree = 0.0f;
        
        float sw = ToyDirector::sharedDirector()->getFrameWidth();
        float sh = ToyDirector::sharedDirector()->getFrameHeight();
        
        Toymat4 modelview, projection;
        Toymat3 normMat;
        
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixPush();
        ToyGLtranslatef(sw/2, sh/2, 0.0f);
        ToyGLrotatef(0.0f, 1.0f, 1.0f, degree);
        ToyGLrotatef(1.0f, 0.0f, 0.0f, -45);
        // ToyGLrotatef(0.0f, 0.0f, 1.0f, 90);
        ToyGLscalef(3.0f, 3.0f, 3.0f);
        ToyGLmatrixGet(&modelview);
        ToyGLmatrixPop();
        
        ToyGLmatrixMode(TOY_GL_PROJECTION);
        ToyGLmatrixGet(&projection);
        
        memcpy(&normMat.m[0], &modelview.m[0], sizeof(float) * 3);
        memcpy(&normMat.m[3], &modelview.m[4], sizeof(float) * 3);
        memcpy(&normMat.m[6], &modelview.m[8], sizeof(float) * 3);
        
        program->setUniform("normMat", &normMat);
        program->setUniform("modelview", &modelview);
        program->setUniform("projection", &projection);
        
        degree += 1.0f;
        degree = degree >= 360.0f ? 0.0f : degree;
    }
}

void ToyScenePreforated::render() {
    if (teapot) {
        teapot->render();
    }
}
