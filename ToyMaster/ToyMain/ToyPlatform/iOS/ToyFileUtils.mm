//
//  ToyFileUtils.mm
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "../ToyFileUtils.h"

std::string ToyFileUtils::getDocDir() {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    return [[paths objectAtIndex:0] UTF8String];
}

std::string ToyFileUtils::getHomeDir() {
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}
