# Raytracer

## Dependencies
This raytracer is made using:
- GLFW
- GLEW

(C/C++ - General) Set additional include directories:
- src\vendor
- src\Framework
- src\Framework\GLAPI
- $(SolutionDir)Dependencies\GLFW\include
- $(SolutionDir)Dependencies\GLEW\include

Copy:
> src\Framework\GLAPI;src\Framework;src\vendor;$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include

(Linker - General) Set Additional Library Directories:
- $(SolutionDir)Dependencies\GLFW\lib-vc2022
- $(SolutionDir)Dependencies\GLEW\lib\Release\Win32

Copy:
> $(SolutionDir)Dependencies\GLFW\lib-vc2022;$(SolutionDir)Dependencies\GLEW\lib\Release\Win32

(Linker - Input) Additional Dependencies
- glfw3.lib
- opengl32.lib
- User32.lib
- Gdi32.lib
- Shell32.lib
- glew32s.lib

Copy
> glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;glew32s.lib
