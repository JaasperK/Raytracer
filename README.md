# Raytracer

## Gruppenmitglieder
Jasper Lennart Köhn (623385) <br>
Max Thomas Reinstadler (622083) <br>
Senol Schulz (624986)

## TODO
+ Implement Light Sources
+ Build Scene
+ Raytrace

## Dependencies
Dieser Raytracer entsteht im Rahmen des Programmierpraktikums des Moduls Computergraphik und wurde unter Windows 10 und 11 mit Visual Studio 2022 und x86 Architektur entwickelt.
Dabei haben wir *GLFW* und *GLEW* verwendet. Die benötigten Datein sind im *Dependencies*-Folder enthalten und müssen nur noch richtig in das Projekt eingebunden werden (siehe [Setup](#Setup)).

## Setup
Öffnen Sie die *Solution Properties* und stellen Sie sicher, dass alle Felder wie beschrieben gesetzt sind:

(**C/C++ - General**) Setzen Sie *Additional Include Directories*:
- src\vendor
- src\Framework
- src\Framework\GLAPI
- $(SolutionDir)Dependencies\GLFW\include
- $(SolutionDir)Dependencies\GLEW\include

Zum Kopieren: <br>
`src\Framework\GLAPI;src\Framework;src\vendor;$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include`

(**Linker - General**) Setzen Sie *Additional Library Directories*:
- $(SolutionDir)Dependencies\GLFW\lib-vc2022
- $(SolutionDir)Dependencies\GLEW\lib\Release\Win32

Zum Kopieren: <br>
`$(SolutionDir)Dependencies\GLFW\lib-vc2022;$(SolutionDir)Dependencies\GLEW\lib\Release\Win32`

(**Linker - Input**) Setzen Sie *Additional Dependencies*:
- glfw3.lib
- opengl32.lib
- User32.lib
- Gdi32.lib
- Shell32.lib
- glew32s.lib

Zum Kopieren: <br>
`glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;glew32s.lib`

## Ausführung
Über Visual Studio (F5).
