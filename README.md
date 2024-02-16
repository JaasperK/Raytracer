# Raytracer
Dieser Raytracer entsteht im Rahmen des Programmierpraktikums für das Modul Computergraphik an der Humboldt Universität zu Berlin.
Zu Beginn der Übungsaufgaben haben wir mit der Programmierung eines Wrappers um die OpenGL-API begonnen und auch für diesen Raytracer verwendet.
Die interessanten Datein sind src/Main.cpp und res/shaders/fragmentshader.frag.

## Gruppenmitglieder
Jasper Lennart Köhn (623385) <br>
Max Thomas Reinstadler (622083) <br>
Senol Schulz (624986)

## Features
- Bewegbare Kamera
- "Echtzeit" Raytracing für Kugeln mit
  - mehreren Rays pro Pixel ```u_RaysPerPixel```
  - mehreren bounces pro Ray ```u_MaxBounces```
- Lichtberechnung durch die lineare Interpolation zwischen einer spekularen und einer diffusen Komponente anhand des Winkels zur Lichtquelle
- Shadow rays für die Schattenberechnung

## Quellen
Für die Erzeugung der Zufallszahlen für die Offsets der Ray origin und der Vektoren für die diffuse Reflexion:
- www.pcg-random.org und https://github.com/imneme/pcg-cpp
- www.shadertoy.com/view/XlGcRh
- https://stackoverflow.com/a/6178290
- https://math.stackexchange.com/a/1585996



## Dependencies
Der Raytracer wurde unter Windows 10 und 11 mit Visual Studio 2022 und für die x86 Architektur entwickelt.
Dabei haben wir *GLFW* und *GLEW* verwendet. Zusätzlich haben wir glm für Vector und Matrix Operationen und stb_image zum Laden von Texturen verwendet.
Die benötigten Datein sind in den *Dependencies*- und *src\vendor*-Folder enthalten und müssen nur noch richtig in das Projekt eingebunden werden (siehe [Setup](#Setup)).

## Setup
Nach dem Öffnen der Solution sollte das Projekt direkt ausführbar sein, falls das nicht der Fall ist, stellen Sie sicher, dass Sie x86 verwenden und in den
*Solution Properties* die Folgenden Felder, wie beschrieben gesetzt sind:

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
