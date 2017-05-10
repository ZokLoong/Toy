//
//  ToyCamera.h
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#ifndef ToyCamera_h
#define ToyCamera_h

#include <stdio.h>
#include <stdlib.h>

struct Toymat4;
struct Toyvec3;

// Projection
typedef enum eToyProjection {
    TOY_ORTHOGRAPHIC,
    TOY_PERSPECTIVE
} eToyProjection;

class ToyCamera {
public:
    ToyCamera();
    virtual ~ToyCamera();
    
    virtual void setFOVy(const float fovy);
    virtual float getFOVy(void);
    
    virtual void setNearDist(const float nearDist);
    virtual float getNearDist(void);
    
    virtual void setFarDist(const float farDist);
    virtual float getFarDist(void);
    
    virtual void setAspectRatio(const float ratio);
    virtual float getAspectRatio(void);
    
    virtual void setProjectionType(eToyProjection pt);
    virtual eToyProjection getProjectionType(void);
    
    virtual void setPosition(const struct Toyvec3 *pos);
    struct Toyvec3 *getPosition(void);
    
protected:
    eToyProjection projType; // Orthographic or perspective ?
    float FOVy; // y-direction filed-of-view
    float farDist; //Far clip distance - default 10000
    float nearDist; // Near clip distance - default 100
    float aspect; // x/y viewport ratio - default 1.3333
    
    struct Toyvec3 *position; // Position of camera
};

#endif /* ToyCamera_hpp */
