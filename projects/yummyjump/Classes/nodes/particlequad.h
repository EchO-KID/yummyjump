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

#ifndef PIX2D_PARTICLEQUAD_H
#define PIX2D_PARTICLEQUAD_H

#include "forwards.h"

NS_PIX2D_BEGIN

class ParticleQuad : public CCParticleSystemQuad
{
public:
    ParticleQuad();
    virtual ~ParticleQuad();

    /// @brief create a particle emiter from a plist file using a texture "full path"
    static ParticleQuad* create(CCParticleBatchNode *batch, const char *plistfile);

    /// Factory helpers
    /// @brief create a star explosion particle using the texture from the batch node
    static ParticleQuad* createStarsExplosion(CCParticleBatchNode *batch);
    static ParticleQuad* createStarsExplosion2(CCParticleBatchNode *batch);
    /// TODO
    static ParticleQuad* createStarsExplosion(CCParticleBatchNode *batch, const char *frameName);
};

NS_PIX2D_END

#endif /* PIX2D_PARTICLEQUAD_H */
