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
/**
 * @file:   command.cpp
 * @author: Laurent Zubiaur
 * @brief:
 */

#include "console/command.h"
/// #include "console/dictmaker.h"
#include <support/base64.h>

/// Remove following includes with yours
#include "debug/debuglayer.h"

/// libcurl
#include <curl/curl.h>

/// mkdir
#include <errno.h>
#include <sys/stat.h>

USING_NS_PIX2D;

NS_PIX2D_CONSOLE_BEGIN

/*
bool Command::reloadLevel()
{
    /// Replace following code with your code to reload the level
    if (CCScene *scene = LevelLoader::createWithData(DebugSettings::getInstance()->levelData.c_str()))
        CCDirector::sharedDirector()->replaceScene(scene);
    return true;
}

bool Command::reloadLevel(const char *data)
{
    /// Replace following code with your code to reload the level
    char *decoded = nullptr;
    base64Decode((unsigned char*)data, strlen(data), (unsigned char**)&decoded);
    if (CCScene *scene = LevelLoader::createWithData(decoded)) {
        CCDirector::sharedDirector()->replaceScene(scene);
        DebugSettings::getInstance()->levelData = std::string(decoded);
    }
    delete decoded;
    return true;
}
*/

/** Original code from CCSpriteFrameCache::addSpriteFramesWithDictionary */
#if false
void Command::replaceSpriteFrames(CCDictionary *pDict, CCTexture2D *pTexture)
{
    CCDictionary *metadataDict = (CCDictionary*)pDict->objectForKey("metadata");
    CCDictionary *framesDict = (CCDictionary*)pDict->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL)
        format = metadataDict->valueForKey("format")->intValue();

    // check the format
    CCAssert(format == 2, "Only format 2 is supported");

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();

        /*
         if (CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str()))
         continue;
         */

        CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
        bool rotated = false;

        // rotation
        if (format == 2) {
            rotated = frameDict->valueForKey("rotated")->boolValue();
        }

        CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
        CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());

        // create frame
        CCSpriteFrame *spriteFrame = new CCSpriteFrame();
        spriteFrame->initWithTexture(pTexture, frame, rotated, offset, sourceSize);
        // add sprite frame
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
        spriteFrame->release();
    }
}
#endif

struct WriteFile {
    std::string filename;
    FILE *stream;
};

/// Recursively create a directory path (aka. mkdir -p)
int mkdir(const char *dir) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp),"%s",dir);
    len = strlen(tmp);
    if(tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for(p = tmp + 1; *p; p++)
        if(*p == '/') {
            *p = 0;
            if (::mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    if (::mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
        return -1;
    }
    return 0;
}

size_t write_curl_data(char *data, size_t size, size_t nmemb, void *userdata)
{
    struct WriteFile *out = (struct WriteFile *)userdata;
    if(out && !out->stream) {
        /// open file for writing. It's better to do it here because the
        /// CURLOPT_WRITEFUNCTION will be call only if the connection was
        /// successful and there's actually data.
        if (size_t idx = out->filename.find_last_of('/')) {
            if (mkdir(out->filename.substr(0, idx).c_str()) != 0) {
                CCLOGERROR("CURLOPT_WRITEFUNCTION: failure, can't create directory path for filename (%s): %s",out->filename.c_str(),strerror(errno));
                return -1;
            }
        }
        out->stream = fopen(out->filename.c_str(), "wb");
        if(!out->stream) {
            CCLOGERROR("CURLOPT_WRITEFUNCTION: failure, can't open file to write (%s): %s",out->filename.c_str(),strerror(errno));
            return -1;
        }
    }
    size_t bytes = fwrite(data, size, nmemb, out->stream);
    if (bytes == size * nmemb) {
        CCLOG("CURLOPT_WRITEFUNCTION: writing %lu bytes to file %s",bytes,out->filename.c_str());
    } else {
        CCLOGERROR("CURLOPT_WRITEFUNCTION: failure, can't write %lu bytes to file (%s): %s",size * nmemb,out->filename.c_str(),strerror(errno));
    }
    return bytes;
}

void Command::refreshAssets(std::string &repo,std::vector<std::string> &assets)
{
    struct WriteFile writeFile = { "", nullptr };

    /// The error buffer used by libcurl to store error messages
    char err_buffer[CURL_ERROR_SIZE];
    /// Init libcurl and get an libcurl easy session
    CURL *handle = curl_easy_init();

    /// Configure the libcurl session
    curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L); /// verbose mode
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); /// Follow redirections
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_curl_data); /// C function callback to process data read by libcurl. Can be called more than once
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &writeFile); /// User data passed to the CURLOPT_WRITEFUNCTION. Can be anything.
    curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, err_buffer); /// Pointer to the error buffer that libcurl must used to store error message if any
    curl_easy_setopt(handle, CURLOPT_USERPWD, "curl:C+nnYt1AHVY"); /// username:password

    for (std::string &str : assets) {
        writeFile.filename = CCFileUtils::sharedFileUtils()->getWritablePath().append(str);
        /// Set the curl request url
        curl_easy_setopt(handle, CURLOPT_URL, (repo + str).c_str()); /// Must not use std::string::append here.
        /// performs the entire request in a blocking manner and returns when done
        if (curl_easy_perform(handle) != CURLE_OK) {
            CCLOGERROR("CURL Error: %s", err_buffer);
        }
        if (writeFile.stream) {
            fclose(writeFile.stream);
            writeFile.stream = nullptr; /// must nullify so a new file is created
        }
    }
    /// Time to clean up libcurl ressources
    curl_easy_cleanup(handle);
    /// Close the file stream
}

/*
void Command::updateSpriteFrames(const char *pPlist, const char *pTexture)
{
    char *plist_data;
    int plist_data_len = base64Decode((unsigned char*)pPlist, strlen(pPlist), (unsigned char**)&plist_data);
    /// std::cout << plist_data << std::endl;

    char *texture_data;
    int texture_data_len = base64Decode((unsigned char*)pTexture, strlen(pTexture), (unsigned char**)&texture_data);

    DictMaker maker;
    CCDictionary *dict = maker.createDictionaryWithString(plist_data, plist_data_len);

    CCImage *img = new CCImage();
    img->initWithImageData(texture_data, texture_data_len);
    CCTexture2D *texture = new CCTexture2D();
    texture->initWithImage(img);

    replaceSpriteFrames(dict, texture);

    delete plist_data;
    delete texture_data;
}
*/

void Command::setDebugParams(bool showPhysicsDraw,bool showStats,bool zoomOutScene)
{
    DebugSettings::getInstance()->showPhysicsDraw = showPhysicsDraw;
    DebugSettings::getInstance()->showStats = showStats;
    DebugSettings::getInstance()->zoomOutScene = zoomOutScene;
}

NS_PIX2D_CONSOLE_END
