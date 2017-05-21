//
//  ToyMesh.c
//  Toy
//
//  Created by LongZhao on 2017/5/14.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyMesh.h"
#include "../ToyMain/ToyPlatform/ToyFileUtils.h"

static void ToyMeshAddVertexdata(ToyMesh *mesh,
                                 ToyTrianglelist *trianglelist,
                                 int vertex_index,
                                 int uv_index) {
    unsigned int index = 0;
    while (index != mesh->nvertexdata) {
        if (vertex_index == mesh->vertexdata[index].vertex_index) {
            if (uv_index == -1 ||
                uv_index == mesh->vertexdata[index].uv_index)
                goto add_index_to_tirangle_list;
        }
        ++index;
    }
    index = mesh->nvertexdata;
    ++mesh->nvertexdata;
    mesh->vertexdata = (ToyVertexdata *)realloc(mesh->vertexdata, sizeof(ToyVertexdata) * mesh->nvertexdata);
    mesh->vertexdata[index].uv_index = uv_index;
    mesh->vertexdata[index].vertex_index = vertex_index;
add_index_to_tirangle_list:
    ++trianglelist->nindicesarray;
    trianglelist->indicesarray = (unsigned int *)realloc(trianglelist->indicesarray, sizeof(unsigned int) * trianglelist->nindicesarray);
    trianglelist->indicesarray[trianglelist->nindicesarray - 1] = index;
}

