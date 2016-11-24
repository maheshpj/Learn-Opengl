# Learn OpenGL

1.	Install CMake to Build Project Files  
 	CMake will allow us to build Xcode projects that work with GLEW.  
	`brew install cmake`
	
2.  Build Xcode Project Files
```
	cd OpenGlLearn
	mkdir xcode
	cd xcode
	cmake -G "Xcode" ..
```
 
Once completed, there should be a project available in the “xcode” folder that was created.
 
If you prefer, you can also build individual projects for each C++ file at a time by running a command like this:
 
`./run.sh examples/example.cpp`