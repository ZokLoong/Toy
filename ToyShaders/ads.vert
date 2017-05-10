
attribute vec3 vertPosition;
attribute vec3 vertNormal;

varying vec3 lightIntensity;

struct LightInfo {
    vec3 Position;  // Light position in eye - coordinate
    vec3 La;        // Ambient light intensity
    vec3 Ld;        // Diffuse light intensity
    vec3 Ls;        // Sepcular light intesity
};
uniform LightInfo light;

struct MaterialInfo {
    vec3 Ka;        // Ambient reflectivity
    vec3 Kd;        // Diffuse reflectivity
    vec3 Ks;        // Specular reflectivity
    float Shininess;// Specular shininess factor
};
uniform MaterialInfo material;

uniform mat3 normMat;
uniform mat4 modelview;
uniform mat4 projection;

void main() {
    vec3 tnorm = normalize(normMat * vertNormal);
    vec3 eyecoord = vec3(modelview * vec4(vertPosition, 1.0));
    vec3 s = normalize(light.Position - eyecoord);
    vec3 v = normalize(-eyecoord.xyz);
    vec3 r = reflect(-s, tnorm);
    vec3 ambient = light.La * material.Ka;
    float sDotN = max(dot(s, tnorm), 0.0);
    vec3 diffuse = light.Ld * material.Kd * sDotN;
    vec3 spec = vec3(0.0);
    if (sDotN > 0.0)
        spec = light.Ls * material.Ks * pow(max(dot(r, v), 0.0), material.Shininess);
    lightIntensity = ambient + diffuse + spec;
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
