//
//  ToyLoop.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/CADisplayLink.h>

@interface ToyLoop : NSObject {
    CADisplayLink *displayLink;
}

+ (id)sharedLoop;
- (void)start;
- (void)event:(id)sender;

@end
