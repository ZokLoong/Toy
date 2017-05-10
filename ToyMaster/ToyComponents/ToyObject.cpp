//
//  ToyObject.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyObject.h"

ToyObject::ToyObject()
: vaoHandle(0) {
    
}

ToyObject::~ToyObject() {
    if (vaoHandle) {
        glDeleteVertexArraysOES(1, &vaoHandle);
        vaoHandle = 0;
    }
}
