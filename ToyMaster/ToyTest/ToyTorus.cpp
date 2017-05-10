//
//  ToyTorus.cpp
//  Toy
//
//  Created by LongZhao on 2017/5/1.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyTorus.h"
#include "../ToyMain/ToyMath/Toymath.h"

ToyTorus::ToyTorus() {
    
}

ToyTorus::~ToyTorus() {
    glDeleteBuffers(4, vboHandle);
}

void ToyTorus::init() {
    faces = sides * rings;
    int nverts = sides * (rings + 1);
    
    float *v = (float *)malloc((3 * nverts) * sizeof(float)); // vertexs
    float *n = (float *)malloc((3 * nverts) * sizeof(float)); // normals
    float *tex = (float *)malloc((2 * nverts) * sizeof(float)); // tex coords
    unsigned int *el = (unsigned int *)malloc((6 * faces) * sizeof(unsigned int)); // Elements
    
    // Generate the data
    generateVerts(v, n, tex, el, outerRadius, innerRadius);
    
    // Create VBO handle and Populate the data
    glGenBuffers(4, vboHandle);
    
    // vertex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nverts) * sizeof(float), v, GL_STATIC_DRAW);
    
    // normal
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
    glBufferData(GL_ARRAY_BUFFER, (3 * nverts) * sizeof(float), n, GL_STATIC_DRAW);
    
    // texture
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
    glBufferData(GL_ARRAY_BUFFER, (2 * nverts) * sizeof(float), tex, GL_STATIC_DRAW);
    
    // Elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6 * faces) * sizeof(unsigned int), el, GL_STATIC_DRAW);
    
    free(v);
    free(n);
    free(tex);
    free(el);
    
    // Create VAO handle and Populate the vbo handle
    glGenVertexArraysOES(1, &vaoHandle);
    glBindVertexArrayOES(vaoHandle);
    
    glEnableVertexAttribArray(0); // vertex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1); // normal
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(2); // tex
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandle[3]);
    
    glBindVertexArrayOES(0);
}

void ToyTorus::init(float outerRadius, float innerRadius, int nsides, int nrings) {
    this->outerRadius = outerRadius;
    this->innerRadius = innerRadius;
    this->rings = nrings;
    this->sides = nsides;
    
    init();
}

void ToyTorus::visit() {
    
}

void ToyTorus::render() {
    glBindVertexArrayOES(vaoHandle);
    glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, 0);
}

void ToyTorus::generateVerts(float *verts, float *norms, float *tex, unsigned int *el, float outerRadius, float innerRadius) {
    float ringFactor = (TOY_PI * 2) / rings;
    float sideFactor = (TOY_PI * 2) / sides;
    int idx = 0, tidx = 0;
    for( int ring = 0; ring <= rings; ring++ ) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for( int side = 0; side < sides; side++ ) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = (outerRadius + innerRadius * cv);
            verts[idx] = r * cu;
            verts[idx + 1] = r * su;
            verts[idx + 2] = innerRadius * sv;
            norms[idx] = cv * cu * r;
            norms[idx + 1] = cv * su * r;
            norms[idx + 2] = sv * r;
            tex[tidx] = u / (TOY_PI * 2);
            tex[tidx + 1] = v / (TOY_PI * 2);
            tidx += 2;
            // Normalize
            float len = sqrt( norms[idx] * norms[idx] +
                             norms[idx+1] * norms[idx+1] +
                             norms[idx+2] * norms[idx+2] );
            norms[idx] /= len;
            norms[idx+1] /= len;
            norms[idx+2] /= len;
            idx += 3;
        }
    }
    
    idx = 0;
    for( int ring = 0; ring < rings; ring++ ) {
        int ringStart = ring * sides;
        int nextRingStart = (ring + 1) * sides;
        for( int side = 0; side < sides; side++ ) {
            int nextSide = (side+1) % sides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx+1] = (nextRingStart + side);
            el[idx+2] = (nextRingStart + nextSide);
            el[idx+3] = ringStart + side;
            el[idx+4] = nextRingStart + nextSide;
            el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }
}
