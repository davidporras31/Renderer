#ifndef MATH_GLSL
#define MATH_GLSL

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define EPSILON 1e-6

// useful math functions for shaders not provided by GLSL
float saturate(float x) {
    return clamp(x, 0.0, 1.0);
}
float remap(float value, float oldMin, float oldMax, float newMin, float newMax) {
    return newMin + (value - oldMin) * (newMax - newMin) / (oldMax - oldMin);
}
float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
float rand(vec3 co) {
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233, 45.164))) * 43758.5453);
}
float angleBetween(vec3 v1, vec3 v2) {
    float dotProd = dot(normalize(v1), normalize(v2));
    return acos(clamp(dotProd, -1.0, 1.0));
}
float smoothMin(float a, float b, float k) {
    float h = max(k - abs(a - b), 0.0) / k;
    return min(a, b) - h * h * k * 0.25;
}
float smoothMax(float a, float b, float k) {
    float h = max(k - abs(a - b), 0.0) / k;
    return max(a, b) + h * h * k * 0.25;
}
float inverseLerp(float a, float b, float value) {
    return (value - a) / (b - a);
}
float quadraticBezier(float t, float p0, float p1, float p2) {
    float u = 1.0 - t;
    return u * u * p0 + 2.0 * u * t * p1 + t * t * p2;
}
float cubicBezier(float t, float p0, float p1, float p2, float p3) {
    float u = 1.0 - t;
    return u * u * u * p0 + 3.0 * u * u * t * p1 + 3.0 * u * t * t * p2 + t * t * t * p3;
}
float degToRad(float degrees) {
    return degrees * ( PI / 180.0);
}
float radToDeg(float radians) {
    return radians * (180.0 / PI );
}
float hermite(float t, float p0, float m0, float p1, float m1) {
    float t2 = t * t;
    float t3 = t2 * t;
    return (2.0 * t3 - 3.0 * t2 + 1.0) * p0 + (t3 - 2.0 * t2 + t) * m0 + (-2.0 * t3 + 3.0 * t2) * p1 + (t3 - t2) * m1;
}
float smootherstep(float edge0, float edge1, float x) {
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}
float easeInOut(float t) {
    return t < 0.5 ? 2.0 * t * t : -1.0 + (4.0 - 2.0 * t) * t;
}
float perlinNoise(vec2 uv) {
    vec2 i = floor(uv);
    vec2 f = fract(uv);
    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}
float fractalNoise(vec2 uv, int octaves, float persistence) {
    float total = 0.0;
    float frequency = 1.0;
    float amplitude = 1.0;
    for (int i = 0; i < octaves; i++) {
        total += perlinNoise(uv * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= persistence;
    }
    return total;
}
float simplexNoise(vec2 uv) {
    // Implementation of 2D Simplex Noise
    const vec2 C = vec2(0.211324865405187, 0.366025403784439); // (3.0 - sqrt(3.0)) / 6.0
    vec2 i = floor(uv + dot(uv, C.yy));
    vec2 x0 = uv - i + dot(i, C.xx);
    vec2 i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec2 x1 = x0 - i1 + C.xx;
    vec2 x2 = x0 - 1.0 + 2.0 * C.xx;
    vec3 p = vec3(0.0);
    p += max(0.5 - dot(x0, x0), 0.0) * max(0.5 - dot(x0, x0), 0.0) * rand(i);
    p += max(0.5 - dot(x1, x1), 0.0) * max(0.5 - dot(x1, x1), 0.0) * rand(i + i1);
    p += max(0.5 - dot(x2, x2), 0.0) * max(0.5 - dot(x2, x2), 0.0) * rand(i + vec2(1.0, 1.0));
    return p.x * 70.0; // Scale to [-1, 1]
}

mat4 lookAt(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat4(
        vec4(s, 0.0),
        vec4(u, 0.0),
        vec4(-f, 0.0),
        vec4(eye, 1.0)
    );
}
#endif // MATH_GLSL