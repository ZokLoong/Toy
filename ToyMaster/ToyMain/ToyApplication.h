//
//  ToyApplication.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyApplication_h
#define ToyApplication_h

#include <stdio.h>

class ToyApplication {
public:
    static ToyApplication *sharedApplication();
    
    ToyApplication();
    virtual ~ToyApplication();
    
    virtual void run();
};

#endif /* ToyApplication_h */