ToyObj *ToyObjRead(const char *filename, const char *prefix) {
    ToyObj *obj = 0;
    char *data = 0;
    
    char path[TOY_MAX_CHAR] = {0};
    sprintf(path, "%s/%s", prefix, filename);
    
    data = (char *) ToyFileUtils::read(path, 0);
    
    if (!data) return 0;
    else {
        Toyvec3 v;
        ToyMesh *mesh = 0;
        ToyTrianglelist *trianglelist = 0;
        char use_smooth_normals = 0;
        char useuvs = 0;
        char last = 0;
        char *line = strsep(&data, "\n");
        char name[TOY_MAX_CHAR] = {0};
        char group[TOY_MAX_CHAR] = {0};
        char usemtl[TOY_MAX_CHAR] = {0};
        char str[TOY_MAX_CHAR] = {0};
        
        obj = (ToyObj *)calloc(1, sizeof(ToyObj));
        strcpy(obj->name, filename);
        
        while (line && sizeof(line) > 0) {
            if (!line[0] || line[0] == '#') {
                goto next_obj_line;
            } else if (line[0] == 'f' && line[1] == ' ') {
                int vertex_index[3] = {0, 0, 0};
                int uv_index[3] = {0, 0, 0};
                int normal_index[3] = {0, 0, 0};
                int idx = 0;
                
                if (sscanf(line, "f %d/%d %d/%d %d/%d",
                           &vertex_index[0],
                           &uv_index[0],
                           &vertex_index[1],
                           &uv_index[1],
                           &vertex_index[2],
                           &uv_index[2]) == 6) {
                    useuvs = 1;
                } else if (sscanf(line, "f %d//%d %d//%d %d//%d",
                                  &vertex_index[0],
                                  &normal_index[0],
                                  &vertex_index[1],
                                  &normal_index[1],
                                  &vertex_index[2],
                                  &normal_index[2]) == 6) {
                    useuvs = 0;
                } else if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                  &vertex_index[0],
                                  &uv_index[0],
                                  &normal_index[0],
                                  &vertex_index[1],
                                  &uv_index[1],
                                  &normal_index[1],
                                  &vertex_index[2],
                                  &uv_index[2],
                                  &normal_index[2]) == 9) {
                    useuvs = 1;
                }
                
                if (last != 'f') {
                    ++obj->nmesh;
                    obj->mesh = (ToyMesh *) realloc(obj->mesh, sizeof(ToyMesh) * obj->nmesh);
                    
                    mesh = &obj->mesh[obj->nmesh - 1];
                    memset(mesh, 0, sizeof(ToyMesh));
                    
                    ++mesh->ntrianglelist;
                    mesh->trianglelist = (ToyTrianglelist *) realloc(mesh->trianglelist, sizeof(ToyTrianglelist) * mesh->ntrianglelist);
                    
                    trianglelist = &mesh->trianglelist[mesh->ntrianglelist - 1];
                    memset(trianglelist, 0, sizeof(ToyTrianglelist));
                    
                    if (name[0]) strcpy(mesh->name, name);
                    else if (usemtl[0]) strcpy(mesh->usemtl, name);
                    else if (group[0]) strcpy(mesh->name, group);
                    mesh->use_smooth_normals = use_smooth_normals;
                    trianglelist->useuvs = useuvs;
                    
                    trianglelist->mode = GL_TRIANGLES;
                    
                    name[0] = usemtl[0] = group[0] = 0;
                }
                
                for (idx = 0; idx < 3; ++idx) {
                    --vertex_index[idx];
                    --uv_index[idx];
                    ToyMeshAddVertexdata(mesh, trianglelist, vertex_index[idx], uv_index[idx]);
                }
                
                ++trianglelist->ntriangleindx;
                trianglelist->triangleindex = (ToyTriangleIndex *) realloc(trianglelist->triangleindex, sizeof(ToyTriangleIndex) * trianglelist->ntriangleindx);
                memcpy(trianglelist->triangleindex[trianglelist->ntriangleindx - 1].vertex_index, vertex_index, sizeof(vertex_index));
                memcpy(trianglelist->triangleindex[trianglelist->ntriangleindx - 1].uv_index, uv_index, sizeof(uv_index));
            } else if (sscanf((const char *)data, "v %f %f %f", &v.x, &v.y, &v.z) == 3) {
                // vertex data
                ++obj->nvertices;
                obj->vertices = (Toyvec3 *) realloc(obj->vertices, sizeof(Toyvec3) * obj->nvertices);
                // obj->normals = (Toyvec3 *) realloc(obj->normals, sizeof(Toyvec3) * obj->nvertices);
                // obj->fnormals = (Toyvec3 *) realloc(obj->fnormals, sizeof(Toyvec3) * obj->nvertices);
                
                memcpy(&obj->vertices[obj->nvertices - 1], &v, sizeof(Toyvec3));
            } else if (sscanf((const char *)data, "vn %f %f %f", &v.x, &v.y, &v.z) == 3) {
                // normal data
            } else if (sscanf((const char *)data, "vt %f %f", &v.x, &v.y) == 2) {
                // texture coordinates
                ++obj->ntexcoords;
                obj->texs = (Toyvec2 *) realloc(obj->texs, sizeof(Toyvec2) * obj->ntexcoords);
                
                memcpy(&obj->texs[obj->ntexcoords - 1], &v, sizeof(Toyvec2));
            } else if (sscanf((const char *)data, "o %s", str) == 1) strcpy(name, str);
            else if (sscanf((const char *)data, "g %s", str) == 1) strcpy(group, str);
            else if (sscanf((const char *)data, "usemtl %s", str) == 1) strcpy(usemtl, str);
            else if (sscanf((const char *)data, "mtllib %s", str) == 1) strcpy(obj->mtllib, str);
            else if (sscanf((const char *)data, "s %s", str) == 1) {
                use_smooth_normals = 1;
                if (!strcmp(str, "off") || !strcmp(str, "0")) use_smooth_normals = 0;
            }
        next_obj_line:
            last =  line[0];
            line = strsep(&data, "\n");
        }
        
        obj->normals = (Toyvec3 *) calloc(1, sizeof(Toyvec3) * obj->nvertices);
        obj->fnormals = (Toyvec3 *) calloc(1, sizeof(Toyvec3) * obj->nvertices);
        obj->tangent = (Toyvec3 *) calloc(1, sizeof(Toyvec3) * obj->nvertices);
        
        // Build normals
        {
            unsigned int i, j, k, index;
            i = 0;
            while (i != obj->nmesh) {
                mesh = &obj->mesh[i];
                
                j = 0;
                while (j != mesh->ntrianglelist) {
                    trianglelist = &mesh->trianglelist[j];
                    
                    k = 0;
                    while (k != trianglelist->ntriangleindx) {
                        Toyvec3 v1, v2, normal;
                        
                        // vertex normal
                        Toyvec3Sub(&v1,
                                   &obj->vertices[trianglelist->triangleindex[k].vertex_index[0]],
                                   &obj->vertices[trianglelist->triangleindex[k].vertex_index[1]]);
                        Toyvec3Sub(&v2,
                                   &obj->vertices[trianglelist->triangleindex[k].vertex_index[0]],
                                   &obj->vertices[trianglelist->triangleindex[k].vertex_index[2]]);
                        Toyvec3Cross(&normal, &v1, &v2);
                        Toyvec3Normalize(&normal, &normal);
                        
                        // face normal
                        memcpy(&obj->fnormals[trianglelist->triangleindex[k].vertex_index[0]],
                               &normal,
                               sizeof(Toyvec3));
                        memcpy(&obj->fnormals[trianglelist->triangleindex[k].vertex_index[1]],
                               &normal,
                               sizeof(Toyvec3));
                        memcpy(&obj->fnormals[trianglelist->triangleindex[k].vertex_index[2]],
                               &normal,
                               sizeof(Toyvec3));
                        
                        // smooth normal
                        for (index = 0; index < 3; ++index) {
                            Toyvec3Add(&obj->normals[trianglelist->triangleindex[k].vertex_index[index]],
                                       &obj->normals[trianglelist->triangleindex[k].vertex_index[index]],
                                       &normal);
                        }
                        
                        if (trianglelist->useuvs) {
                            Toyvec3 tangent;
                            Toyvec2 uv1, uv2;
                            float c;
                            
                            Toyvec2Sub(&uv1,
                                       &obj->texs[trianglelist->triangleindex[k].uv_index[2]],
                                       &obj->texs[trianglelist->triangleindex[k].uv_index[0]]);
                            Toyvec2Sub(&uv2,
                                       &obj->texs[trianglelist->triangleindex[k].uv_index[1]],
                                       &obj->texs[trianglelist->triangleindex[k].uv_index[0]]);
                            
                            c = 1.0f / (uv1.x * uv2.y - uv2.x * uv1.y);
                            
                            tangent.x = (v1.x * uv2.y + v2.x * uv1.y) * c;
                            tangent.y = (v1.y * uv2.y + v2.y * uv1.y) * c;
                            tangent.z = (v1.z * uv2.y + v2.z * uv1.y) * c;
                            
                            for (index = 0; index < 3; ++index) {
                                Toyvec3Add(&obj->tangent[trianglelist->triangleindex[k].vertex_index[index]],
                                           &obj->tangent[trianglelist->triangleindex[k].vertex_index[index]],
                                           &tangent);
                            }
                        }
                        
                        ++k;
                    }
                    
                    ++j;
                }
                
                ++i;
            }
            
            // Normalize normals
            i = 0;
            while (i != obj->nmesh) {
                j = 0;
                while (j != obj->mesh[i].nvertexdata) {
                    index = obj->mesh[i].vertexdata[j].vertex_index;
                    
                    Toyvec3Normalize(&obj->normals[index], &obj->normals[index]);
                    
                    if (obj->mesh[i].vertexdata[j].uv_index != -1) {
                        Toyvec3Normalize(&obj->tangent[index], &obj->tangent[index]);
                    }
                    
                    ++j;
                }
                
                ++i;
            }
        }
    }
    return obj;
}

