//
//  ToyTest.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyTest.h"

ToyObject *ToyTest::getCurrentTest() {
//    ToySceneDiffuse::sharedScene()->init();
//    return ToySceneDiffuse::sharedScene();
    ToySceneAds::sharedScene()->init();
    return ToySceneAds::sharedScene();
}
