return {
    emitterType = kCCParticleModeGravity, -- kCCParticleModeGravity, kCCParticleModeRadius
    angle = 0.0,
    angleVariance = 360.0,
    duration = 0.10, -- kCCParticleDurationInfinity 
    maxParticules = 15,
    blendFuncDestination = GL_ONE_MINUS_SRC_ALPHA,
    blendFuncSource = GL_ONE_MINUS_SRC_ALPHA,
    blendAdditive = false,
    startColor = {1,1,1,0.25},
    startColorVariance = {0,0,0,0},
    finishColor = {1,1,1,0.35},
    finishColorVariance = {0,0,0,0},
    startSize = 15.0,
    startSizeVariance = 15.0,
    finishSize = 0.0,
    finishSizeVariance = 0.0,
    lifespan = 0.0,
    lifespanVariance = 0.5,
    rotationStart = 0,
    rotationStartVariance = 0,
    rotationEnd = 0,
    rotationEndVariance = 0,
    sourcePosition = {0,0},
    sourcePositionVariance = {0,0},
    textureFileName = '',
    textureImageData = '',
    -- Mode Radius
    maxRadius = 1.0,
    maxRadiusVariance = 1.0,
    minRadius = 1.0,
    rotatePerSecond = 0.0,
    rotatePerSecondVariance = 0.0,
    -- Mode gravity 
    gravity = {0,0},
    speed = 80.0,
    speedVariance = 2.0,
    radialAcceleration = 0.0,
    radialAccelVariance = 0.0,
    tangentialAcceleration = 0.0,
    tangentialAccelVariance = 0.0,
    -- rotationIsDir = false , -- not supported in Lua
}
