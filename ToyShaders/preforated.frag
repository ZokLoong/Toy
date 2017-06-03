
precision mediump float;

varying vec3 frontColor;
varying vec3 backColor;
varying vec2 texCoord;

void main() {
    const float scale = 15.0;
    
    bvec2 toDiscard = greaterThan(fract(texCoord * scale), vec2(0.2, 0.2));
    
    if (all(toDiscard)) {
        discard;
    }
    
    if (gl_FrontFacing) {
        gl_FragColor = vec4(frontColor, 1.0);
    } else {
        gl_FragColor = vec4(backColor, 1.0);
    }
}
