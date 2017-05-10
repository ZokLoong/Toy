
precision mediump float;

varying vec3 lightIntensity;

void main() {
    gl_FragColor = vec4(lightIntensity, 1.0);
}
