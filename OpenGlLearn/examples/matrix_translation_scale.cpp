//
//  matrix_translation_scale.cpp
//  OpenGlLearn
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

double prev_seconds;
int frame_count;

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
    2.0f, 0.0f, 0.0f, 0.0f,  // first column
    0.0f, 2.0f, 0.0f, 0.0f,  // second column
    0.0f, 0.0f, 2.0f, 0.0f,  // third column
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

void _print_extra() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supoorted %s\n", version);
}

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
    
    while (!glfwWindowShouldClose(window)) {
        update_fps_counter(window);
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

