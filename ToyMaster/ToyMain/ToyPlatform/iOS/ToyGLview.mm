//
//  ToyGLview.m
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#import "ToyGLview.h"
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES2/gl.h>
#include "../../ToyGLSL/ToyGLFrameBuffer.h"
#include "../../ToyDirector.h"

#include <iostream>
#include "../../ToyGLSL/ToyGLProgramCache.h"
#include "../ToyFileUtils.h"

static ToyGLview *s_view;
@implementation ToyGLview

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

+ (id)sharedGLview {
    return s_view;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        
        s_view = self;
    }
    return self;
}

- (void)setupLayer {
    toyLayer = (CAEAGLLayer *)self.layer;
    toyLayer.opaque = YES;
}

- (void)setupContext {
    toyContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!toyContext) {
        NSLog(@"Error: Failed to create OpenGL ES2.0 context.\n");
        return;
    }
    if (![EAGLContext setCurrentContext:toyContext]) {
        NSLog(@"Error: Failed to set OpenGL ES2.0 context.\n");
        return;
    }
    
    ToyGLFrameBuffer::sharedFrameBuffer()->setGLcolorBuffer();
    [toyContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:toyLayer];
    ToyGLFrameBuffer::sharedFrameBuffer()->setGLdepthBuffer();
    ToyGLFrameBuffer::sharedFrameBuffer()->setGLframeBuffer();
    
    ToyGLFrameBuffer::sharedFrameBuffer()->setGLBuffer();
    
    ToyGLFrameBuffer::sharedFrameBuffer()->setViewport(0, 0, self.frame.size.width, self.frame.size.height);
    ToyGLFrameBuffer::sharedFrameBuffer()->setScissor(0, 0, self.frame.size.width, self.frame.size.height);
    
    ToyDirector::sharedDirector()->setFrameSize(self.frame.size.width, self.frame.size.height);
}

- (void)presentGLview {
    [toyContext presentRenderbuffer:GL_RENDERBUFFER];
}

@end
