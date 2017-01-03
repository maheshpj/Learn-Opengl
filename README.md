# Learn OpenGL

Learn OpenGL

## OpenGL Setup

### Steps
1.  Open LearnOpenGL xcode project `/LearnOpenGL/LearnOpenGL.xcodeproj`
2.  To run any example, select the appropriate target e.g. `BasicTriangle` and click Run

### Advance Setup Steps
To use latest GLFW and GLEW libs (other than in lib folder) use below steps

[OpenGL 3.0+ setup GLFW and GLEW on a Mac](https://www.youtube.com/watch?v=Tz0dq2krCW8&t=334s)

1.  Install [HomeBrew - package manager for macOS](http://brew.sh/)
2.  Install GLFW3
    >$brew install glfw3
3.  Install GLEW
    >$brew install glew
4.  Open LearnOpenGL xcode project `/LearnOpenGL/LearnOpenGL.xcodeproj` and select main project
5.  Select `Build Settings > Search Paths > Header Search Paths` click + button
6.  Add `/usr/local/include`
7.  Go to `Build Phases > Link BinaryWith Libraries` click + button
8.  Search for 'opengl', add **OpenGL.framework**
9.  Click + button again, select `Add other...` button
10. Type `command + shift + G`, in text box type `/usr/local/`
11. Go to `Cellar > glew > [version] > lib`
12. Select **libGLEW.{version}.dylib**, click Open
13. Repeat steps 9, 10
14. Go to `Cellar > glfw3 > [version] > lib`
15. Select **libglfw.{version}.dylib**, click Open