//
//  squareOf2VBOs.cpp
//  OpenGlLearn
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    fprintf(stderr, "Running Square with 2 VBO triangles...\n\n");
    
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
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
    
    
    // Program for square
    
    GLfloat points1[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    
    GLfloat points2[] = {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    const char* vertex_shader =
    "#version 410\n"
    "in vec3 vp;"
    "void main () {"
    "	gl_Position = vec4 (vp, 1.0);"
    "}";
    
    const char* frag_shader =
    "#version 410\n"
    "out vec4 frag_colour;"
    "void main () {"
    "	frag_colour = vec4 (0.8, 0.3, 0.5, 1.0);"
    "}";
    
    // VBO 1
    GLuint vbo1;
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points1), points1, GL_STATIC_DRAW);
    
    // VBO 1
    GLuint vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW);
    
    // VAO 1
    GLuint vao1;
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // VAO 2
    GLuint vao2;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // Shaders
    GLuint vs, fs;
    GLuint shader_programme;
    
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    
    fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag_shader, NULL);
    glCompileShader(fs);
    
    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);
        
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
    
}


