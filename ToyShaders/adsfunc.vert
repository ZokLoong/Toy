
attribute vec3 vertPosition;
attribute vec3 vertNormal;

varying vec3 lightIntensity;

struct LightInfo {
    vec3 Position; // Light position in eye coordinates
    vec3 La; // Ambient light intensity
    vec3 Ld; // Diffuse light intensity
    vec3 Ls; // Specular light intensity
};
uniform LightInfo light;

struct MaterialInfo {
    vec3 Ka; // Ambient reflectivity
    vec3 Kd; // Diffuse reflectivity
    vec3 Ks; // Specular reflectivity
    float Shininess; // Specular shininess factor
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
    vec3 tnorm;
    vec3 tPosition;
    
    getEyeSpace(tnorm, tPosition);
    lightIntensity = phongModel(tPosition, tnorm);
    
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
