//
//  ToyGLProgram.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyGLProgram.h"
#include "../ToyMath/Toymat3.h"
#include "../ToyMath/Toymat4.h"

ToyGLProgram::ToyGLProgram()
: program(0)
, linked(false)
, vertShader(0)
, fragShader(0) {
    
}

ToyGLProgram::~ToyGLProgram() {
    destroy();
    
    uniforms.clear();
}

void ToyGLProgram::destroy() {
    if (vertShader) {
        if (program) glDetachShader(program, vertShader);
        
        glDeleteShader(vertShader);
        vertShader = 0;
    }
    if (fragShader) {
        if (program) glDetachShader(program, fragShader);
        
        glDeleteShader(fragShader);
        fragShader = 0;
    }
    if (program) {
        glDeleteProgram(program);
        program = 0;
    }
}

void ToyGLProgram::attachShader(const char *vertSource, const char *fragSource) {
    if (!vertSource || !fragSource) {
        printf("Error: GLSL shader source is NULL.\n");
        return;
    }
    
    // Vertex shader
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    if (0 == vertShader) {
        printf("Error: Failed to create vertex shader.\n");
        return;
    }
    glShaderSource(vertShader, 1, &vertSource, 0);
    if (!compileShader(vertShader)) {
        printf("Error: Failed to compile vertex shader.\n");
        destroy();
        return;
    }
    
    // Fragment shader
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == fragShader) {
        printf("Error: Failed to create fragment shader.\n");
        return;
    }
    glShaderSource(fragShader, 1, &fragSource, 0);
    if (!compileShader(fragShader)) {
        printf("Error: Failed to compile fragment shader.\n");
        destroy();
        return;
    }
    
    program = glCreateProgram();
    if (0 == program) {
        printf("Error: Failed to create GLSL program.\n");
        destroy();
        return;
    }
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    // link();
}

bool ToyGLProgram::compileShader(GLuint shader) {
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (GL_FALSE == status) {
        GLint size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        if (size > 0) {
            GLchar *log = (GLchar *)malloc(sizeof(GLchar) * size);
            glGetShaderInfoLog(shader, size, 0, log);
            printf("Info: %s\n", log);
            free(log);
        }
        
        destroy();
        return false;
    }
    return true;
}

void ToyGLProgram::link() {
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        printf("Error: Failed to link GLSL program.\n");
        
        GLint size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        if (size > 0) {
            GLchar *log = (GLchar *)malloc(sizeof(GLchar) * size);
            glGetProgramInfoLog(program, size, 0, log);
            printf("Info: %s\n", log);
            free(log);
        }
        
        destroy();
    }
    
    linked = true;
}

void ToyGLProgram::use() {
    if (program) {
        glUseProgram(program);
    }
}

void ToyGLProgram::setAttribLocation(const char *attrib, int loc) {
    if (program) {
        glBindAttribLocation(program, loc, attrib);
    } else {
        printf("Warning: GLSL program must be create before set attribute location\n");
    }
}

GLint ToyGLProgram::getUniformLoc(const char *uniform) {
    TOY_GLSL_UNIFORMS::iterator iter = uniforms.find(uniform);
    if (iter != uniforms.end()) {
        return iter->second;
    }
    int loc = glGetUniformLocation(program, uniform);
    if (loc >= 0) {
        uniforms[uniform] = loc;
    }
    return loc;
}

void ToyGLProgram::setUniform(const char *uniform, float v) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniform1f(loc, v);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, int v) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniform1i(loc, v);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, bool v) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniform1i(loc, v);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, float v0, float v1) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniform2f(loc, v0, v1);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, float v0, float v1, float v2) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniform3f(loc, v0, v1, v2);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, const struct Toymat3 *mat) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniformMatrix3fv(loc, 1, GL_FALSE, mat->m);
        }
    }
}

void ToyGLProgram::setUniform(const char *uniform, const struct Toymat4 *mat) {
    if (program) {
        int loc = getUniformLoc(uniform);
        if (loc >= 0) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, mat->m);
        }
    }
}
