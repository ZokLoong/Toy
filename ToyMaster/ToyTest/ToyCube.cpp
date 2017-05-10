//
//  ToyCube.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyCube.h"

ToyCube::ToyCube() {
    
}

ToyCube::ToyCube(float side) {
    this->side = side;
}

ToyCube::~ToyCube() {
    glDeleteBuffers(4, vboHandle);
    if (vaoHandle)
        glDeleteVertexArraysOES(1, &vaoHandle);
}

void ToyCube::init() {
    float side2 = side / 2.0f;
    
    float v[24*3] = {
        // Front
        -side2, -side2, side2,
        side2, -side2, side2,
        side2,  side2, side2,
        -side2,  side2, side2,
        // Right
        side2, -side2, side2,
        side2, -side2, -side2,
        side2,  side2, -side2,
        side2,  side2, side2,
        // Back
        -side2, -side2, -side2,
        -side2,  side2, -side2,
        side2,  side2, -side2,
        side2, -side2, -side2,
        // Left
        -side2, -side2, side2,
        -side2,  side2, side2,
        -side2,  side2, -side2,
        -side2, -side2, -side2,
        // Bottom
        -side2, -side2, side2,
        -side2, -side2, -side2,
        side2, -side2, -side2,
        side2, -side2, side2,
        // Top
        -side2,  side2, side2,
        side2,  side2, side2,
        side2,  side2, -side2,
        -side2,  side2, -side2
    };
    
    float n[24*3] = {
        // Front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    float tex[24*2] = {
        // Front
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    
    GLuint el[] = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };
    
    // Create VBO handle and populate the data
    glGenBuffers(4, vboHandle);
    
    // Vertex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    
    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);
    
    // texs
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_STATIC_DRAW);
    
    // elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(el), el, GL_STATIC_DRAW);
    
    // Create VAO handle and populate the data
    glGenVertexArraysOES(1, &vaoHandle);
    glBindVertexArrayOES(vaoHandle);
    
    glEnableVertexAttribArray(0); // vertex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1); // norm
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(2); // tex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]);
    
    glBindVertexArrayOES(0);
}

void ToyCube::visit() {
    
}

void ToyCube::render() {
    glBindVertexArrayOES(vaoHandle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
