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

#ifndef PIX2D_ASSETS_H
#define PIX2D_ASSETS_H

#include "forwards.h"

#define LabelTTF(__STR__,__NAME__,__SIZE__) CCLabelTTF::create(__STR__, Assets::font(__NAME__), Assets::fontSize(__SIZE__));

NS_PIX2D_BEGIN

class Assets {
public:
    /// Resource type supported: sd, hd and retina
    struct ResourceType {
        cocos2d::CCSize size;   /// The resource size (480x320, 1024x768 or 2048x1536)
        char directory[16];     /// The resource directory (sd, hd or retina)
    };

    enum FontTag {
        kRoboto = 0,
        kChewy,
        // kAnnieUseYourTelescope,
        // kTrashHand,
    };

    /// Fonts size are not hardcoded in an enum but rather stored in a array
    /// because we dynamically adjust the fonts size according to device resolution
    enum FontSizeTag {
        kFontSizeTiny = 0,
        kFontSizeSmall,
        kFontSizeMedium,
        kFontSizeLarge,
        kFontSizeHuge
    };

    /**
     * @brief Write string `test` to file `filename`. Returns true on success or false otherwise.
     * The "writable path" is implicitly prefixed to `filename`.
     */
    static bool writeTextFile(const std::string &filename, const std::string &text);
    /**
     * @brief Returns the content of the file `filename` or an empty string on error. This call fullPathFromFilename implicitly on `filename`.
     * It call getFileData so it's cross-platform (e.g. on android it reads in the apk zip file).
     */
    static std::string readTextFile(const std::string &filename, bool encrypted = false);

    static bool enableMutliResolutionSupport();
    static bool loadCustomShaders();
    /** @brief Reload all custom shaders. This is needed on Android when the app is back on foreground (see proj.android/jni/hellolua/main.cpp). */
    static bool reloadCustomShaders();

    static inline const char *font(FontTag tag) { return smFonts[tag].c_str(); }
    static inline float fontSize(FontSizeTag tag) { return smFontsSize[tag]; }

protected:
    /// Multi-resolution support
    static ResourceType smallResource;
    static ResourceType mediumResource;
    static ResourceType largeResource;
    static cocos2d::CCSize designResolutionSize;
    /// Font support
    static std::string smFonts[2];
    static float smFontsSize[5];
};

NS_PIX2D_END
#endif // PIX2D_ASSETS_H
