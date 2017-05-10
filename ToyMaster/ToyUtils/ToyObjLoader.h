//
//  ToyObjLoader.h
//  Toy
//
//  Created by LongZhao on 2017/5/7.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyObjLoader_h
#define ToyObjLoader_h

#include <stdio.h>
#include <stdlib.h>

class ToyObjLoader {
public:
    ToyObjLoader();
    virtual ~ToyObjLoader();
    
    bool read(const char *filePath);
    
protected:
    float *v;
    float *n;
    float *tex;
    unsigned int *el;
};

#endif /* ToyObjLoader_h */
