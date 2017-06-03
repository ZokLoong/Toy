
attribute vec3 vertPosition;
attribute vec3 vertNormal;
attribute vec2 vertTexcoords;

varying vec3 frontColor;
varying vec3 backColor;
varying vec2 texCoord;

struct LightInfo {
    vec3 Position;
    vec3 La;
    vec3 Ld;
    vec3 Ls;
};
uniform LightInfo light;

struct MaterialInfo {
    vec3 Ka;
    vec3 Ks;
    vec3 Kd;
    float Shininess;
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
    vec3 Specular = vec3(0.0);
    if (sDotN > 0.0) {
        Specular = light.Ls * material.Ks * pow(max(dot(r, v), 0.0), material.Shininess);
    }
    return Ambient + Diffuse + Specular;
}

void main() {
    vec3 norm;
    vec3 position;
    
    texCoord = vertTexcoords;
    
    getEyeSpace(norm, position);
    
    frontColor = phongModel(position, norm);
    backColor = phongModel(position, -norm);
    
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
