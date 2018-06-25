-- Copyright (C) 2012-2015 Laurent Zubiaur - voodoocactus.com
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

local Util = {}; Util.__index = Util

print 'Loading package util...'

local fileUtils = CCFileUtils:sharedFileUtils()
local visible = pix2d.VisibleRect

-- Parameters
-- priority: the touch priority. Set it to a value fewer then kCCMenuHandlerPriority to get a modal popup dialog.
-- buttons: 'cancel','ok','cancelok'
-- callback: the callback function called when the ok and/or cancel button is tapped. If callback returns true
-- then this message box is auto-removed.
function Util.dialog(priority,size,buttons,callback,color,frame)
    local layer = color and CCLayerColor:create(color) or CCLayer:create()
    layer:registerScriptTouchHandler(
        function(e,x,y) return true end,
        false, -- no multi-touch (process touches one by one)
        priority,
        true)
    layer:setTouchEnabled(true)
    local background = CCScale9Sprite:createWithSpriteFrameName(frame or 'messagebox2.png')
    background:setContentSize(size)
    local node = CCNode:create()
    node:setPosition(visible:center())
    local menu = CCMenu:create()
    menu:setPosition(ccp(0,0))
    menu:setTouchPriority(priority)
    if buttons == 'ok' or buttons == 'cancelok' then
        local button = Util.createCustomMenuItem('button_ok.png',nil,nil,function()
            if callback('ok',layer,node) then layer:removeFromParentAndCleanup(true) end
        end)
        button:setPosition(size.width * 0.3, -size.height * 0.5)
        menu:addChild(button)
    end
    if buttons == 'cancel' or buttons == 'cancelok' then
        local button = Util.createCustomMenuItem('button_cancel.png',nil,nil,function()
            if callback('cancel',layer,node) then layer:removeFromParentAndCleanup(true) end
        end)
        button:setPosition(-size.width * 0.3, -size.height * 0.5)
        menu:addChild(button)
    end
    layer:addChild(node)
    node:addChild(background)
    node:addChild(menu)
    return layer, node
end

function Util.messageBox(text,priority,buttons,callback)
    local label = Util.label(text,0,0,0.7)
    local size = label:getContentSize()
    size.width = math.min((size.width * 0.7) + 60,visible:size().width)
    size.height = math.min((size.height * 0.7)+ 40,visible:size().height)
    local layer, node = Util.dialog(priority,size,buttons,callback,nil,'messagebox.png')
    node:addChild(label)
    return layer, node
end

function Util.normalizeAngle(angle)
    angle = angle % (2 * math.pi)
    return angle >= 0 and angle or angle + 2 * math.pi
end

function Util.sign(x)
    return x>0 and 1 or x<0 and -1 or 0
end

function Util.ccc4f(p)
    return ccc4f(p[1],p[2],p[3],p[4])
end

function Util.toColor4f(p)
    return ccc4f(p[1]/255, p[2]/255, p[3]/255, p[4]/255)
end

-- Create a batched sprite from `batch` with size `w` and `h`. The texture is
-- repeated if `repeatTex` equals true.
function Util.createBatchSprite(batch,w,h,repeatTex)
    local sprite = CCSprite:createWithTexture(batch:getTexture(),CCRectMake(0,0,w,h))
    if repeatTex then
        local texParams     = ccTexParams()
        texParams.minFilter = GL_LINEAR
        texParams.magFilter = GL_LINEAR
        texParams.wrapS     = GL_REPEAT
        texParams.wrapT     = GL_REPEAT
        sprite:getTexture():setTexParameters(texParams)
    end
    batch:addChild(sprite)
    return sprite
end

function Util.blend(src,dst)
    local bf = ccBlendFunc()
    bf.src = src; bf.dst = dst
    return bf
end

function Util.normalBlend()
    return Util.blend(GL_ONE, GL_ONE_MINUS_SRC_ALPHA)
end

function Util.additiveBlend()
    return Util.blend(GL_ONE, GL_ONE)
end

function Util.alphaBlend()
    return Util.blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
end

function Util.screenBlend()
    return Util.blend(GL_ONE, GL_ONE_MINUS_SRC_COLOR)
end

function Util.multiplyBlend()
    return Util.blend(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA)
