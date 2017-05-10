
attribute vec3 vertPosition; // Vertex position
attribute vec3 vertNorm; // Vertex normal

varying vec3 lightIntensity; // Light intensity

uniform vec3 lightPosition; // Light position in eye - coordinate
uniform vec3 Kd; // Reflect of diffuse light
uniform vec3 Ld; // Intensity of light

uniform mat3 normMat; // matrix of normal
uniform mat4 modelview; // matrix of modelview
uniform mat4 projection; // matrix of projection

void main() {
    // Convert normal and position to eye coord
    vec3 tnorm = normalize(normMat * vertNorm);
    vec3 eyecoord = vec3(modelview * vec4(vertPosition, 1.0));
    vec3 s = normalize(lightPosition - eyecoord);
    
    // The diffuse shading equation
    lightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);
    
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
