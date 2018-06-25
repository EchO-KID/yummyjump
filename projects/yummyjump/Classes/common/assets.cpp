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

#include "assets.h"
#include "common/settings.h"
#include <fstream>

/// #include <libwebsockets.h>

#if COCOS2D_DEBUG > 0
//# include <dirent.h>
# include <lua.h>
# include <stdio.h>
#endif

#define BUFFERSIZE 4096 /// libb64 buffer size
#include <b64/decode.h>

#include <errno.h>

NS_PIX2D_BEGIN

/// Since 2.0.4 cocos2d-x uses a new fonts library and we must do some extra work to use custom fonts on iOS and other platforms
/// see http://www.cocos2d-x.org/projects/cocos2d-x/wiki/How_to_Use_Custom_TTF_Font_on_iOS
/// iOS font are defined without path and .ttf extension
/// custom ttf files must be defined in info.plist:
/*
 <key>UIAppFonts</key>
 <array>
 <string>fonts/myfont1.ttf</string>
 <string>fonts/myfont2.ttf</string>
 </array>
*/
std::string Assets::smFonts[] =
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    "RobotoCondensed-Regular",
    "Chewy",
#else
    /// Other platform must define fullpath and .ttf extension
    "fonts/RobotoCondensed-Regular.ttf",
    "fonts/Chewy.ttf",
#endif
};

/// Default font sizes.
float Assets::smFontsSize[] = { 4, 8, 12, 20, 32 };

/// Supported resource resolutions. See http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Multi_resolution_support
Assets::ResourceType Assets::smallResource  =  { CCSizeMake(480, 320),   "sd" };          // iphone3: 480x320
Assets::ResourceType Assets::mediumResource =  { CCSizeMake(1024, 768),  "hd"   };        // ipad: 1024x768
Assets::ResourceType Assets::largeResource  =  { CCSizeMake(2048, 1536), "retina" };      // ipad: retina: 2048x1536
CCSize Assets::designResolutionSize = CCSizeMake(480, 320); /// Width x Height pixel

#if COCOS2D_DEBUG > 0
/// Recursively removing the content of the directory 'path'
void emptyFolder(const std::string &path)
{
    if (DIR *folder = opendir(path.c_str())) {
        while (struct dirent *entry = readdir(folder)) {
            if (strcmp(entry->d_name,".") == 0 ||
                strcmp(entry->d_name,"..") == 0)
                continue;

            std::stringstream buf;
            buf << path << '/' << entry->d_name;
            /// std::stringstream::str() returns a temporary string which is destroy when the expression ends.
            /// So the following expression is wrong and filepath will points to a string destroyed before the next statement.
            /// const char *filepath = buf.str().c_str();
            /// Therefore we have to copy the stringstream buffer in order to used it after the expression is done.
            /// See. http://stackoverflow.com/questions/24011182/recursive-stdstringstream-and-c-str/24011602#24011602
            /// std::string filepath(buf.str());
            const std::string filepath = buf.str();

            if (entry->d_type == DT_DIR)
                emptyFolder(filepath);
            if (remove(filepath.c_str()) == 0)
                CCLOG("File removed: %s", filepath.c_str());
            else
                CCLOGERROR("Can't delete file %s (%s)", filepath.c_str(), strerror(errno));
        }
        closedir(folder);
    } else {
        CCLOGERROR("Can't open directory %s (%s)", path.c_str(), strerror(errno));
    }
}
#endif

