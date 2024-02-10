#version 460 core

out vec4 FragColor;

// Raytracer settings
uniform int u_RaysPerPixel;
uniform int u_MaxBounces;
// Camera data
uniform vec3 u_CamPosition;
uniform mat4 u_CameraMatrix;
uniform vec2 u_Resolution;
// Spheres
uniform vec3 u_LightSphereCenter;
uniform float u_LightSphereRadius;
uniform vec3 u_LightSphereColor;

uniform vec3 u_Sphere1Center;
uniform float u_Sphere1Radius;
uniform vec3 u_Sphere1Color;

uniform vec3 u_Sphere2Center;
uniform float u_Sphere2Radius;
uniform vec3 u_Sphere2Color;

uniform int u_NumSpheres;


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
    vec3 color;
};

// Setup spheres
Sphere spheres[3] = Sphere[3](
    Sphere(u_LightSphereCenter, u_LightSphereRadius, u_LightSphereColor),
    Sphere(u_Sphere1Center, u_Sphere1Radius, u_Sphere1Color),
    Sphere(u_Sphere2Center, u_Sphere2Radius, u_Sphere2Color)
    );

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
        // only nearest intersection
        float dist = (-b - sqrt(discriminant)) / (2 * a);

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

RayInfo closestRayCollision(Ray ray) {
    RayInfo closest = RayInfo(false, 0.0, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));

    for (int i = 0; i < u_NumSpheres; i++) {
        RayInfo temp = raySphereIntersect(ray, spheres[i]);
        if (temp.ditHit && temp.dist < closest.dist) {
            closest = temp;
        }
    }

    return closest;
}


vec3 trace(Ray ray) {
    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    vec3 rayColor = vec3(1.0, 1.0, 1.0);

    for (int bounceCount = 0; bounceCount <= u_MaxBounces; bounceCount++) {
        RayInfo info = closestRayCollision(ray);
    }
    
    return incomingLight;
}

void main() {
    // coord: [-1; 1]
    vec2 coord = ((gl_FragCoord.xy / u_Resolution) - 0.5) * 2;
    // cam is at (0,0,5), looking in dir (0,0,-1)
    vec3 dir = vec3(coord, -1.0);
    
    Ray ray = Ray(u_CamPosition, normalize(dir));
    RayInfo info = raySphereIntersect(ray, spheres[0]);

    if (info.ditHit) {
        FragColor = vec4(coord, 0.0, 1.0);
    } else {
        FragColor = vec4(0.07, 0.13, 0.17, 1.0);
    }

    vec3 incomingLight = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < u_RaysPerPixel; i++) {
        incomingLight += trace(ray);
    }

    vec3 pixelColor = incomingLight / u_RaysPerPixel;
    //FragColor = vec4(pixelColor, 1.0);
};
