//
//  ToyGLFrameBuffer.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyGLFrameBuffer_h
#define ToyGLFrameBuffer_h

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

class ToyGLFrameBuffer {
public:
    static ToyGLFrameBuffer *sharedFrameBuffer();
    
    ToyGLFrameBuffer();
    virtual ~ToyGLFrameBuffer();
    
    void clear();
    void swapBuffer();
    
    void setGLBuffer();
    
    void setViewport(int x, int y, int w, int h);
    void setScissor(int x, int y, int w, int h);
    
    void setGLcolorBuffer();
    void setGLdepthBuffer();
    void setGLframeBuffer();
    
    GLuint getColorBuffer() { return colorBuffer; }
    GLuint getDepthBuffer() { return depthBuffer; }
    GLuint getFrameBuffer() { return frameBuffer; }
    
protected:
    GLuint colorBuffer;
    GLuint depthBuffer;
    GLuint frameBuffer;
};

#endif /* ToyGLFrameBuffer_h */
