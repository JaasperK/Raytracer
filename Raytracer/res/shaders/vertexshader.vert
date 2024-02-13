#version 460 core

out vec3 v_Position;
out vec3 v_Normal;
out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_CameraMatrix;
uniform mat4 u_ModelMatrix;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

void main() {
    vec4 pos = vec4(aPos, 1.0);
    v_Position = pos.xyz;
    v_Normal = aNormal;
    v_Color = aColor;
    v_TexCoord = aTexCoord;
    gl_Position = pos;
};