end

function Util.negativeBlend()
    return Util.blend(GL_ZERO, GL_ONE_MINUS_DST_COLOR)
end

function Util.overlayBlend()
    return Util.blend(GL_SRC_ALPHA, GL_ONE)
end

function Util.progressBarHorizontal(fg,bg,x,y,percent,parent)
    local pb = CCProgressTimer:create(CCSprite:createWithSpriteFrameName(fg))
    local pbbg = CCSprite:createWithSpriteFrameName(bg)
    pb:setPosition(x,y)
    pb:setType(kCCProgressTimerTypeBar)
    pb:setMidpoint(ccp(0,1))
    pb:setBarChangeRate(ccp(1,0))
    -- pb:setReverseDirection(false)
    pbbg:setPosition(x,y)
    pb:setPercentage(percent or 0.0)
    if parent then parent:addChild(pbbg); parent:addChild(pb) end
    return pb,pbbg
end

-- Internal function to create a progress bar with a background sprite
local function _progressBarVertical(fg,bg,x,y,percent,parent)
    local pb = CCProgressTimer:create(fg)
    pb:setPosition(x,y)
    pb:setType(kCCProgressTimerTypeBar)
    pb:setMidpoint(ccp(1,0))
    pb:setBarChangeRate(ccp(0,1))
    -- pb:setReverseDirection(false)
    bg:setPosition(x,y)
    pb:setPercentage(percent or 0.0)
    if parent then parent:addChild(bg); parent:addChild(pb) end
    return pb,bg
end

-- Create a vertical progress bar using the given sprite frame names
function Util.progressBarVertical(fg,bg,x,y,percent,parent)
    return _progressBarVertical(
        CCSprite:createWithSpriteFrameName(fg),
        CCSprite:createWithSpriteFrameName(bg),
        x,y,percent,parent)
end

-- Same as above but with sprites instead of sprite frames
function Util.progressBarVerticalWithSprites(fg,bg,x,y,percent,parent)
    return _progressBarVertical(CCSprite:create(fg),CCSprite:create(bg),x,y,percent,parent)
end

-- Walk through all children of the node `parent` and for each child call `fn`.
-- The child node is cast into `ctype` or CCNode or provided or nil.
-- Type is a string with the C++ type (e.g. pix2d::MaClass) and not Lua
-- rype (e.g. pix2d.MyClass).
-- The current child is passed to the callback function which might return false
-- to stop the loop. Returns the number of processed child node and the count
-- of all children.
function Util.forEachChild(parent,fn,ctype)
    local array = parent:getChildren()
    local count = array:count()
    local result = 0
    ctype = ctype or 'CCNode'
    for i = 0, count -1 do
        local child = tolua.cast(array:objectAtIndex(i),ctype)
        local continue = fn(child)
        if continue ~= nil and not continue then break end
        result = result + 1
    end
    return result, count
end

-- Returns the bounding box of the direct children. Padding can be nil (no padding),
-- a number or a table with vertical and horizontal padding (e.g. { 10, 15 })
function Util.childrenBoundingBox(parent,padding)
    local max = { x = 0.0, y = 0.0 }
    local min = { x = 0.0, y = 0.0 }
    Util.forEachChild(parent,function(child)
        local bb = child:boundingBox()
        max.x = math.max(max.x, bb.origin.x + bb.size.width)
        max.y = math.max(max.y, bb.origin.y + bb.size.height)
        min.x = math.min(min.x, bb.origin.x)
        min.y = math.min(min.y, bb.origin.y)
    end)
    local p = nil
    if padding == nil then
        p = { 0, 0 }
    elseif type(padding) == 'number' then
        p = { padding, padding }
    else
        p = padding
    end
    return CCRectMake(min.x + p[1], min.y + p[2], max.x - min.x + p[1], max.y - min.y + p[2])
end

-- http://lua-users.org/wiki/CopyTable
function Util.shallowcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in pairs(orig) do
            copy[orig_key] = orig_value
        end
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

