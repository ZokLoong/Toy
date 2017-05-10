//
//  ToyCamera.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyCamera.h"
#include "ToyMath/Toyvec3.h"
#include "ToyMath/Toymat4.h"

ToyCamera::ToyCamera()
: position(0) {
    
}

ToyCamera::~ToyCamera() {
    if (position) {
        free(position);
        position = 0;
    }
}

void ToyCamera::setFOVy(const float fovy) {
    FOVy = fovy;
}

float ToyCamera::getFOVy() {
    return FOVy;
}

void ToyCamera::setAspectRatio(const float ratio) {
    aspect = ratio;
}

float ToyCamera::getAspectRatio() {
    return aspect;
}

void ToyCamera::setNearDist(const float nearDist) {
    this->nearDist = nearDist;
}

float ToyCamera::getNearDist() {
    return nearDist;
}

void ToyCamera::setFarDist(const float farDist) {
    this->farDist = farDist;
}

float ToyCamera::getFarDist() {
    return farDist;
}

void ToyCamera::setProjectionType(eToyProjection pt) {
    projType = pt;
}

eToyProjection ToyCamera::getProjectionType() {
    return projType;
}

void ToyCamera::setPosition(const Toyvec3 *pos) {
    if (position == 0) {
        position = (Toyvec3 *)malloc(sizeof(Toyvec3));
    }
    Toyvec3Assign(position, pos);
}

Toyvec3 *ToyCamera::getPosition() {
    return position;
}
