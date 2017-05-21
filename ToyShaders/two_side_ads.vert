
attribute vec3 vertPosition;
attribute vec3 vertNormal;

varying vec3 lightIntensityBack;
varying vec3 lightIntensityFront;

struct LightInfo {
    vec3 Position;  // vert position in eye coordinates
    vec3 La;        // Ambient light color intensity
    vec3 Ld;        // Diffuse light color intensity
    vec3 Ls;        // Specular light color intensity
};
uniform LightInfo light;

struct MaterialInfo {
    vec3 Ka;        // Ambient reflectivity
    vec3 Kd;        // Diffuse reflectivity
    vec3 Ks;        // Specular reflectivity
    float Shininess;// Specular shininess reflect factor
};
uniform MaterialInfo material;

uniform mat3 normMat;
uniform mat4 modelview;
uniform mat4 projection;

void getEyeSpace(out vec3 norm, out vec3 position) {
    norm = normalize(normMat * vertNormal);
    position = vec3(modelview * vec4(vertPosition, 1.0));
}

vec3 phongModel(vec3 position, vec3 norm) {
    vec3 s = normalize(light.Position - position);
    vec3 r = reflect(-s, norm);
    vec3 v = normalize(-position.xyz);
    vec3 Ambient = light.La * material.Ka;
    float sDotN = max(dot(s, norm), 0.0);
    vec3 Diffuse = light.Ld * material.Kd * sDotN;
    vec3 Spec = vec3(0.0);
    if (sDotN > 0.0) {
        Spec = light.Ls * material.Ks * pow(max(dot(r, v), 0.0), material.Shininess);
    }
    return Ambient + Diffuse + Spec;
}

// This function is simple for test flat, because OpenGL ES2.0 is not support flat
// But the result is not very good
/*
vec3 flatLight(vec3 color, float s) {
    float x = ceil(color.x * s)/s;
    float y = ceil(color.y * s)/s;
    float z = ceil(color.z * s)/s;
    
    return vec3(x, y, z);
}
*/

void main() {
    vec3 tnorm, tpos;
    getEyeSpace(tnorm, tpos);
    
    // lightIntensityFront = flatLight(phongModel(tpos, tnorm), 5.0);
    lightIntensityFront = phongModel(tpos, tnorm);
    lightIntensityBack = phongModel(tpos, -tnorm);
    
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
