#version 460 core

out vec4 FragColor;

uniform sampler2D u_Texture0;
uniform sampler2D jasper;
uniform float u_AmbLight;

in vec2 v_TexCoord;
in vec3 v_Normal;

void main() {
    //FragColor = (u_AmbLight + (1.0 - u_AmbLight) * max(v_Normal.z, 0.1)) * texture(u_Texture0, v_TexCoord);
    FragColor = texture(u_Texture0, v_TexCoord) + texture(u_Texture0, v_TexCoord);
};
