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

#ifndef PIX2D_SETTINGS_H
#define PIX2D_SETTINGS_H

#include "forwards.h"

NS_PIX2D_BEGIN

namespace settings {
    extern const char *seasons_json_filename;   /// seasons metadata json file
    extern const char *level_test_filename;

    /// CCNode Tags
    enum {
        kTagPhysicsLayer = 1,
        kTagPath,
        kTagRopeSpriteBatchNode,
        kTagTouchListener,
        kTagPhysicsNodeSprite,
        /// Debug tag
        kTagDebugLayer,
        kTagDebugConsole
    };

    /// Layer Z order
    enum {
        kZOrderPhysicsLayer = 0,
        kZOrderDebugLayer
    };

    /// Sprite Z order (The larger the z order number is, the later the node will be drawn)
    /*
    enum {
        kZOrderAnchor = 0,
        kZOrderHero
    };
    */

    /// Touch priority
    enum {
        /// kTouchPriorityTouchListener = 10,
        kTouchPriorityPhysicsLayer = 1,
        /// kTouchPriorityDebugLayer,
    };

    /// Customs shaders keys
    extern const char *kShader_PositionTexture_uColor_uTime;
    extern const char *kShader_Grayscale;
};

NS_PIX2D_END
#endif // PIX2D_SETTINGS_H
