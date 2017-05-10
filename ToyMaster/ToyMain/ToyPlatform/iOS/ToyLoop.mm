//
//  ToyLoop.m
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#import "ToyLoop.h"
#include "../../ToyDirector.h"

static ToyLoop *s_loop = nil;
@implementation ToyLoop
+ (id)sharedLoop {
    if (s_loop == nil) {
        s_loop = [ToyLoop new];
    }
    return s_loop;
}

- (void)start {
    [displayLink invalidate];
    displayLink = nil;
    
    displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(event:)];
    [displayLink setPreferredFramesPerSecond:60];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)event:(id)sender {
    ToyDirector::sharedDirector()->mainLoop();
}

@end
