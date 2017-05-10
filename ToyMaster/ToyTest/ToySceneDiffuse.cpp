//
//  ToySceneDiffuse.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToySceneDiffuse.h"
#include "../ToyMain/ToyPlatform/ToyFileUtils.h"
#include "../ToyMain/ToyMath/Toymath.h"
#include "../ToyMain/ToyDirector.h"

static ToySceneDiffuse s_scene;
ToySceneDiffuse *ToySceneDiffuse::sharedScene() {
    return &s_scene;
}

ToySceneDiffuse::ToySceneDiffuse()
: cube(0)
, teapot(0)
, torus(0) {
    
}

ToySceneDiffuse::~ToySceneDiffuse() {
    if (cube) {
        delete cube;
        cube = 0;
    }
    if (torus) {
        delete torus;
        torus = 0;
    }
    if (teapot) {
        delete teapot;
        teapot = 0;
    }
}

void ToySceneDiffuse::init() {
    std::string vertPath = ToyFileUtils::getHomeDir().append("/ToyShaders/diffuse.vert");
    std::string fragPath = ToyFileUtils::getHomeDir().append("/ToyShaders/diffuse.frag");
    unsigned char *vertSource = ToyFileUtils::read(vertPath.c_str(), 0);
    unsigned char *fragSource = ToyFileUtils::read(fragPath.c_str(), 0);
    
    program = ToyGLProgramCache::sharedGLProgramCache()->createProgram("diffuse", (const GLchar *)vertSource, (const GLchar *)fragSource);
    if (program) {
        program->setAttribLocation("vertPosition", 0);
        program->setAttribLocation("vertNorm", 1);
        
        program->link();
        
        // cube = new ToyCube(100.0f);
        // cube->init();
        // torus = new ToyTorus();
        // torus->init(3.2f, 2.2f, 30, 30);
        
        Toymat4 transf;
        Toymat4Identity(&transf);
        Toymat4Translatef(&transf, 0.5f, 0.8f, 0.3f);
        teapot = new ToyTeapot();
        teapot->init(13, transf);
    }
    if (program && program->isLinked()) {
        program->use();
        
        Toyvec3 lightPos;
        Toyvec3Fill(&lightPos, 500.0f, 500.0f, 500.0f);
        
        Toymat4 modelview;
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixGet(&modelview);
        Toyvec3Transform(&lightPos, &lightPos, &modelview);
        
        // L = Ld * Kd * Dot(s, n)
        program->setUniform("lightPosition", lightPos.x, lightPos.y, lightPos.z); // Set light position
        program->setUniform("Kd", 0.9f, 0.5f, 0.3f); // Set refleact factor of light
        program->setUniform("Ld", 1.0f, 1.0f, 1.0f); // Set light intensity
    }
    
    if (vertSource) {
        free(vertSource);
        vertSource = 0;
    }
    if (fragSource) {
        free(fragSource);
        fragSource = 0;
    }
}

void ToySceneDiffuse::visit() {
    if (program && program->isLinked()) {
        program->use();
        
        static float degree = 0.0f;
        
        Toymat4 modelview, projection;
        Toymat3 normMat;
        
        float sw = ToyDirector::sharedDirector()->getFrameWidth();
        float sh = ToyDirector::sharedDirector()->getFrameHeight();
        
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixPush();
        ToyGLtranslatef(sw/2, sh/2 - 12, 0.0f);
        ToyGLrotatef(0.0f, 1.0f, 1.0f, degree);
        ToyGLrotatef(1.0f, 0.0f, 0.0f, -45);
        // ToyGLrotatef(0.0f, 0.0f, 1.0f, 90);
        ToyGLscalef(3.0f, 3.0f, 3.0f);
        ToyGLmatrixGet(&modelview);
        ToyGLmatrixPop();
        
        memcpy(&normMat.m[0], &modelview.m[0], sizeof(float) * 3);
        memcpy(&normMat.m[3], &modelview.m[4], sizeof(float) * 3);
        memcpy(&normMat.m[6], &modelview.m[8], sizeof(float) * 3);
        
        ToyGLmatrixMode(TOY_GL_PROJECTION);
        ToyGLmatrixGet(&projection);
        
        program->setUniform("normMat", &normMat);
        program->setUniform("modelview", &modelview);
        program->setUniform("projection", &projection);
        
        degree += 1.0f;
        degree = degree >= 360.0f ? 0.0f : degree;
    }
}

void ToySceneDiffuse::render() {
    if (cube) {
        cube->render();
    }
    if (torus) {
        torus->render();
    }
    if (teapot) {
        teapot->render();
    }
}
