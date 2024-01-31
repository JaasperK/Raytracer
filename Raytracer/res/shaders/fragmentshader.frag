#version 460 core

out vec4 FragColor;

uniform sampler2D u_Texture0;
uniform float u_AmbLight;
uniform bool u_IsLightSource;

in vec2 v_TexCoord;
in vec3 v_Normal;


struct Ray {
    vec3 origin;
    vec3 direction;
    int bounceCount;
    bool hitLightSource;
    vec3 color;
};

void main() {
    if (u_IsLightSource) {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        FragColor = (u_AmbLight + (1.0 - u_AmbLight) * max(v_Normal.z, 0.1)) * texture(u_Texture0, v_TexCoord);
    }
};
