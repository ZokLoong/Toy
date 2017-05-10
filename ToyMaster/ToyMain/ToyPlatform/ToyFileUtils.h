//
//  ToyFileUtils.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyFileUtils_h
#define ToyFileUtils_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class ToyFileUtils {
public:
    static unsigned char *read(const char *filePath, long *size);
    static bool write(const char *filePath, unsigned char *data, long usize);
    
    static std::string getHomeDir();
    static std::string getDocDir();
};

#endif /* ToyFileUtils_h */
