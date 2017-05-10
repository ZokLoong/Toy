
attribute vec3 vertPosition;
attribute vec3 vertColor;

varying vec3 Color;

uniform mat4 modelview;
uniform mat4 projection;

void main() {
    Color = vertColor;
    gl_Position = projection * modelview * vec4(vertPosition, 1.0);
}
