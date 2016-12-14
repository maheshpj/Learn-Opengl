//
//  matrix_translation.cpp
//  OpenGlLearn
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "common.hpp"


int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    
    if(!window){
        fprintf(stderr, "ERROR: Could not open window with glfw3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supoorted %s\n", version);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    
    // Program for traingle
    
    GLuint vs, fs;
    GLuint shader_programme;
    
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
        0.5f, 0.0f, 0.0f, 1.0f   // fourth column
    };
    
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

    // Shaders
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    if(!_check_for_compile_errors(vs)) {
        return false;
    };
    
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag_shader, NULL);
    glCompileShader(fs);
    if(!_check_for_compile_errors(fs)) {
        return false;
    };

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    if(!_check_program_linking_errors(shader_programme)) {
        return false;
    }
    
    // retrive the location of the new matrix uniform in vert shader
    int matrix_location = glGetUniformLocation(shader_programme, "matrix");
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        update_fps_counter(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
        //glDrawArrays(GL_LINE_LOOP, 0, 3);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;

}

