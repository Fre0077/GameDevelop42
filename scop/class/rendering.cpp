#include "rendering.hpp"
#include "mat4.hpp"
#include "../include/utils.h"

rendering::rendering() {
    lastX = 400.0f;
	lastY = 300.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	firstMouse = true;
	leftMousePressed = false;

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

rendering::~rendering() {}

void rendering::renderTriangles(const std::vector<std::vector<float>>& triangles, GLuint shaderProgram) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    mat4 view;
    view.view(-cameraPos.x, -cameraPos.y, -cameraPos.z);

    mat4 projection;
    projection.project(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    mat4 rotY, rotX;
    rotY.world("y", this->rotY);
    rotX.world("x", this->rotX);
    mat4 model = rotY.multiply(rotX);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view.data);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection.data);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, model.data);

    for (const auto& triangle : triangles) {
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(float), triangle.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}

void rendering::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    (void) window;

    if (!leftMousePressed) {
        firstMouse = true;
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = lastX - xpos;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotY += xoffset;
    rotX += yoffset;
}

void rendering::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    (void) window;
    (void) mods;
    
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            leftMousePressed = true;
        } else if (action == GLFW_RELEASE) {
            leftMousePressed = false;
        }
    }
}

void rendering::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    (void) window;
    (void) xoffset;
    
    cameraPos.z -= (float)yoffset * 0.3f;
    
    if (cameraPos.z < 0.5f)
        cameraPos.z = 0.5f;
    if (cameraPos.z > 10.0f)
        cameraPos.z = 10.0f;
}
