#version 460 core

out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_CameraMatrix;
uniform mat4 u_ModelMatrix;

uniform vec3 u_CamPos;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

void main() {
    v_Normal = aPos.xyz;
    v_TexCoord = aTexCoord;
    gl_Position = u_CameraMatrix * u_ModelMatrix * vec4(aPos, 1.0);
};