bool Assets::enableMutliResolutionSupport()
{
    /// Multi resolution support BEFORE cocos2d-x 2.0.4
    /// The correct resolution is enableds using setResourceDirectory which set the resource directory for the current device's resolution
    /// Shared/common images to all resolutions are stored in the root resources (Resources/GameResources/textures)
    /// See http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Mechanism_of_loading_resources

    /****************************************************************************************************************
     *
     *     Since 2.0.4, cocos2d-x introduced a new multi-resolution support
     *     http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Multi_resolution_support
     *     http://www.cocos2d-x.org/wiki/Detailed_explanation_of_Cocos2d-x_Multi-resolution_adaptation
     *
     *     Set the design resolution: width, height and policy
     *
     *    - kResolutionExactFit -
     *    The entire application is visible in the specified area without trying to preserve the original aspect ratio.
     *    Distortion can occur, and the application may appear stretched or compressed.
     *
     *    - kResolutionNoBorder -
     *    The entire application fills the specified area, without distortion but possibly with some cropping,
     *    while maintaining the original aspect ratio of the application.
     *
     *    - kResolutionShowAll -
     *    The entire application is visible in the specified area without distortion while maintaining the original
     *    aspect ratio of the application. Borders can appear on two sides of the application.
     ****************************************************************************************************************/

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = pDirector->getOpenGLView();
    CCFileUtils &fileUtils = *CCFileUtils::sharedFileUtils();

    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
    CCSize frameSize = pEGLView->getFrameSize();

    /// We select resource according to the frame's height.
    /// If the resource size is different from design resolution size, you need to set contentScaleFactor.
    /// We use the ratio of resource's height to the height of design resolution,
    /// this can make sure that the resource's height could fit for the height of design resolution.

    std::vector<std::string> resOrder = fileUtils.getSearchResolutionsOrder();

    /// GPU max texture size
    GLint maxTextureSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    CCLOG("GPU max texture size: %d", maxTextureSize);

    bool scaledGraphics = false;

    /// set the contentScaleFactor based on the ratio of WIDTH
    if (frameSize.width > mediumResource.size.width && maxTextureSize >= 2048) {
        CCLOG("Select LARGE (ipadhd) resource...");
        resOrder.insert(resOrder.begin(), largeResource.directory);
        /// pDirector->setContentScaleFactor(largeResource.size.width/designResolutionSize.width);
        pDirector->setContentScaleFactor(4.f);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.width > smallResource.size.width  && maxTextureSize >= 1024) {
        CCLOG("Select MEDIUM (hd) resource...");
        resOrder.insert(resOrder.begin(), mediumResource.directory);
        /// pDirector->setContentScaleFactor(mediumResource.size.width/designResolutionSize.width);
        pDirector->setContentScaleFactor(2.f);
        scaledGraphics = frameSize.width > mediumResource.size.width; // have scale down because of max texture size too small?
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else {
        CCLOG("Select SMALL (sd) resource...");
        resOrder.insert(resOrder.begin(), smallResource.directory);
        /// pDirector->setContentScaleFactor(smallResource.size.width/designResolutionSize.width);
        pDirector->setContentScaleFactor(1.f);
        scaledGraphics = frameSize.width > smallResource.size.width; // have scale down because of max texture size too small?
    }

    /// Show an error message if we scaled down the graphics or the max texture size is too small
    if (scaledGraphics || maxTextureSize < 512) {
        CCLOGERROR("Unsupported max texture size: %d",maxTextureSize);
        CCMessageBox("We detected graphics limitation which might prevent the app to work properly or to use HD graphics (max texture too small)", "ERROR");
    }

    /// Bug fix: the resolution directory must have a trailing slash (e.g. hd/ or sd/) or
    /// CCFileUtils::getFullPathForDirectoryAndFilename() will not work correclty on iOS if
    /// both search paths and resolution order are defined (missing slash between directory and filename).
    /// We now use setSearchResolutionsOrder instead of addSearchResolutionsOrder because
    /// addSearchResolutionsOrder simply add the string to the list of the resolution order without adding the trailing slash.
    /// setSearchResolutionOrder takes care of adding the trailing slash if missing.
    /// See. http://discuss.cocos2d-x.org/t/search-paths-and-resolutions-order-issue-on-ios/14424
    fileUtils.setSearchResolutionsOrder(resOrder);

    /// Set the font sizes
    for (int i = 0; i < 4; i++)
        smFontsSize[i]  *= designResolutionSize.width / smallResource.size.width;

    ////////////////// Trace settings... /////////////////
#if COCOS2D_DEBUG > 0

    /// Redirect standard output and error stream to file
    //freopen(fileUtils.getWritablePath().append("cocos2d.log").c_str(), "a+", stdout);
    //freopen(fileUtils.getWritablePath().append("cocos2d.log").c_str(), "a+", stderr);

    /// In debug mode we change the default search path to the following.
    std::vector<std::string> paths;
    paths.push_back(fileUtils.getWritablePath()); /// First we search the writable path root for assets download on-the-fly (see command.h/cpp)
    paths.push_back(fileUtils.getWritablePath().append("lua")); /// Secondly we search in the lua folder below the writable root for lua script
    paths.push_back(""); /// Finally we look in the default resource path (empty string)

    fileUtils.setSearchPaths(paths);

    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetAndroid || platform == kTargetIpad || platform == kTargetIphone) {
        /// Purge the writable folder
        CCLOG("Removing files from the assets staging area (writable path)...");
        /// TODO on mac getWritablePath is "/Users/lzubiaur/Library/Caches/".
        /// So it should not be wipe out but temporary assets should be written in a subfolder
        emptyFolder(fileUtils.getWritablePath());
    }

    CCLOG("Real screen size: %.0fx%.0f", pEGLView->getFrameSize().width, pEGLView->getFrameSize().height);
    CCLOG("Design resolution size: %.0fx%.0f", pEGLView->getDesignResolutionSize().width, pEGLView->getDesignResolutionSize().height);
    CCLOG("Content scale factor: %f", pDirector->getContentScaleFactor());
    CCLOG("Scale x:%f y:%f", pEGLView->getScaleX(), pEGLView->getScaleY());
    CCLOG("Visible origin: x:%.0f y:%.0f",pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y);
    CCLOG("Visible size: %.0fx%.0f", pEGLView->getVisibleSize().width, pEGLView->getVisibleSize().height);

    /// Log the search paths
    std::string searchPath;
    for (const std::string s : fileUtils.getSearchPaths())
        searchPath.append(' ' + s);
    CCLOG("Search path: %s", searchPath.c_str());

    /// Log the search resolution order
    std::string resolutionOrder;
    for (const std::string s : fileUtils.getSearchResolutionsOrder())
        resolutionOrder.append(' ' + s);
    CCLOG("Search resolution order: %s", resolutionOrder.c_str());
    CCLOG("Writeable path: %s", fileUtils.getWritablePath().c_str());
    CCLOG("Lua version: %s",LUA_VERSION);

    /// CCLOG("Websocket version %s",lws_get_library_version());

    /*
     d("top:         %f %f", CVisibleRect::top().x,          CVisibleRect::top().y           );
     d("rightTop:    %f %f", CVisibleRect::rightTop().x,     CVisibleRect::rightTop().y      );
     d("leftTop:     %f %f", CVisibleRect::leftTop().x,      CVisibleRect::leftTop().y       );
     d("left:        %f %f", CVisibleRect::left().x,         CVisibleRect::left().y          );
     d("right:       %f %f", CVisibleRect::right().x,        CVisibleRect::right().y         );
     d("leftBottom:  %f %f", CVisibleRect::leftBottom().x,   CVisibleRect::leftBottom().y    );
     d("rightBottom: %f %f", CVisibleRect::rightBottom().x,  CVisibleRect::rightBottom().y   );
     d("center:      %f %f", CVisibleRect::center().x,       CVisibleRect::center().y        );
     d("bottom:      %f %f", CVisibleRect::bottom().x,       CVisibleRect::bottom().y        );
     */
#endif

    return true;
}

