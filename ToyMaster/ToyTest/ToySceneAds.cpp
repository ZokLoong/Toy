//
//  ToySceneAds.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToySceneAds.h"
#include "../ToyMain/ToyPlatform/ToyFileUtils.h"
#include "../ToyMain/ToyMath/Toymath.h"
#include "../ToyMain/ToyDirector.h"
#include "../ToyUtils/ToyMesh.h"

static ToySceneAds s_scene;
ToySceneAds *ToySceneAds::sharedScene() {
    return &s_scene;
}

ToySceneAds::ToySceneAds()
: program(0)
, teapot(0)
, torus(0) {
    
}

ToySceneAds::~ToySceneAds() {
    if (torus) {
        delete torus;
        torus = 0;
    }
    if (teapot) {
        delete teapot;
        teapot = 0;
    }
    if (monkey) {
        monkey = ToyObjFree(monkey);
    }
}

void ToySceneAds::init() {
//    std::string vertPath = ToyFileUtils::getHomeDir().append("/ToyShaders/ads.vert");
//    std::string fragPath = ToyFileUtils::getHomeDir().append("/ToyShaders/ads.frag");
//    std::string vertPath = ToyFileUtils::getHomeDir().append("/ToyShaders/adsfunc.vert");
//    std::string fragPath = ToyFileUtils::getHomeDir().append("/ToyShaders/adsfunc.frag");
    std::string vertPath = ToyFileUtils::getHomeDir().append("/ToyShaders/two_side_ads.vert");
    std::string fragPath = ToyFileUtils::getHomeDir().append("/ToyShaders/two_side_ads.frag");
    unsigned char *vertSource = ToyFileUtils::read(vertPath.c_str(), 0);
    unsigned char *fragSource = ToyFileUtils::read(fragPath.c_str(), 0);
    
    program = ToyGLProgramCache::sharedGLProgramCache()->createProgram("ads", (const GLchar *)vertSource, (const GLchar *)fragSource);
    if (program) {
        program->setAttribLocation("vertPosition", 0); // vertex position
        program->setAttribLocation("vertNormal", 1); // vertex normal
        
        program->link();
        
        // torus = new ToyTorus();
        // torus->init(2.5, 2.0f, 30, 30);
        
        /*
        Toymat4 transf;
        Toymat4Identity(&transf);
        Toymat4Translatef(&transf, 0.5f, 0.8f, 0.3f);
        teapot = new ToyTeapot();
        teapot->init(13, transf);*/
        
        monkey = ToyObjRead("ToyShaders/model.obj", ToyFileUtils::getHomeDir().c_str());
        ToyObjBuild(monkey);
    }
    if (program && program->isLinked()) {
        program->use();
        
        Toyvec3 lightPos;
        Toyvec3Fill(&lightPos, 500.0f, 500.0f, 500.0f);
        
        Toymat4 modelview;
        ToyGLmatrixMode(TOY_GL_MODELVIEW);
        ToyGLmatrixGet(&modelview);
        Toyvec3Transform(&lightPos, &lightPos, &modelview);
        
        program->setUniform("material.Kd", 0.9f, 0.5f, 0.3f);
        program->setUniform("light.Ld", 1.0f, 1.0f, 1.0f);
        program->setUniform("material.Ka", 0.9f, 0.5f, 0.3f);
        program->setUniform("light.La", 0.4f, 0.4f, 0.4f);
        program->setUniform("material.Ks", 0.8f, 0.8f, 0.8f);
        program->setUniform("light.Ls", 0.2f, 0.2f, 0.2f);
        program->setUniform("materials.shininess", 100.0f);
        
        program->setUniform("light.Position", lightPos.x, lightPos.y, lightPos.z);
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

void ToySceneAds::visit() {
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
        ToyGLscalef(9.0f, 9.0f, 9.0f);
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

void ToySceneAds::render() {
    if (torus) {
        torus->render();
    }
    if (teapot) {
        teapot->render();
    }
    if (monkey) {
        ToyObjDraw(monkey);
    }
}
