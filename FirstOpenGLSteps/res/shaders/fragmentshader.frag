#version 460 core

out vec4 FragColor;

uniform sampler2D u_Earth;
uniform float u_AmbLight;

in vec2 v_TexCoord;
in vec3 v_Normal;

void main() {
    FragColor = (u_AmbLight + (1.0 - u_AmbLight) * max(v_Normal.z, 0.1)) * texture(u_Earth, v_TexCoord);
};
