
precision mediump float;

varying vec3 lightIntensityBack;
varying vec3 lightIntensityFront;

void main() {
    if (gl_FrontFacing) {
        gl_FragColor = vec4(lightIntensityFront, 1.0);
    } else {
        gl_FragColor = vec4(lightIntensityBack, 1.0);
    }
}