bool Assets::loadCustomShaders()
{
    /// Scrollable texture shader
    {
        CCGLProgram *shader = new CCGLProgram();
        shader->initWithVertexShaderFilename("shaders/shader_PositionTexture_uColor_uTime.vsh", "shaders/shader_PositionTexture_uColor_uTime.fsh");
        shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        shader->link();
        shader->updateUniforms();
        CCShaderCache::sharedShaderCache()->addProgram(shader, settings::kShader_PositionTexture_uColor_uTime);
    }

    /// Grayscale shader
    {
        CCGLProgram *shader = new CCGLProgram();
        shader->initWithVertexShaderFilename("shaders/shader_Grayscale.vsh", "shaders/shader_Grayscale.fsh");
        shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        shader->link();
        shader->updateUniforms();
        CCShaderCache::sharedShaderCache()->addProgram(shader, settings::kShader_Grayscale);
    }

    CHECK_GL_ERROR_DEBUG();

    return true;
}

struct SpriteStruct {
    CCSprite *sprite;
    int name;
};

bool Assets::reloadCustomShaders()
{
    CCLOG("reload custom shaders");
    CCGLProgram *shader = CCShaderCache::sharedShaderCache()->programForKey(settings::kShader_PositionTexture_uColor_uTime);
    shader->reset();
    shader->initWithVertexShaderFilename("shaders/shader_PositionTexture_uColor_uTime.vsh", "shaders/shader_PositionTexture_uColor_uTime.fsh");
    shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    shader->link();
    shader->updateUniforms();

    /// TODO

    CHECK_GL_ERROR_DEBUG();

    return true;
}

std::string Assets::readTextFile(const std::string &filename, bool encrypted)
{
    CCLOG("Start reading data file %s...",filename.c_str());
    if(!filename.length()) {
        CCLOGERROR("ERROR: Can't read file. Filename is invalid (string is empty)");
        return std::string();
    }

    /// Note: no need to call CCFileUtils::fullPathForFilename (done implicitly by getFileData)

    long unsigned int size = 0;
    if (unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(filename.c_str(), "r", &size)) {
        if (size > 0) {
            CCLOG("Read data file sucessfuly. %lu bytes read from %s",size,filename.c_str());
            std::string str;
            if (encrypted) {
                base64::decoder b64;
                std::stringstream in;
                std::stringstream out;
                in.write((char*)data, size);
                b64.decode(in, out);
                str = string(out.str());
            } else {
                str = string((const char *)data, size);
            }
            delete[] data;
            return str;
        } else {
            CCLOGWARN("WARNING: No byte read from file %s",filename.c_str());
        }
    } else {
        CCLOGERROR("ERROR: Can't read data file %s. %s",filename.c_str(),strerror(errno));
    }
    return std::string();
}

bool Assets::writeTextFile(const std::string &filename, const std::string &text)
{
    if(!filename.length()) {
        CCLOGERROR("ERROR: Filename is invalid (string is empty)");
        return false;
    }

    /// libstdc++ (Gnu) has different constructor than libc++ (llvm) and does not accept a std::string as parameter
    std::ofstream out(CCFileUtils::sharedFileUtils()->getWritablePath().append(filename).c_str(), std::ofstream::out);

    out << text;
    /// out << '\n';
    out.flush();

    bool rc = true;
    if (out.bad())
        rc = false;

    out.close();

    return rc;
}

NS_PIX2D_END
