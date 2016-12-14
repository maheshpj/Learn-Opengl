//
//  triangle_rotate_0_90.cpp
//  OpenGlLearn
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "common.hpp"

#define PI 3.14159265


GLfloat points[] = {
    0.0f,	0.5f,	0.0f,
    0.5f, -0.5f,	0.0f,
    -0.5f, -0.5f,	0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f,	0.0f,
    0.0f, 1.0f,	0.0f,
    0.0f, 0.0f,	1.0f
};

float matrix[] = {
    1.0f, 0.0f, 0.0f, 0.0f,  // first column
    0.0f, 1.0f, 0.0f, 0.0f,  // second column
    0.0f, 0.0f, 1.0f, 0.0f,  // third column
    0.0f, 0.0f, 0.0f, 1.0f   // fourth column
};

const char* vertex_shader =
"#version 410\n"
"in vec3 vert_pos;"
"in vec3 vert_col;"
"uniform mat4 matrix;"
"out vec3 color;"
"void main() {"
"   color = vert_col;"
"	gl_Position = matrix * vec4(vert_pos, 1.0);"
"}";

const char* frag_shader =
"#version 410\n"
"in vec3 color;"
"out vec4 frag_colour;"
"void main() {"
"	frag_colour = vec4(color, 1.0);"
"}";

GLuint _get_shader_program() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    if(!_check_for_compile_errors(vs)) {
        return false;
    };
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag_shader, NULL);
    glCompileShader(fs);
    if(!_check_for_compile_errors(fs)) {
        return false;
    };
    
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    if(!_check_program_linking_errors(shader_programme)) {
        return false;
    }
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return shader_programme;
}

void _show_rotation_angle(GLFWwindow* window, float angle) {
    char tmp[128];
    sprintf(tmp, "Rotation Angle: %.0f", angle);
    glfwSetWindowTitle(window, tmp);
}

int main() {
    GLFWwindow* window = _get_window();
    if(window == NULL) {
        return 1;
    }
    
    glewExperimental = GL_TRUE;
    glewInit();
    _print_extra();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // VBO
    GLuint vert_vbo;
    glGenBuffers(1, &vert_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint color_vbo;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    // VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLuint shader_programme = _get_shader_program();
    
    // retrive the location of the new matrix uniform in vert shader
    int matrix_location = glGetUniformLocation(shader_programme, "matrix");
    
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    
    // rotate at 1 unit per second
    float speed = -1.0f;
    double deg = 0.0f;
    double rad = deg * PI / 180.0f;
    
    while (!glfwWindowShouldClose(window)) {
        // when triangle is at 0 or 90 degrees
        // change the direction and wait for some time
        if(deg == 0.0f || deg == 90.0f) {
            speed = -speed;
            usleep(1000000);
        }
        deg = deg + speed;
        rad = deg * PI / 180.0;
        
        // update the matrix
        matrix[5] = cos(rad);
        matrix[6] = sin(rad);
        matrix[9] = -sin(rad);
        matrix[10] = cos(rad);
        
        //update_fps_counter(window);
        _show_rotation_angle(window, deg);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
        
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
    
    glfwTerminate();
    return 0;
}

