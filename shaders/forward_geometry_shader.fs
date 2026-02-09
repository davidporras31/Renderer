#version 430 core

struct Material {
    vec3 albedo;
    sampler2D albedoMap;
    float metallic;
    sampler2D metallicMap;
    float roughness;
    sampler2D roughnessMap;
    float ao;
    sampler2D aoMap;
    vec3 emissive;
    sampler2D emissiveMap;
    sampler2D normalMap;
};

struct Light {
    vec4 position;      //xyz = position, w = type
    vec4 direction;     //alaign by 4 bytes, w = unused
    vec4 color;
    vec4 data;          //data for light type spec
};

layout(std140, binding = 0) uniform LightDataUBO {
    Light lights[16];
    Light count;
};

in vec2 uv;
in vec3 normal;
in vec3 worldPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;

vec4 getAlbedo() {
    return material.albedo.x != -1 ? vec4(material.albedo, 1.0) : texture(material.albedoMap, uv);
}
float getMmetallic() {
    return material.metallic != -1 ? material.metallic : texture(material.metallicMap, uv).r;
}
float getRoughness() {
    return material.roughness != -1 ? material.roughness : texture(material.roughnessMap, uv).r;
}
float getAnbientOclusion() {
    return material.ao != -1 ? material.ao : texture(material.aoMap, uv).r;
}
vec3 getEmissive() {
    return material.emissive.x != -1 ? material.emissive : texture(material.emissiveMap, uv).rgb;
}
vec3 getNormal() {
    return texture(material.normalMap, uv).rgb;
}

const float PI = 3.14159265359;

// Fresnel (Schlick approximation)
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Normal Distribution Function (GGX / Trowbridge-Reitz)
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

// Geometry function (Schlick-GGX)
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    return NdotV / (NdotV * (1.0 - k) + k);
}

// Smith’s method
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 calculatePointLight(Light light, vec3 N, vec3 V, vec3 P, vec3 albedo, float metallic, float roughness) {
    vec3 L = normalize(light.position.xyz - worldPos);
    vec3 H = normalize(V + L);

    float distance = length(light.position.xyz - worldPos);
    float attenuation = clamp(1.0 - distance / light.data.x, 0.0, 1.0);
    attenuation *= attenuation; // smoother falloff

    vec3 radiance = light.color.rgb * attenuation;

    // Base reflectivity
    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = (1.0 - kS) * (1.0 - metallic);

    float NdotL = max(dot(N, L), 0.0);
    if (NdotL <= 0.0)
        return vec3(0.0);

    return (kD * albedo / PI + specular) * radiance * NdotL;
}

vec3 calculateDirectionalLight(Light light, vec3 N, vec3 V, vec3 P, vec3 albedo, float metallic, float roughness) {
    vec3 L = normalize(light.direction.xyz);
    vec3 H = normalize(V + L);

    float NdotL = max(dot(N, L), 0.0);
    if (NdotL <= 0.0)
        return vec3(0.0);

    // Base reflectivity
    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    // Cook-Torrance BRDF
    float D = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);


    vec3 numerator    = D * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * NdotL + 0.0001;
    vec3 specular     = numerator / denominator;

    // Energy conservation
    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

    vec3 diffuse = kD * albedo / PI;

    // Final lighting
    return (diffuse + specular) * light.color.rgb * NdotL;
}

vec3 calculateLighting(vec3 N, vec3 V, vec3 P, vec3 albedo, float metallic, float roughness) {
    vec3 result = vec3(0.0);
    for(int i = 0; i < count.data.r; ++i) {
        Light light = lights[i];

        float type = light.position.w;

        // Simple diffuse lighting calculation
        if(type == 0) //directionnal light
        {
            result += calculateDirectionalLight(light, N, V, P, albedo, metallic, roughness);
        } else if(type == 1)  //point light
        {
            result += calculatePointLight(light, N, V, P, albedo, metallic, roughness);
        } else if(type == 2) //spot light
        {

        } else if(type == 3) //area light
        {

        }
    }
    return result;
}

void main() {
    vec3 N = normalize(normal);
    vec3 V = normalize(viewPos - worldPos);

    vec3 albedo = getAlbedo().rgb;
    float metallic = getMmetallic();
    float roughness = getRoughness();

    vec3 color = calculateLighting(N, V, worldPos, albedo, metallic, roughness);

    vec3 ambient = albedo * getAnbientOclusion() * 0.03;
    color += ambient;
    color += getEmissive();

    FragColor = vec4(color, 1.0);
}