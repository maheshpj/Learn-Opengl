//
//  common.cpp
//  LearnOpenGL
//
//  Created by Mahesh Jadhav on 15/12/16.
//  Copyright © 2016 ison. All rights reserved.
//

#include "common.hpp"


GLFWwindow* _get_window() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return NULL;
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
        return NULL;
    }
    glfwMakeContextCurrent(window);
    
    return window;
}

double prev_seconds;
int frame_count;

void update_fps_counter(GLFWwindow* window) {
    double current_seconds;
    double elapsed_seconds;
    
    current_seconds = glfwGetTime();
    elapsed_seconds = current_seconds - prev_seconds;
    
    if(elapsed_seconds > 0.25) {
        prev_seconds = current_seconds;
        char tmp[128];
        double fps = (double)frame_count / elapsed_seconds;
        
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frame_count = 0;
    }
    frame_count++;
}

void _print_shader_info_log(GLuint shader_index) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
    printf("shader info log for GL index %u:\n%s\n", shader_index, log);
}

bool _check_for_compile_errors(GLuint shader_index) {
    int params = -1;
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params) {
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader_index);
        _print_shader_info_log(shader_index);
        return false;
    }
    return true;
}

void _print_program_info_log(GLuint program) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog(program, max_length, &actual_length, log);
    printf("program info log for GL index %u:\n%s", program, log);
}

bool _check_program_linking_errors(GLuint program) {
    // check if link was unsuccessful
    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if(GL_TRUE != params) {
        fprintf(stderr, "Error: could not link shader program GL index %u\n",
                program);
        _print_program_info_log(program);
        return false;
    }
    return true;
}

void _print_extra() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supoorted %s\n", version);
}