ToyObj *ToyObjFree(ToyObj *obj) {
    ToyObjFreeData(obj);
    ToyObjFreeGL(obj);
    
    free(obj);
    obj = 0;
    
    return obj;
}

void ToyObjFreeData(ToyObj *obj) {
    if (obj->vertices) {
        free(obj->vertices);
        obj->vertices = 0;
    }
    if (obj->normals) {
        free(obj->normals);
        obj->normals = 0;
    }
    if (obj->fnormals) {
        free(obj->fnormals);
        obj->fnormals = 0;
    }
    if (obj->texs) {
        free(obj->texs);
        obj->texs = 0;
    }
}

void ToyObjFreeGL(ToyObj *obj) {
    int i;
    i = 0;
    while (i != obj->nmesh) {
        ToyMesh *mesh = &obj->mesh[i];
        
        if (mesh->vbo) {
            glDeleteBuffers(1, &mesh->vbo);
            mesh->vbo = 0;
        }
        int j = 0;
        while (j != mesh->ntrianglelist) {
            ToyTrianglelist *trianglelist = &mesh->trianglelist[j];
            if (trianglelist->vbo) {
                glDeleteBuffers(1, &trianglelist->vbo);
                trianglelist->vbo = 0;
            }
            if (trianglelist->triangleindex) {
                free(trianglelist->triangleindex);
                trianglelist->triangleindex = 0;
            }
            trianglelist->ntriangleindx = 0;
            if (trianglelist->indicesarray) {
                free(trianglelist->indicesarray);
                trianglelist->indicesarray = 0;
            }
            trianglelist->nindicesarray = 0;
        }
        if (mesh->vao) {
            glDeleteVertexArraysOES(1, &mesh->vao);
            mesh->vao = 0;
        }
        
        if (mesh->vertexdata) {
            free(mesh->vertexdata);
            mesh->vertexdata = 0;
        }
        mesh->nvertexdata = 0;
        
        if (mesh->trianglelist) {
            free(mesh->trianglelist);
            mesh->trianglelist = 0;
        }
        mesh->ntrianglelist = 0;
    }
}

void ToyObjBuild(ToyObj *obj) {
    int i = 0;
    while (i != obj->nmesh) {
        ToyObjBuildMesh(obj, i);
        ++i;
    }
}

