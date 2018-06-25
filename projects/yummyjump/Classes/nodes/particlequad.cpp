/**
Copyright (C) 2012-2015 Laurent Zubiaur - voodoocactus.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 **/

#include "nodes/particlequad.h"
#include "common/visiblerect.h"

NS_PIX2D_BEGIN

ParticleQuad::ParticleQuad()
{
    CCLOG("Create new particle batch");
}

ParticleQuad::~ParticleQuad()
{
    CCLOG("Destroy particle batch");
}

ParticleQuad* ParticleQuad::create(CCParticleBatchNode *batch, const char *plistfile)
{
    ParticleQuad *particle = new ParticleQuad();
    particle->autorelease();

    particle->m_sPlistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistfile);
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(particle->m_sPlistFile.c_str());
    CCAssert( dict != NULL, "Particles: plist file not found");

    /// Texture filename is not prefixed with the fullpath by default
    /// so we do it in the dictionary before calling the init method
    const char *textureFileName = dict->valueForKey("textureFileName")->getCString();
    std::string textureFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(textureFileName);
    dict->setObject(CCString::create(textureFullPath), "textureFileName");

    if (! particle->initWithDictionary(dict, "")) {
        CC_SAFE_RELEASE_NULL(particle);
    }

    dict->release();

    /// batch->addChild(particle);
    return particle;
}

ParticleQuad* ParticleQuad::createStarsExplosion(CCParticleBatchNode *batch)
{
    ParticleQuad *particle = new ParticleQuad();
    particle->autorelease();

    /// Total particles
    float maxParticules = 100;
    particle->initWithTotalParticles(maxParticules);

    /// Duration
    particle->setDuration(.05f);
    /// particle->setDuration(kCCParticleDurationInfinity);
    /// Mode
    particle->setEmitterMode(kCCParticleModeGravity);
    /// Life
    particle->setLife(.05f);
    particle->setLifeVar(.60f);
    /// Size
    particle->setStartSize(15);
    particle->setStartSizeVar(.0f);
    particle->setEndSize(10);
    particle->setEndSizeVar(5);

    // Gravity Mode: gravity
    particle->setGravity(ccp(0,0));

    // Gravity mode: radial acceleration
    particle->setRadialAccel(0);
    particle->setRadialAccelVar(0);

    // Gravity mode: speed of particles
    particle->setSpeed(80);
    particle->setSpeedVar(.0f);

    // angle
    particle->setAngle(.0f);
    particle->setAngleVar(360);

    // emitter position
    particle->setPosition(VisibleRect::center());
    particle->setPosVar(CCPointZero);

    // emitter blending mode
    particle->setBlendAdditive(false);
    /// "Overlay" blending mode
    /// particle->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE});

        // emission Rate
    particle->setEmissionRate(maxParticules / particle->getLife());  /// total particle / life

    // color of particles
    particle->setStartColor(ccc4f(1,1,0,1));
    particle->setStartColorVar(ccc4f(0,0,0,0));
    particle->setEndColor(ccc4f(1,1,0,0));
    particle->setEndColorVar(ccc4f(0,0,0,0));

    // emiter texture
    particle->setTexture(batch->getTexture());

    particle->setAutoRemoveOnFinish(true);

    /// Add to the batch node
    batch->addChild(particle);

    return particle;
}

ParticleQuad* ParticleQuad::createStarsExplosion2(CCParticleBatchNode *batch)
{
    ParticleQuad *particle = new ParticleQuad();
    particle->autorelease();

    /// Total particles
    float maxParticules = 15;
    particle->initWithTotalParticles(maxParticules);

    /// Duration
    particle->setDuration(.2f);
    /// particle->setDuration(kCCParticleDurationInfinity);
    /// Mode
    particle->setEmitterMode(kCCParticleModeGravity);
    /// Life
    particle->setLife(.0f);
    particle->setLifeVar(.50f);
    /// Size
    particle->setStartSize(30);
    particle->setEndSize(25);
    particle->setEndSizeVar(0);

    // Gravity Mode: gravity
    particle->setGravity(ccp(0,0));

    // Gravity mode: radial acceleration
    particle->setRadialAccel(0);
    particle->setRadialAccelVar(0);

    // Gravity mode: speed of particles
    particle->setSpeed(235);
    particle->setSpeedVar(2.0f);

    // angle
    particle->setAngle(.0f);
    particle->setAngleVar(360);

    // emitter position
    particle->setPosition(VisibleRect::center());
    particle->setPosVar(ccp(-15,-13));

    // emitter blending mode
    particle->setBlendAdditive(false);
    /// "Overlay" blending mode
    /// particle->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE});

    // emission Rate
    particle->setEmissionRate(maxParticules / particle->getLife());  /// total particle / life

    // color of particles
    particle->setStartColor(ccc4f(1,1,1,.24f));
    particle->setStartColorVar(ccc4f(0,0,0,0));
    particle->setEndColor(ccc4f(1,1,0,.35f));
    particle->setEndColorVar(ccc4f(1,1,1,0));

    // emiter texture
    particle->setTexture(batch->getTexture());

    particle->setAutoRemoveOnFinish(true);

    /// Add to the batch node
    batch->addChild(particle);

    return particle;
}

/// TODO
ParticleQuad* createStarsExplosion(CCParticleBatchNode *batch, const char *frameName)
{
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
    CCAssert(frame, "Sprite frame does not exists");

    ParticleQuad *particle = ParticleQuad::createStarsExplosion(batch);
    particle->setTextureWithRect(frame->getTexture(), frame->getRect());

    return particle;
}

NS_PIX2D_END
