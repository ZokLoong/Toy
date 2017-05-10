//
//  ToyApplication.mm
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "../../ToyApplication.h"
#include "../../ToyDirector.h"
#import "ToyLoop.h"
#include "../../../ToyTest/ToyTest.h"

void ToyApplication::run() {
    ToyDirector::sharedDirector()->initGL();
    
    ToyDirector::sharedDirector()->pushRootObject(ToyTest::getCurrentTest());
    
    [[ToyLoop sharedLoop] start];
}