void ToyObjBuildMesh(ToyObj *obj, unsigned int index) {
    ToyMesh *mesh = &obj->mesh[index];
    ToyObjBuildVBOMesh(obj, index);
    
    glGenVertexArraysOES(1, &mesh->vao);
    glBindVertexArrayOES(mesh->vao);
    
    ToyObjSetAttribMesh(obj, index);
    
    if (mesh->ntrianglelist == 1) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->trianglelist[0].vbo);
    }
    
    glBindVertexArrayOES(0);
}

void ToyObjBuildVBOMesh(ToyObj *obj, unsigned int index) {
    unsigned int i, idx;
    
    ToyMesh *mesh = &obj->mesh[index];
    mesh->offset[0] = 0;
    mesh->stride = sizeof(Toyvec3); // vertex
    
    mesh->offset[1] = mesh->stride;
    mesh->stride += sizeof(Toyvec3); // normals
    
    mesh->offset[2] = mesh->stride;
    mesh->stride += sizeof(Toyvec3); // face normal
    
    mesh->offset[3] = -1;
    if (mesh->vertexdata[0].uv_index != -1) {
        mesh->offset[3] = mesh->stride;
        mesh->stride += sizeof(Toyvec2); // texture
        
        mesh->offset[4] = mesh->stride;
        mesh->stride += sizeof(Toyvec3); // tangent
    }
    
    mesh->size = mesh->nvertexdata * mesh->stride;
    
    unsigned char *vertex_array = (unsigned char *)malloc(mesh->size);
    unsigned char *vertex_start = vertex_array;
    
    i = 0;
    while (i != mesh->nvertexdata) {
        idx = mesh->vertexdata[i].vertex_index;
        // vertex position
        memcpy(vertex_array, &obj->vertices[idx], sizeof(Toyvec3));
        vertex_array += sizeof(Toyvec3);
        // normal
        memcpy(vertex_array, &obj->normals[idx], sizeof(Toyvec3));
        vertex_array += sizeof(Toyvec3);
        // fnormal
        memcpy(vertex_array, &obj->fnormals[idx], sizeof(Toyvec3));
        vertex_array += sizeof(Toyvec3);
        
        if (mesh->vertexdata[0].uv_index != -1) {
            // texture
            memcpy(vertex_array, &obj->texs[mesh->vertexdata[i].uv_index], sizeof(Toyvec2));
            vertex_array += sizeof(Toyvec2);
            
            // tangent
            memcpy(vertex_array, &obj->tangent[idx], sizeof(Toyvec3));
            vertex_array += sizeof(Toyvec3);
        }
        ++i;
    }
    
    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    
    glBufferData(GL_ARRAY_BUFFER, mesh->size, vertex_start, GL_STATIC_DRAW);
    
    free(vertex_start);
    
    i = 0;
    while (i != mesh->ntrianglelist) {
        glGenBuffers(1, &mesh->trianglelist[i].vbo);
        
        // elements
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->trianglelist[i].vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh->trianglelist[i].nindicesarray * sizeof(unsigned int),
                     mesh->trianglelist[i].indicesarray,
                     GL_STATIC_DRAW);
        ++i;
    }
}

void ToyObjSetAttribMesh(ToyObj *obj, unsigned int index) {
    ToyMesh *mesh = &obj->mesh[index];
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    
    // vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh->stride, (char *)(0) + mesh->offset[0]);
    
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mesh->stride, (char *)(0) + mesh->offset[1]);
    
    if (mesh->offset[3] != -1) {
        // texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mesh->stride, (char *)(0) + mesh->offset[3]);
        
        // tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, mesh->stride, (char *)(0) + mesh->offset[4]);
    }
    
    // fnormal
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, mesh->stride, (char *)(0) + mesh->offset[2]);
}

void ToyObjDraw(ToyObj *obj) {
    int i = 0;
    while (i != obj->nmesh) {
        ToyMesh *mesh = &obj->mesh[i];
        if (mesh->vao) {
            glBindVertexArrayOES(mesh->vao);
        } else {
            ToyObjSetAttribMesh(obj, i);
        }
        int j = 0;
        while (j != mesh->ntrianglelist) {
            if (mesh->vao) {
                if (mesh->ntrianglelist != 1) {
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->trianglelist[j].vbo);
                }
            } else {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->trianglelist[j].vbo);
            }
            
            glDrawElements(mesh->trianglelist[j].mode, mesh->trianglelist[j].nindicesarray, GL_UNSIGNED_INT, 0);
            
            ++j;
        }
        
        ++i;
    }
}
