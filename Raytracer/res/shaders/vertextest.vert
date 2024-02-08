#version 460 core


uniform mat4 u_CameraMatrix;
uniform mat4 u_ModelMatrix;

layout (location = 0) in vec3 aPos;


void main()
{
    vec4 pos = u_CameraMatrix * u_ModelMatrix * vec4(aPos, 1.0);
    gl_Position = pos;
}
