//
//  ToyObjLoader.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/7.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyObjLoader.h"

ToyObjLoader::ToyObjLoader()
: v(0)
, n(0)
, tex(0)
, el(0) {
    
}

ToyObjLoader::~ToyObjLoader() {
    if (v) {
        free(v);
        v = 0;
    }
    if (n) {
        free(n);
        n = 0;
    }
    if (tex) {
        free(tex);
        tex = 0;
    }
    if (el) {
        free(el);
        el = 0;
    }
}

bool ToyObjLoader::read(const char *filePath) {
    return true;
}