-- recursive print table (https://gist.github.com/stuby/5445834#file-rprint-lua)
function Util.r_print(s, l, i) -- recursive Print (structure, limit, indent)
    l = (l) or 100; i = i or "";    -- default item limit, indent string
    if (l<1) then print "ERROR: Item limit reached."; return l-1 end;
    local ts = type(s);
    if (ts ~= "table") then print (i,ts,s); return l-1 end
    print (i,ts);           -- print "table"
    for k,v in pairs(s) do  -- print "[KEY] VALUE"
        l = Util.r_print(v, l, i.."\t["..tostring(k).."]");
        if (l < 0) then break end
    end
    return l
end

function Util.worldSpacePosition(node)
    -- assert(node:getParent() ~= nil,'Node has no parent')
    return node:getParent():convertToWorldSpace(ccp(node:getPosition()))
end

function Util.captureScreen(filename)
    local size = pix2d.VisibleRect:size()
    local render = CCRenderTexture:create(size.width,size.height)
    render:setPosition(pix2d.VisibleRect:center())
    local color = pix2d.Physics:getDefaultBackgroundColor()
    render:beginWithClear(color.r,color.g,color.b,color.a)
    CCDirector:sharedDirector():getRunningScene():visit()
    render:endToLua()

    render:saveToFile(filename or os.date('screenshot-%Y-%m-%d-%H-%M-%S.png'),kCCImageFormatPNG)
end

-- Returns a "bouncing" action with a duration and scale.
-- If duration or scale are nil then default values are used.
function Util.bounceAction(duration,scale)
    local a1 = CCScaleBy:create(duration or 0.3,scale or 0.9)
    local a2 = CCEaseElasticOut:create(CCScaleTo:create(duration or 0.3,1.0))
    return CCSequence:createWithTwoActions(a1,a2)
end

-- Create a black sprite with the text 'str' as negative mask
-- So the only visible part of the screen would be the label's text
function Util.loadingMask(str)
    local label = util.labelTTF(str,'Chewy','Huge')
    label:setPosition(visible:center())
    label:setColor(ccc3(255,255,255))

    local size = visible:size()
    local render = CCRenderTexture:create(size.width,size.height)
    render:clear(0,0,0,0)
    render:setPosition(visible:center())
    render:begin()
    label:visit()
    render:endToLua()

    local sprite = CCSprite:createWithTexture(render:getSprite():getTexture())
    local bf = ccBlendFunc()
    bf.src = GL_ZERO
    bf.dst = GL_SRC_ALPHA
    sprite:setBlendFunc(bf)
    sprite:setPosition(visible:center())
    return sprite
end

-- DEPRECATED: Call the script `filename` and pass a variable numer of arguments
function Util.loadScript(filename,...)
    -- We can't use loadfile on android because assets are in a zip file
    -- We could use a custom loader like cocos2dx_lua_loader for packages (require)
    -- assert(loadfile(fileUtils:fullPathForFilename(filename)))(...)
    assert(loadstring(Util.readDataFileSafe(filename)))(...)
end
-- Font size: Tiny,Small,Medium,Large,Huge
local function cutomItemHandler(name,node)
    -- tolua.cast(node,'CCMenuItemSprite')
    if name == 'selected' then
        node:runAction(CCEaseElasticOut:create(CCScaleTo:create(0.3,1.15)))
        -- node:setColor(ccc3(255,0,0))
        -- node:getSelectedImage():setBlendFunc(Util.additiveBlend())
    else
        node:runAction(CCEaseElasticOut:create(CCScaleTo:create(0.3,1.0)))
        -- node:setColor(ccc3(255,255,255))
    end
end

-- NOTE: Use createCustomMenuItem to create with sprite frame names
function Util.createCustomMenuItemWithSprite(normal,selected,disabled,handler)
    local item = pix2d.CustomMenuItem:create(
        CCSprite:create(normal),
        CCSprite:create(selected or normal),
        CCSprite:create(disabled or normal))
    item:registerScriptHandler(cutomItemHandler)
    if handler then
        item:registerScriptTapHandler(handler)
    end
    return item
end

function Util.createCustomMenuItem(normal,selected,disabled,handler)
    local item = pix2d.CustomMenuItem:create(
        CCSprite:createWithSpriteFrameName(normal),
        CCSprite:createWithSpriteFrameName(selected or normal),
        CCSprite:createWithSpriteFrameName(disabled or normal))
    item:registerScriptHandler(cutomItemHandler)
    if handler then
        item:registerScriptTapHandler(handler)
    end
    return item
end

function Util.createMenuItem(normal,selected,disabled)
     return CCMenuItemSprite:create(
        CCSprite:createWithSpriteFrameName(normal),
        CCSprite:createWithSpriteFrameName(selected or normal),
        CCSprite:createWithSpriteFrameName(disabled or normal))
end

function Util.label(msg,x,y,scale)
    local label = CCLabelBMFont:create(msg,'Chewy.fnt')
    label:setPosition(x,y)
    if scale then label:setScale(scale) end
    return label
end

function Util.labelTTF(msg,font,size)
    local _font = pix2d.Assets:font(pix2d.Assets[font])
    local _size = pix2d.Assets:fontSize(pix2d.Assets[size])
    return CCLabelTTF:create(msg,_font,_size)
end

-- Return the data file 'filename'
function Util.readDataFile(filename)
    return assert(Util.readDataFileSafe(filename,false),"Can't read data file "..filename)
end

-- Returns the data file 'filename' or an empty string if an error occurs
-- We can't simply use io.open because for instance in android the app bundle
-- is zipped.
function Util.readDataFileSafe(filename)
    return pix2d.Assets:readTextFile(filename,false) -- decrypt flag
    --[[
    fileUtils:getFileData(filename,'r')
    -- Get the full path for filename
    local fp = fileUtils:fullPathForFilename(filename)
    local file = io.open(fp,'r')
    if not file then
        print('Can\'t open file in read mode',fp)
        return nil
    end
    -- load all the file
    local s = file:read('*a')
    file:close()
    return s
    --]]
end

-- Write 'data' to file 'filename'. The filename is prefixed with the writable path
-- Returns true on success or false otherwise
function Util.writeDataFileSafe(filename,data)
    -- Get the writable path
    local file = io.open(fileUtils:getWritablePath()..filename,'w+')
    if not file then
        print('Can\'t open file in write mode',filename)
        return false
    end
    local rc = file:write(data)
    print('Write file',rc)
    file:close()
    return true
end

-- For iterator that iterates two by two
function Util.ipairs2(t)
    local function ipairs_it(t, i)
        i = i + 1
        local v1 = t[i]
        i = i + 1
        local v2 = t[i]
        if v1 ~= nil and v2 ~= nil then
            return i,v1,v2
        else
            return nil
        end
    end
    return ipairs_it, t, 0
end

-- Call the Lua garbage collector
function Util.collectGarbage(max)
    print('BEFORE garbage collection:',math.floor(collectgarbage("count")))
    max = max or 3
    for i = 1, max do
        collectgarbage("collect")
    end
    print('AFTER garbage collection:',math.floor(collectgarbage("count")))
end

-- Release unused memeory.
-- Do NOT call this function after loading a scene but rather before.
-- For instance removeSpriteFrames() or removeUnusedSpriteFrames() will remove
-- frames that is not currently used but might be needed later in the level
-- (e.g. creating a rope on the fly). Since the frames was not used yet and removed
-- it will crash if the app tries to use that frame.
function Util.releaseMemory()
    print 'Releasing memory...'
    -- Purge the cocosbuilder cache and shared loader
    -- CCNodeLoaderLibrary:sharedCCNodeLoaderLibrary():purge(true)
    -- CCNodeLoaderLibrary:purgeSharedCCNodeLoaderLibrary()
    -- Purge sounds and musics
    -- This will need to re-init volume when creating again sounds
    -- SimpleAudioEngine:sharedEngine():end()
    -- purge bitmap label cache
    CCLabelBMFont:purgeCachedData()
    -- Sprite frames cache.
    CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFrames()
    -- Texture cache
    CCTextureCache:sharedTextureCache():removeAllTextures()
    -- CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    -- File cache
    CCFileUtils:sharedFileUtils():purgeCachedEntries()
    -- Notification center (required?)
    CCNotificationCenter:purgeNotificationCenter()
    -- User default
    CCUserDefault:purgeSharedUserDefault()
    -- Animation cache
    CCAnimationCache:purgeSharedAnimationCache()
    -- Call lua garbage collector
    Util.collectGarbage()
end

return Util
-- EOF
