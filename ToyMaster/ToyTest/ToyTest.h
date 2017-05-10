//
//  ToyTest.h
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyTest_h
#define ToyTest_h

#include <stdio.h>
#include "../ToyComponents/ToyObject.h"
#include "ToyScene.h"
#include "ToySceneDiffuse.h"
#include "ToySceneAds.h"

class ToyTest {
public:
    static ToyObject *getCurrentTest();
};

#endif /* ToyTest_h */
