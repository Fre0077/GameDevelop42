#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;      // Matrice del modello
uniform mat4 view;       // Matrice della vista (camera)
uniform mat4 projection; // Matrice di proiezione

out vec3 vertexColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;
}
