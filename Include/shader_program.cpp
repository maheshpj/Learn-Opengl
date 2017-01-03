//
//  shader_program.cpp
//  LearnOpenGL
//
//  Created by Mahesh Jadhav on 15/12/16.
//  Copyright © 2016 ison. All rights reserved.
//

#include "shader_program.hpp"
#include "common.hpp"


GLuint get_shader_program(char* vertex_shader, char* frag_shader) {
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