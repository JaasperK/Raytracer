#version 460 core

out vec4 FragColor;

// Raytracer settings
uniform vec3 u_BackgroundColor;
uniform int u_RaysPerPixel;
uniform int u_MaxBounces;
// Camera data
uniform vec3 u_CamPosition;
uniform mat4 u_CameraMatrix;
uniform vec2 u_Resolution;
// Spheres
uniform int u_NumSpheres;

uniform vec3 u_LightSphereCenter;
uniform float u_LightSphereRadius;
uniform vec3 u_LightSphereColor;

uniform vec3 u_Sphere1Center;
uniform float u_Sphere1Radius;
uniform vec3 u_Sphere1Color;

uniform vec3 u_Sphere2Center;
uniform float u_Sphere2Radius;
uniform vec3 u_Sphere2Color;

uniform vec3 u_Sphere3Center;
uniform float u_Sphere3Radius;
uniform vec3 u_Sphere3Color;

uniform vec3 u_Sphere4Center;
uniform float u_Sphere4Radius;
uniform vec3 u_Sphere4Color;

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Sphere {
    vec3 center;
    float radius;
    vec3 color;
    bool isLight;
};

// Setup spheres
Sphere spheres[5] = Sphere[5](
    Sphere(u_LightSphereCenter, u_LightSphereRadius, u_LightSphereColor, true),
    Sphere(u_Sphere1Center, u_Sphere1Radius, u_Sphere1Color, false),
    Sphere(u_Sphere2Center, u_Sphere2Radius, u_Sphere2Color, false),
    Sphere(u_Sphere3Center, u_Sphere3Radius, u_Sphere3Color, false),
    Sphere(u_Sphere4Center, u_Sphere4Radius, u_Sphere4Color, false)
    );

Sphere lightsource = spheres[0];

struct RayInfo {
    bool didHit;
    bool hitLight;
    float dist;
    vec3 point;
    vec3 normal;
    vec3 color;
};

RayInfo raySphereIntersect(Ray ray, Sphere sphere) {
    RayInfo info = RayInfo(false, false, 0.0, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
    vec3 raySphereOffset = ray.origin - sphere.center;

    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(raySphereOffset, ray.direction);
    float c = dot(raySphereOffset, raySphereOffset) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        // only nearest intersection
        float dist = (-b - sqrt(discriminant)) / (2 * a);

        // ignore cases where ray hits behind the camera
        if (dist >= 0) {
            info.didHit = true;
            info.hitLight = sphere.isLight;
            info.dist = dist;
            info.point = ray.origin + ray.direction * dist;
            info.normal = normalize(info.point - sphere.center);
            info.color = sphere.color;
        }
    }

    return info;
};

// Test ray against all spheres in the scene
RayInfo closestRayCollision(Ray ray) {
    RayInfo closest = RayInfo(false, false, 10000000.0, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));

    for (int i = 0; i < u_NumSpheres; i++) {
        RayInfo temp = raySphereIntersect(ray, spheres[i]);
        if (temp.didHit && temp.dist < closest.dist) {
            closest = temp;
        }
    }

    return closest;
};

//struct RayInfo {
//    bool didHit;
//    bool hitLight;
//    float dist;
//    vec3 point;
//    vec3 normal;
//    vec3 color;
//};

// Raytracing:
// 1. Find closest intersection of ray.
//    1.1. if (!didHit) return backgrcolor
// 2. calculate ray color
// 3. calculate ray to light
//    3.1 if (!didHit) return black
//    3.2 else return ray color


vec3 trace(Ray ray) {
    RayInfo info = closestRayCollision(ray);

    if (!info.didHit) {
        if (info.hitLight) {
            return info.color;
        }
        return u_BackgroundColor;
    }

    float intensity = dot(-ray.direction, info.normal);
    vec3 color = intensity * info.color;
    
    ray.origin = info.point;
    ray.direction = normalize(lightsource.center - info.point);

    info = closestRayCollision(ray);

    if (!info.hitLight) {
        return vec3(0.0, 0.0, 0.0);
    }

    return color;
};

void main() {
    // coord: [-1; 1]
    vec2 coord = ((gl_FragCoord.xy / u_Resolution) - 0.5) * 2;
    // cam is at (0,0,5), looking in dir (0,0,-1)
    vec3 dir = vec3(coord, -1.0);
    
    Ray ray = Ray(u_CamPosition, normalize(dir));
    
    vec3 pixelColor = trace(ray);
    FragColor = vec4(pixelColor, 1.0);

    //RayInfo info0 = raySphereIntersect(ray, spheres[0]);
    //RayInfo info1 = raySphereIntersect(ray, spheres[1]);
    //RayInfo info2 = raySphereIntersect(ray, spheres[2]);
    //RayInfo info3 = raySphereIntersect(ray, spheres[3]);
    //RayInfo info4 = raySphereIntersect(ray, spheres[4]);
    //
    //RayInfo inf[] = { info0, info1, info2, info3, info4 };
    //
    //if (!info0.didHit && !info1.didHit && !info2.didHit && !info3.didHit && !info4.didHit) {
    //    FragColor = vec4(u_BackgroundColor, 1.0);
    //} else {
    //    for (int i = 0; i < u_NumSpheres; i++) {
    //        if (inf[i].didHit) {
    //            FragColor = vec4(inf[i].color, 1.0);
    //            break;
    //        }
    //    }  
    //} 
};
