//define renderer parameters using Xmacro
// the macro takes three arguments: type, name, default value
#ifndef RENDERER_PARAMETERS
#define RENDERER_PARAMETERS(type, name, defaultValue)
#endif
// window parameters
RENDERER_PARAMETERS(unsigned int, windowWidth, 800)
RENDERER_PARAMETERS(unsigned int, windowHeight, 600)
RENDERER_PARAMETERS(bool, vsyncEnabled, true)
RENDERER_PARAMETERS(bool, fullscreenEnabled, false)
RENDERER_PARAMETERS(bool, borderlessWindowEnabled, false)
RENDERER_PARAMETERS(unsigned int, frameRateLimit, 60)   // -1 for unlimited
// camera parameters
RENDERER_PARAMETERS(float, cameraFOV, 45.0f)
// antialiasing parameters
RENDERER_PARAMETERS(bool, msaaEnabled, true)
RENDERER_PARAMETERS(unsigned int, msaaSamples, 4)
RENDERER_PARAMETERS(bool, fxaaEnabled, false)
// lighting parameters
RENDERER_PARAMETERS(unsigned int, maxLights, 100)
// shadow parameters
RENDERER_PARAMETERS(bool, shadowsEnabled, true)
RENDERER_PARAMETERS(unsigned int, shadowMapResolution, 2048)
RENDERER_PARAMETERS(float, shadowBias, 0.005f)
RENDERER_PARAMETERS(unsigned int, numCascades, 4)
// post-processing parameters
RENDERER_PARAMETERS(float, exposure, 1.0f)
RENDERER_PARAMETERS(float, gamma, 2.2f)
RENDERER_PARAMETERS(bool, bloomEnabled, true)
RENDERER_PARAMETERS(float, bloomIntensity, 1.0f)
RENDERER_PARAMETERS(bool, motionBlurEnabled, true)
RENDERER_PARAMETERS(float, motionBlurIntensity, 1.0f)
RENDERER_PARAMETERS(bool, depthOfFieldEnabled, true)
RENDERER_PARAMETERS(bool, ssaoEnabled, true)
RENDERER_PARAMETERS(float, ssaoRadius, 0.5f)
RENDERER_PARAMETERS(float, ssaoBias, 0.025f)
RENDERER_PARAMETERS(float, ssaoIntensity, 1.0f)
RENDERER_PARAMETERS(bool, screenspaceReflectionsEnabled, true)