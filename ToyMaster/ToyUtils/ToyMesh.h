//
//  ToyMesh.h
//  Toy
//
//  Created by LongZhao on 2017/5/14.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyMesh_h
#define ToyMesh_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "../ToyMain/ToyMath/Toymath.h"
#include "../ToyMain/ToyGLSL/ToyGLProgramCache.h"

#define TOY_MAX_CHAR    256

// struct for material
typedef struct ToyMaterial {
    
} ToyMaterial;

// struct for triangle index
typedef struct ToyTriangleIndex {
    unsigned int vertex_index[3];
    unsigned int uv_index[3];
} ToyTriangleIndex;

// struct for triangle list
typedef struct ToyTrianglelist {
    unsigned int ntriangleindx; // triangle index number
    ToyTriangleIndex *triangleindex;
    
    unsigned char useuvs;
    GLint mode;
    
    unsigned int nindicesarray;
    unsigned int *indicesarray;
    
    unsigned int vbo;
} ToyTrianglelist;

// struct for vertex data
typedef struct ToyVertexdata {
    int vertex_index;
    int uv_index;
} ToyVertexdata;

// struct for mesh
typedef struct ToyMesh {
    char name[TOY_MAX_CHAR];    // mesh name
    char usemtl[TOY_MAX_CHAR];  // use material name
    
    unsigned int ntrianglelist; // triangle list number
    ToyTrianglelist *trianglelist;
    
    unsigned int nvertexdata;   // vertex data number
    ToyVertexdata *vertexdata;
    
    unsigned char use_smooth_normals;
    
    unsigned int vbo;
    unsigned int stride;
    unsigned int size;
    unsigned int offset[5];
    unsigned int vao;
} ToyMesh;

// struct for obj format
typedef struct ToyObj {
    char name[TOY_MAX_CHAR];    // object file name
    char mtllib[TOY_MAX_CHAR];  // mtllib name
    
    unsigned int nvertices;     // vertex number
    Toyvec3 *vertices;
    Toyvec3 *normals;           // vertex normal
    Toyvec3 *fnormals;          // surface normal
    Toyvec3 *tangent;           // tangent
    
    unsigned int ntexcoords;    // texture coordinates number
    Toyvec2 *texs;              // texture coordinates
    
    unsigned int nmesh;         // mesh number
    ToyMesh *mesh;              // mesh
} ToyObj;

extern ToyObj *ToyObjRead(const char *filename, const char *prefix);
extern ToyObj *ToyObjFree(ToyObj *obj);
extern void ToyObjFreeData(ToyObj *obj);
extern void ToyObjFreeGL(ToyObj *obj);
extern void ToyObjBuild(ToyObj *obj);
extern void ToyObjBuildMesh(ToyObj *obj, unsigned int index);
extern void ToyObjBuildVBOMesh(ToyObj *obj, unsigned int index);
extern void ToyObjSetAttribMesh(ToyObj *obj, unsigned int index);
extern void ToyObjDraw(ToyObj *obj);

#endif /* ToyMesh_h */
