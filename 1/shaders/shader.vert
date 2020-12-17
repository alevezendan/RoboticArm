#version 410 core

layout(location = 0) in vec3 vertex_position;
//matric model,view,projection uniform 


void main() {
    gl_Position = vec4(vertex_position, 1.0);
}
