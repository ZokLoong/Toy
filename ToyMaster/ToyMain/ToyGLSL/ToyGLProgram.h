//
//  ToyGLProgram.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyGLProgram_h
#define ToyGLProgram_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

struct Toymat3;
struct Toymat4;

typedef std::map< std::string, int > TOY_GLSL_UNIFORMS;

class ToyGLProgram {
public:
    ToyGLProgram();
    virtual ~ToyGLProgram();
    
    void attachShader(const char *vertSource, const char *fragSource);
    bool compileShader(GLuint shader);
    
    void link();
    void use();
    
    void destroy();
    
    void setAttribLocation(const char *attrib, int loc);
    GLint getUniformLoc(const char *uniform);
    
    void setUniform(const char *uniform, float v);
    void setUniform(const char *uniform, int v);
    void setUniform(const char *uniform, bool v);
    void setUniform(const char *uniform, float v0, float v1);
    void setUniform(const char *uniform, float v0, float v1, float v2);
    void setUniform(const char *uniform, const struct Toymat3 *mat);
    void setUniform(const char *uniform, const struct Toymat4 *mat);
    
    bool isLinked() { return linked; }
    
    void setName(std::string name) { this->name = name; }
    std::string getName() { return name; }
    
protected:
    GLuint program;
    GLuint vertShader;
    GLuint fragShader;
    
    TOY_GLSL_UNIFORMS uniforms;
    
    bool linked;
    
    std::string name;
};

#endif /* ToyGLProgram_h */
