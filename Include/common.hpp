//
//  common.hpp
//  LearnOpenGL
//
//  Created by Mahesh Jadhav on 15/12/16.
//  Copyright © 2016 ison. All rights reserved.
//

#ifndef common_hpp
#define common_hpp

#include <GLFW/glfw3.h>
#include <stdio.h>


void update_fps_counter(GLFWwindow* window);
void _print_shader_info_log(GLuint shader_index);
bool _check_for_compile_errors(GLuint shader_index);
void _print_program_info_log(GLuint program);
bool _check_program_linking_errors(GLuint program);
void _print_extra();
GLFWwindow* _get_window();

#endif /* common_hpp */
