#version 460 core

out vec4 FragColor;

uniform sampler2D u_Texture0;
uniform float u_AmbLight;
uniform bool u_IsLightSource;
uniform int u_RaysPerPixel;
uniform int u_MaxBounces;
uniform vec3 u_CamPosition;

in vec2 v_TexCoord;
in vec3 v_Normal;


struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Sphere {
    vec3 center;
    float radius;
};

struct Triangle {
    vec3 a, b, c;
    vec3 na,nb, nc;
};

struct Hit {
    bool hit;
    float dist;
    vec3 point;
    vec3 normal;
};

Hit raySphereIntersect() {
    Hit hit;
    //TODO

    return hit;
}

vec3 trace(Ray ray) {
    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    vec3 rayColor = vec3(1.0, 1.0, 1.0);

    for (int bounceCount = 0; bounceCount <= u_MaxBounces; bounceCount++) {
        // TODO
    }
    
    return incomingLight;
}

void main() {
    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    Ray ray;

    for (int i = 0; i < u_RaysPerPixel; i++) {
        ray.origin = u_CamPosition;
        ray.direction = normalize(vec3(0.0, 0.0, 1.0) - ray.origin);

        incomingLight += trace(ray);
    }

    vec3 pixelColor = incomingLight / u_RaysPerPixel;
    FragColor = vec4(pixelColor, 1.0);
};
