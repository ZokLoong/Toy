//
//  ToyGLview.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface ToyGLview : UIView {
    CAEAGLLayer *toyLayer;
    EAGLContext *toyContext;
}

+ (id)sharedGLview;
- (void)presentGLview;

@end
