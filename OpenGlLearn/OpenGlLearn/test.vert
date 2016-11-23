#version 410

in vec3 vertex_position;

void main() {
    gl_position = vec4(vertex_position, 1.0);
}