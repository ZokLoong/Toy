//
//  ToyApplication.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyApplication.h"

static ToyApplication s_application;
ToyApplication *ToyApplication::sharedApplication() {
    return &s_application;
}

ToyApplication::ToyApplication() {
    
}

ToyApplication::~ToyApplication() {
    
}
