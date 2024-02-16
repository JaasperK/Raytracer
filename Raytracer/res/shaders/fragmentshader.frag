#version 460 core

out vec4 FragColor;

// Raytracer settings
uniform int u_RaysPerPixel;
uniform int u_MaxBounces;
uniform int u_Frame;
uniform vec3 u_EnvLight;

// Camera settings
uniform mat4 u_CameraMatrix;
uniform vec3 u_CamPosition;
uniform vec2 u_Resolution;

// Sphere data
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
    vec3 emittedLight;
};

// Setup spheres
Sphere spheres[5] = Sphere[5](
    Sphere(u_LightSphereCenter, u_LightSphereRadius, u_LightSphereColor, vec3(1, 1, 1)),
    Sphere(u_Sphere1Center, u_Sphere1Radius, u_Sphere1Color, vec3(0, 0, 0)),
    Sphere(u_Sphere2Center, u_Sphere2Radius, u_Sphere2Color, vec3(0, 0, 0)),
    Sphere(u_Sphere3Center, u_Sphere3Radius, u_Sphere3Color, vec3(0, 0, 0)),
    Sphere(u_Sphere4Center, u_Sphere4Radius, u_Sphere4Color, vec3(0, 0, 0))
    );

Sphere lightsource = spheres[0];

struct RayInfo {
    bool didHit;
    float dist;
    vec3 point;
    vec3 normal;
    vec3 color;
    bool hitLight;
    vec3 emittedLight;
};

// PCG (permuted congruential generator). From:
// www.pcg-random.org and www.shadertoy.com/view/XlGcRh
uint NextRandom(inout uint state)
{
	state = state * 747796405 + 2891336453;
	uint result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
	result = (result >> 22) ^ result;
	return result;
}

float RandomValue(inout uint state)
{
	return NextRandom(state) / 4294967295.0; // 2^32 - 1
}

// Random value in normal distribution (with mean=0 and sd=1)
float RandomValueNormalDistribution(inout uint state)
{
	// From: https://stackoverflow.com/a/6178290
	float theta = 2 * 3.1415926 * RandomValue(state);
	float rho = sqrt(-2 * log(RandomValue(state)));
	return rho * cos(theta);
}

// Calculate a random direction
vec3 RandomDirection(inout uint state)
{
	// From: https://math.stackexchange.com/a/1585996
	float x = RandomValueNormalDistribution(state);
	float y = RandomValueNormalDistribution(state);
	float z = RandomValueNormalDistribution(state);
	return normalize(vec3(x, y, z));
}

vec2 RandomPointInCircle(inout uint rngState)
{
	float angle = RandomValue(rngState) * 2 * 3.14159;
	vec2 pointOnCircle = vec2(cos(angle), sin(angle));
	return pointOnCircle * sqrt(RandomValue(rngState));
}

RayInfo raySphereIntersect(Ray ray, Sphere sphere) {
    RayInfo info = RayInfo(false, 10000000, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), false, vec3(0, 0, 0));
    vec3 raySphereOffset = ray.origin - sphere.center;

    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(raySphereOffset, ray.direction);
    float c = dot(raySphereOffset, raySphereOffset) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        // only nearest intersection
        float dist = (-b - sqrt(discriminant)) / (2 * a);

        // ignore cases where ray hits behind the camera
        if (dist >= 0.0) {
            info.didHit = true;
            info.dist = dist;
            info.point = ray.origin + ray.direction * dist;
            info.normal = normalize(info.point - sphere.center);
            info.color = sphere.color;
            info.hitLight = sphere.emittedLight != vec3(0, 0, 0);
            info.emittedLight = sphere.emittedLight;
        }
    }

    return info;
};

// Test ray against all spheres in the scene
RayInfo closestRayCollision(Ray ray) {
    RayInfo closest = RayInfo(false, 10000000, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), false, vec3(0, 0, 0));

    for (int i = 0; i < u_NumSpheres; i++) {
        RayInfo temp = raySphereIntersect(ray, spheres[i]);
        if (temp.didHit && temp.dist < closest.dist) {
            closest = temp;
        }
    }

    return closest;
};


vec3 trace(Ray ray, inout uint seed) {
    vec3 light = vec3(0, 0, 0);
    vec3 color = vec3(1, 1, 1);

    for (int bounceCount = 0; bounceCount <= u_MaxBounces; bounceCount++) {
        RayInfo info = closestRayCollision(ray);        
        if (!info.didHit) {
            light += u_EnvLight * color;
            break;
        }

        // Cast shadow ray
        RayInfo shadow = closestRayCollision(Ray(info.point, normalize(lightsource.center - info.point)));
        if (!shadow.hitLight) {
            return info.emittedLight;
        }


        // Update light
        if (info.hitLight) {
            light += info.emittedLight * color;
            return light;
        }

        // Update ray
        ray.origin = info.point;
        vec3 specularDir = normalize(reflect(ray.direction, info.normal));
        vec3 diffuseDir = RandomDirection(seed);  // is normalized
        if (dot(diffuseDir, info.normal) < 0) {  // if diffuseDir goes into the sphere
            diffuseDir *= -1;
        }
        float intensity = max(0, dot(-ray.direction, info.normal));
        ray.direction = mix(diffuseDir, specularDir, intensity);

        color *= intensity * info.color;

    }

    return light;
};

void main() {
    vec3 pixelColor = vec3(0, 0, 0);
    float strength = 0.002;

    // coord: [-1; 1]
    vec2 coord = 2 * (gl_FragCoord.xy / u_Resolution) - 1.0;
    vec3 rayDirection = mat3(u_CameraMatrix) * vec3(coord, 1.0);
    
    // cam is at (0,0,10), looking in dir (0,0,-1)
    Ray ray = Ray(u_CamPosition, normalize(rayDirection));

    vec3 right = normalize(u_CameraMatrix[0].xyz);
    vec3 up = normalize(u_CameraMatrix[1].xyz);
    
    uint rngSeed = uint(gl_FragCoord.x * gl_FragCoord.y + u_Frame * 975230);

    for (int i = 0; i < u_RaysPerPixel; i++) {
        vec2 offset = RandomPointInCircle(rngSeed) * strength;
        ray.origin = u_CamPosition + right * offset.x + up * offset.y;
        pixelColor += trace(ray, rngSeed);
    }

    FragColor = vec4(pixelColor / u_RaysPerPixel, 1.0);
};
