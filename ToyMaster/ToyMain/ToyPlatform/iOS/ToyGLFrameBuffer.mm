
//
//  ToyGLFrameBuffer.mm
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include <stdio.h>
#include "../../ToyGLSL/ToyGLFrameBuffer.h"
#include "ToyGLview.h"

void ToyGLFrameBuffer::swapBuffer() {
    [[ToyGLview sharedGLview] presentGLview];
}
