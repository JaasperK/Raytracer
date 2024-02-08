#version 460 core

out vec4 FragColor;


// Camera data
uniform vec3 u_CamPosition;
uniform mat4 u_CameraMatrix;

// Light sources
uniform vec3 u_LightSphereCenter;
uniform float u_LightSphereRadius;

in vec3 v_Posistion;
in vec3 v_Normal;
in vec2 v_TexCoord;


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

struct RayInfo {
    bool ditHit;
    float dist;
    vec3 point;
    vec3 normal;
};

RayInfo raySphereIntersect(Ray ray, Sphere sphere) {
    RayInfo info = RayInfo(false, 0.0, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
    vec3 offsetRayOrigin = ray.origin - sphere.center;

    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(offsetRayOrigin, ray.direction);
    float c = dot(offsetRayOrigin, offsetRayOrigin) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        float dist = (-b * sqrt(discriminant)) / (2 * a);

        // ignore cases where ray hits behind the camera
        if (dist >= 0) {
            info.ditHit = true;
            info.dist = dist;
            info.point = ray.origin + ray.direction * dist;
            info.normal = normalize(info.point - sphere.center);
        }
    }

    return info;
}

void main() {
    vec3 focusPointLocal = vec3(gl_FragCoord.xy - 0.5, 1);
	vec3 focusPoint = (inverse(u_CameraMatrix) * vec4(focusPointLocal, 1.0)).xyz;
    
    Ray ray = Ray(u_CamPosition, normalize(focusPoint - u_CamPosition));
    Sphere sphere = Sphere(u_LightSphereCenter, u_LightSphereRadius);
    RayInfo info = raySphereIntersect(ray, sphere);

    if (info.ditHit) {
        FragColor = vec4(0.5, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(0.07, 0.13, 0.17, 1.0);
    }
};
