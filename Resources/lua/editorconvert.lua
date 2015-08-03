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

local json = require 'json'

-- The package table
local EditorConvert = {}; EditorConvert.__index = EditorConvert

setmetatable(EditorConvert,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            template = {
                levelid = 0,
                season = 0,
                version = '',
                world = {
                    unit = 0.5,
                    position = { 0, 0 },
                    size = { 10, 7 },
                    gravity = { 0, -10 }
                },
                assets = {
                    spritesheets = {},
                    batch = {},
                    particleBatch = {},
                },
                tools = {},
                graph = {}
            }
        }, EditorConvert)
    end
})

-- Load and decode the Tiled file into `self.data`
function EditorConvert:decode(filename)
    print('Decode file',filename)
    local file = io.open(filename,'r')
    assert(file)
    self.data = json.decode(file:read('*a'))
    file:close()
end

-- Encode and save `self.template` to file
function EditorConvert:encode(filename)
    print('Encode file',filename)
    local file = io.open(filename,'w')
    assert(file,"Can't open file in write mode: "..filename)
    file:write(json.encode(self.template))
    file:close()
end

function getTableProperty(object,name,default)
    return object.properties[name] and load('return '..object.properties[name])() or default
end

function getBooleanProperty(object,name,default)
    if object.properties[name] then
        return object.properties[name] == 'true'
    end
    return default
end

function getNumberProperty(object,name,default)
    return object.properties[name] and tonumber(object.properties[name]) or default
end

function EditorConvert:getLayerByName(name)
    for _,layer in ipairs(self.data.layers) do
        if layer.name == name then return layer end
    end
    return nil
end

function EditorConvert:getObjectByName(layer,name)
    for _,o in ipairs(layer.objects) do
        if o.name == name then return o end
    end
    return nil
end

function EditorConvert:parseSprite(object)
    local p = self:parseRect(object)
    local sprite = {
        type = 'sprite',
        layer = object.properties.layer,
        frame = object.properties.frame,
        sprite = object.properties.sprite,
        uid = 0,
        zorder = object.properties.zorder,
        anchor = getTableProperty(object,'anchor'),
        flip = getTableProperty(object,'flip'),
        scale = getTableProperty(object,'scale'),
        opacity = tonumber(object.properties.opacity),
        color = getTableProperty(object,'color'),
        rotation = tonumber(object.properties.rotation),
        position = { p[1], p[2] }
    }
    table.insert(self.template.graph,sprite)
    return sprite
end

function EditorConvert:parseMoon(object)
    local moon = self:parseSprite(object)
    moon.type = 'moon'
end

function EditorConvert:parseInfiniteSprite(object)
    local line = self:parsePolyLine(object)
    table.insert(self.template.graph, {
        type = 'infiniteSprite',
        startPos = { line[1], line[2] },
        endPos = { line[3], line[4] },
        color = getTableProperty(object,'color'),
        flip = getTableProperty(object,'flip'),
        frame = object.properties.frame,
        sprite = object.properties.sprite,
        time = object.properties.time or 1,
        layer = object.properties.layer,
        opacity = object.properties.opacity,
        zorder = object.properties.zorder,
    })
end

function EditorConvert:parseAction(object)
    local path = {
        action = object.properties.action,
        loop = getBooleanProperty(object,'loop'),
    }
    if path.action == 'moveTo' then
        path.points = self:parsePolyLine(object)
        path.speed = object.properties.speed
    elseif path.action == 'splineTo' then
        path.points = self:parsePolyLine(object)
        path.duration = object.properties.duration
        path.tension = object.properties.tension
    elseif path.action == 'circleTo' then
        local circle = self:parseCircle(object)
        path.center = circle.center
        -- path.radius = circle.radius
        path.duration = object.properties.duration
    end
    return path
end

function EditorConvert:parseBad(object)
    local position = self:parseRect(object)
    local bad = {
        type = 'bad',
        frame = object.properties.frame,
        position = { position[1], position[2] },
    }
    if object.properties.path then
        local path = self:getObjectByName(self.currentLayer,object.properties.path)
        assert(path,'No object named '..object.properties.path)
        bad.path = self:parseAction(path)
    end
    table.insert(self.template.graph,bad)
    return bad
end

function EditorConvert:parseSeaLion(object)
    local bad = self:parseBad(object)
    bad.type = 'seaLion'
    return bad
end

function EditorConvert:parseCrab(object)
    local position,center,size = self:parseRect(object)
    local bad = {
        type = 'crab',
        frame = object.properties.frame,
        position = { center[1], center[2] },
    }
    if object.properties.path then
        local path = self:getObjectByName(self.currentLayer,object.properties.path)
        assert(path,'No object named '..object.properties.path)
        bad.path = self:parseAction(path)
    end
    table.insert(self.template.graph,bad)
    return bad
end

function EditorConvert:parseBadPathFinder(object)
    local bad = self:parseBad(object)
    bad.type = 'badPathFinder'
end

function EditorConvert:parseBadFollow(object)
    local bad = self:parseBad(object)
    bad.type = 'badFollow'
    bad.speed = object.properties.speed
end

function EditorConvert:parseSlider(object)
    local path = self:getObjectByName(self.currentLayer,object.properties.path)
    assert(path)
    local p = self:parsePolyLine(path)
    assert(#p == 4)
    local position, center, size = self:parseRect(object)
    local slider = {
        type = 'slider',
        uid = 10,
        position = center,
        size = size,
        startpos = { p[1], p[2] },
        endpos = { p[3], p[4] },
        color = getTableProperty(object,'color'),
        frame = object.properties.frame,
    }
    table.insert(self.template.graph,slider)
end

function EditorConvert:parseRope(object)
    local p = self:parseRect(object)
    local rope = {
                type = 'rope',
                uid = 10,
                startpos = { p[1], p[4] -1},
                endpos = { p[1], p[2] },
                anchor = object.properties.anchor or 'cloud.png',
                hook = object.properties.hook or 'lollipop.png',
                batch = object.properties.batch or 'rainbow.png'
    }
    table.insert(self.template.graph,rope)
end

function EditorConvert:parseScrollingTexture(object)
    local p = self:parseRect(object)
    local texture = {
        type = 'scrollingTexture',
        tag = object.properties.tag,
        zorder = object.properties.zorder,
        layer = object.properties.layer,
        aabb = { p[1], p[2], p[3], p[4] },
        translation = getTableProperty(object,'translation',{0.1,0}),
        texture = object.properties.texture,
        repeatV = getBooleanProperty(object,'repeatV'),
        repeatH = getBooleanProperty(object,'repeatH'),
        color = getTableProperty(object,'color'),
    }
    table.insert(self.template.graph,texture)
end

function EditorConvert:parseCoin(object)
    local p = self:parseRect(object)
    local coin = {
        type = 'coin',
        position = { p[1], p[2] },
        frame = object.properties.frame,
        apparitionLoop = getBooleanProperty(object,'apparitionLoop'),
        apparition = getTableProperty(object,'apparition'),
        color = getTableProperty(object,'color'),
    }
    if object.properties.path then
        local path = self:getObjectByName(self.currentLayer,object.properties.path)
        assert(path,'No object named '..object.properties.path)
        coin.path = self:parseAction(path)
    end
    table.insert(self.template.graph,coin)
end

function EditorConvert:parseBalloon(object)
    local p = self:parseRect(object)
    local balloon = {
        type = 'balloon',
        uid = 5,
        startpos = { p[1], p[4] -1 },
        endpos = { p[1], p[2] },
        anchor = object.properties.anchor or 'balloon.png',
        hook = object.properties.hook or '',
        batch = object.properties.batch or 'balloon_rope.png'
    }
    table.insert(self.template.graph,balloon)
end

function EditorConvert:parseTarget(object)
    local p = self:parseRect(object)
    local target = {
        type = 'target',
        uid = 5,
        position = { p[1], p[2] },
        frame = object.properties.frame,
        apparitionLoop = getBooleanProperty(object,'apparitionLoop'),
        apparition = getTableProperty(object,'apparition'),
        color = getTableProperty(object,'color'),
    }
    if object.properties.path then
        local path = self:getObjectByName(self.currentLayer,object.properties.path)
        assert(path,'No object named '..object.properties.path)
        target.path = self:parseAction(path)
    end
    table.insert(self.template.graph,target)
end

function EditorConvert:parsePlayer(object)
    local p = self:parseRect(object)
    local player = {
        type = 'player',
        uid = 1,
        position = { p[1], p[2] },
        initialImpulse = getNumberProperty(object,'impulse'),
        frame = 'idle.png'
    }
    table.insert(self.template.graph,player)
end

function EditorConvert:parseEclipse(object)
end

function EditorConvert:parsePolyLine(object)
    local size = self.mapSizeInPixel
    local points = {}
    for _,p in ipairs(object.polyline) do
        table.insert(points, (object.x + p.x) / self.data.tilewidth)
        table.insert(points, (size.height - object.y - p.y) / self.data.tileheight)
    end
    return points
end

function EditorConvert:parseRect(object)
    local size = self.mapSizeInPixel
    local position = {
        object.x / self.data.tilewidth,
        (size.height - object.y - object.height) / self.data.tileheight,
        (object.x + object.width) / self.data.tilewidth,
        (size.height - object.y) / self.data.tileheight
    }
    local size = {
        object.width / self.data.tilewidth,
        object.height / self.data.tileheight
    }
    local center = {
        position[1] + (size[1] / 2),
        position[2] + (size[2] / 2)
    }
    return position, center, size
end

function EditorConvert:parsePolygon(object)
    local size = self.mapSizeInPixel
    local points = {}
    for _,p in ipairs(object.polygon) do
        table.insert(points,(object.x + p.x) / self.data.tilewidth)
        table.insert(points,(size.height - object.y - p.y) / self.data.tileheight)
    end
    return points
end

function EditorConvert:parseCircle(object)
    assert(object.ellipse)
    assert(object.width == object.height,'Not a circle')
    local size = self.mapSizeInPixel
    return {
        center = {
            (object.x + (object.width / 2)) / self.data.tilewidth,
            (size.height - (object.y + (object.height / 2))) /self.data.tileheight
        },
        radius = (object.width / self.data.tilewidth) / 2
    }
end

function EditorConvert:parseDancingSprite(object)
    local sprite = self:parseSprite(object)
    sprite.type = 'dancingSprite'
    table.insert(self.template.graph,sprite)
end

function EditorConvert:parseDrawLine(object)
    local line = {
        type = 'line',
        color = getTableProperty(object,'color',{255,0,0,255}),
        points = self:parsePolyLine(object),
        radius = object.properties.radius or 0.5,
    }
    table.insert(self.template.graph,line)
end

function EditorConvert:parseTexture(object)
    local texture = {
        type = 'texture',
        texture = assert(object.properties.texture),
        points = self:parsePolygon(object),
        opacity = object.properties.opacity,
        color = getTableProperty(object,'color'),
        zorder = object.properties.zorder,
        tag = object.properties.tag,
        layer = object.properties.layer,
        scale = getTableProperty(object,'scale'),
    }
    table.insert(self.template.graph,texture)
    return texture
end

--[[
function EditorConvert:parseLight(object)
    local texture = self:parseTexture(object)
    texture.type = 'light'
end
--]]

function EditorConvert:parseShadow(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph,{
        type = 'shadow',
        position = center,
        size = size,
        speed = getNumberProperty(object,'speed'),
        darkness = assert(object.properties.darkness),
    })
end

function EditorConvert:parseDrawPolygon(object)
    local polygon = {
        type = 'polygon',
        points = self:parsePolygon(object),
        borderWidth = getNumberProperty(object,'borderWidth',0),
        borderColor = getTableProperty(object,'borderColor',{0,0,0,0}),
        fillColor = getTableProperty(object,'fillColor',{0,0,0,0}),
    }
    table.insert(self.template.graph,polygon)
end

function EditorConvert:parseGrounds(objects)
    local ground = {
        type = 'ground',
        uid = 10,
        -- indices = true,
        points = {},
        color = getTableProperty(self.data,'ground_color'),
        opacity = tonumber(self.data.properties.ground_opacity),
        texture = self.data.properties.ground_texture
    }
    -- ground.texture = object.properties.texture
    for _,o in ipairs(objects) do
        p = o.polygon and self:parsePolygon(o) or self:parseRect(o)
        table.insert(ground.points,p)
    end
    table.insert(self.template.graph,ground)
end

function EditorConvert:parseBoundary(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'boundary',
        position = { position[1], position[2] },
        size = size,
    })
end

function EditorConvert:parseFan(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'fan',
        position = { position[1], position[2] },
        center = { center[1], center[2] },
        angle = object.properties.angle and math.rad(object.properties.angle) or nil,
        enabled = getBooleanProperty(object,'enabled',nil),
        -- size = size,
    })
end

function EditorConvert:parseSpear(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'spear',
        position = { center[1], center[2] },
        angle = object.properties.angle and math.rad(object.properties.angle) or nil,
        frame = object.properties.frame,
    })
end

function EditorConvert:parseFloatingPlatform(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'floatingPlatform',
        position = { center[1], center[2] },
        frame = object.properties.frame,
    })
end

function EditorConvert:parseCardboard(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'cardboard',
        position = { center[1], center[2] },
        frame = object.properties.frame,
    })
end

function EditorConvert:parseTeleport(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph, {
        type = 'teleport',
        position = position,
        angle = object.properties.angle and math.rad(object.properties.angle) or nil,
        group = assert(getNumberProperty(object,'group')),
        index = assert(getNumberProperty(object,'index')),
        frame = 'teleport.png',
        effectFrame = 'teleport_ring.png',
        movable = getBooleanProperty(object,'movable',true),
        color = getTableProperty(object,'color'),
        path = object.properties.path and self:parseAction(assert(self:getObjectByName(self.currentLayer,object.properties.path))) or nil,
    })
end

function EditorConvert:parseChain(object)
    local line = self:parsePolyLine(object)
    table.insert(self.template.graph, {
        type = 'chain',
        startpos = { line[1], line[2] },
        endpos = { line[3], line[4] },
        color = getTableProperty(object,'color'),
        batch = object.properties.batch,
        frame = object.properties.frame,
        count = getNumberProperty(object,'nodes'),
        overlap = getNumberProperty(object,'overlap'),
        density = getNumberProperty(object,'density'),
        height = getNumberProperty(object,'height'),
        sensorHeight = getNumberProperty(object,'sensorHeight'),
        mouseMaxForce = getNumberProperty(object,'mouseMaxForce'),
        mouseFrequency = getNumberProperty(object,'mouseFrequency'),
        projection = assert(getTableProperty(object,'projection')),
        movable = getBooleanProperty(object,'movable'),
    })
end

function EditorConvert:parsePhysicsBody(object)
    local position = self:parseRect(object)
    return {
        position = position,
        frame = object.properties.frame,
        body_type = object.properties.body_type,
        tag = object.properties.tag,
        zorder = object.properties.zorder,
        is_sensor = object.properties.sensor,
        restitution = object.properties.restitution,
        friction = object.properties.friction,
        density = object.properties.density,
        category = object.properties.category,
        mask = object.properties.mask,
        group = object.properties.group,
        angle = object.properties.angle and math.rad(getNumberProperty(object,'angle')) or nil,
        frame = object.properties.frame,
        sprite = object.properties.sprite,
    }
end

function EditorConvert:parseCircleBody(object)
    local p = self:parsePhysicsBody(object)
    local circle = self:parseCircle(object)
    p.position = { p.position[1] - circle.radius, p.position[2] - circle.radius} -- HACK center from parseCircle not correct
    p.radius = circle.radius
    p.type = 'circle'
    table.insert(self.template.graph,p)
    return p
end

function EditorConvert:parseBoxBody(object)
    local position, center, size = self:parseRect(object)
    local body = self:parsePhysicsBody(object)
    body.type = 'box'
    body.position = center
    body.size = size
    table.insert(self.template.graph,body)
    return body
end

function EditorConvert:parseTextureBody(object)
    local points = self:parsePolygon(object)
    local body = self:parsePhysicsBody(object)
    body.type = 'textureBody'
    body.points = points
    body.texture = assert(object.properties.texture)
    table.insert(self.template.graph,body)
    return body
end

function EditorConvert:parseIceGround(object)
    local polyline = self:parsePolyLine(object)
    table.insert(self.template.graph,{
        type = 'iceGround',
        points = polyline,
        frame = object.properties.frame,
        friction = object.properties.friction,
        zorder = object.properties.zorder,
    })
end

function EditorConvert:parseBeachBall(object)
    local ball = self:parseCircleBody(object)
    ball.type = 'beachBall'
    ball.path = object.properties.path and
        self:parseAction(assert(self:getObjectByName(self.currentLayer,object.properties.path))) or nil
end

function EditorConvert:parseTrampoline(object)
    local position,center,size = self:parseRect(object)
    table.insert(self.template.graph,{
        uid = 0,
        type = 'trampoline',
        position = position,
        frame = object.properties.frame,
        restitution = assert(object.properties.restitution),
        movable = getBooleanProperty(object,'movable',false),
        angle = object.properties.angle and math.rad(object.properties.angle) or nil,
        addSprite = getTableProperty(object,'sprite'),
    })
end

function EditorConvert:parsePlatterLift(object)
    local line = self:parsePolyLine(object)
    table.insert(self.template.graph, {
        type = 'platterLift',
        startpos = { line[1], line[2] },
        endpos = { line[3], line[4] },
        color = getTableProperty(object,'color'),
        chainBatch = object.properties.chainBatch,
        chainSprite = object.properties.chainSprite,
        wheelFrame = object.properties.wheelFrame,
        speed = object.properties.speed,
        ropes = getTableProperty(object,'ropes'),
        fadeIn = getBooleanProperty(object,'fadeIn'),
    })
end

function EditorConvert:parseElasticRope(object)
    local position,size,center = self:parseRect(object)
    table.insert(self.template.graph,{
        type = 'elasticRope',
        position = position,
        frame = object.properties.frame,
    })
end

function EditorConvert:void()
end

function EditorConvert:parse()
    local level = tonumber(self.data.properties.level)
    local season = tonumber(self.data.properties.season)
    local fileSeasonid, fileLevelid = string.match(self.filename,'%S(%d+)E(%d+).json')
    fileLevelid = tonumber(fileLevelid)
    fileSeasonid = tonumber(fileSeasonid)
    assert(level == tonumber(fileLevelid),'Filename does not match level: '..level..' '..fileLevelid)
    assert(season == tonumber(fileSeasonid),'Filename does not match season')

    assert(season and season > 0 and season < 5)
    -- assert(level and level > 0 and level < 20)

    self.mapSizeInPixel = {}
    self.mapSizeInPixel.width = self.data.width * self.data.tilewidth
    self.mapSizeInPixel.height = self.data.height * self.data.tileheight

    -- properties
    self.template.version = 'autogenerated v0.1'
    self.template.date = os.date('%Y-%m-%d %H:%M:%S')
    self.template.levelid = level
    self.template.season = season

    -- Order of the tools insertion in the json file does NOT matter
    -- The game will create the tool box using its own ordering
    if self.data.properties.tool_rope and self.data.properties.tool_rope ~= '' then
        self.template.tools.rope = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_rope) or 0,
            selected = 'item_rope_s.png',
            normal = 'item_rope_n.png',
            disabled = 'item_rope_d.png',
            meta = {
                type = 'rope',
                starpos = { 0, 0 },
                endpos = { 0, 0 },
                anchor = 'cloud.png',
                hook = 'lollipop.png',
                batch = 'rainbow.png'
            }
        }
    end

    if self.data.properties.tool_block and self.data.properties.tool_block ~= '' then
        self.template.tools.block = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_block) or 0,
            selected = 'item_block_s.png',
            normal = 'item_block_n.png',
            disabled = 'item_block_d.png'
        }
    end

    if self.data.properties.tool_balloon and self.data.properties.tool_balloon ~= '' then
        self.template.tools.balloon = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_balloon) or 0,
            selected = 'item_balloon_s.png',
            normal = 'item_balloon_n.png',
            disabled = 'item_balloon_d.png',
            meta = {
                anchor = 'balloon.png',
                batch = 'balloon_rope.png'
            }
        }
    end

    if self.data.properties.tool_teleport and self.data.properties.tool_teleport ~= '' then
        self.template.tools.teleport = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_teleport) or 0,
            selected = 'item_teleport_s.png',
            normal = 'item_teleport_n.png',
            disabled = 'item_teleport_d.png',
            meta = {
                group = 1,
                frame = 'teleport.png',
                effectFrame = 'teleport_ring.png',
                movable = true,
            }
        }
    end
    if self.data.properties.tool_fan and self.data.properties.tool_fan ~= '' then
        self.template.tools.fan = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_fan) or 0,
            selected = 'item_fan_s.png',
            normal = 'item_fan_n.png',
            disabled = 'item_fan_d.png',
            meta = {
            }
        }
    end

    if self.data.properties.tool_cardboard and self.data.properties.tool_cardboard ~= '' then
        local meta = getTableProperty(self.data,'cardboard',{})
        meta.frame = 'cardboard_box.png'
        self.template.tools.cardboard = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_cardboard) or 0,
            selected = 'item_cardboard_s.png',
            normal = 'item_cardboard_n.png',
            disabled = 'item_cardboard_d.png',
            meta = meta,
        }
    end

    if self.data.properties.tool_trampoline and self.data.properties.tool_trampoline ~= '' then
        self.template.tools.trampoline = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_trampoline) or 0,
            selected = 'item_umbrella_s.png',
            normal = 'item_umbrella_n.png',
            disabled = 'item_umbrella_d.png',
            meta = getTableProperty(self.data,'trampoline',{}),
        }
    end

    if self.data.properties.tool_elastic and self.data.properties.tool_elastic ~= '' then
        self.template.tools.elastic = {
            type = 'tool',
            count = tonumber(self.data.properties.tool_elastic) or 0,
            selected = 'item_carabiner_s.png',
            normal = 'item_carabiner_n.png',
            disabled = 'item_carabiner_d.png',
            meta = getTableProperty(self.data,'elastic',{}),
        }
    end

    if self.data.properties.tool_blink and self.data.properties.tool_blink ~= '' then
        self.template.tools.blink = self.data.properties.tool_blink
    end

    -- Since Lua 5.2 `loadstring` and `setfenv` is deprecated and replaced with `load`
    -- local context = { self = self }
    -- load('self.template.assets.batch = {'..self.data.properties.batch..'}',nil,'t',context)()
    self.template.assets.spritesheets = getTableProperty(self.data,'spritesheets')
    self.template.assets.particleBatch = getTableProperty(self.data,'particleBatch')
    self.template.assets.batch = getTableProperty(self.data,'batch')

    -- Custom scripts
    if self.data.properties.customScripts ~= '' then
        self.template.scripts = getTableProperty(self.data,'customScripts')
    end

    local background = {
        type = 'background',
        sprite = self.data.properties.backgroundSprite,
        spriteColor = getTableProperty(self.data,'backgroundSpriteColor'),
        defaultColor = load('return '..self.data.properties.defaultColor,nil,'t',context)(),
    }
    table.insert(self.template.graph,background)

    -- graph
    local func_map = {
        ground = self.parseGrounds,
        rope = self.parseRope,
        coin = self.parseCoin,
        target = self.parseTarget,
        player = self.parsePlayer,
        balloon = self.parseBalloon,
        dancingSprite = self.parseDancingSprite,
        slider = self.parseSlider,
        line = self.parseDrawLine,
        infiniteSprite = self.parseInfiniteSprite,
        polygon = self.parseDrawPolygon,
        texture = self.parseTexture,
        scrollingTexture = self.parseScrollingTexture,
        sprite = self.parseSprite,
        bad = self.parseBad,
        path = self.void,
        boundary = self.parseBoundary,
        fan = self.parseFan,
        floatingPlatform = self.parseFloatingPlatform,
        spear = self.parseSpear,
        cardboard = self.parseCardboard,
        chain = self.parseChain,
        teleport = self.parseTeleport,
        circle = self.parseCircleBody,
        box = self.parseBoxBody,
        -- polygonBody = self.parsePolygonBody, -- Generic Sprite polygon body -- TODO
        textureBody = self.parseTextureBody, -- Generic Texture polugon body
        beachBall = self.parseBeachBall,
        trampoline = self.parseTrampoline,
        platterLift = self.parsePlatterLift,
        iceGround = self.parseIceGround,
        elasticRope = self.parseElasticRope,
        badPathFinder = self.parseBadPathFinder,
        badFollow = self.parseBadFollow,
        shadow = self.parseShadow,
        moon = self.parseMoon,
        crab = self.parseCrab,
        seaLion = self.parseSeaLion,
        -- light = self.parseLight,
    }
    for _,layer in ipairs(self.data.layers) do
        self.currentLayer = layer
        print('Parsing layer:',self.currentLayer.name)
        local grounds = {}
        for _,o in ipairs(self.currentLayer.objects) do
            local func = func_map[o.type]
            if not func then
                print('WARNING: Unknown object type:',o.type)
            elseif o.type == 'ground' then
                table.insert(grounds,o)
            else
                func(self,o)
            end
        end
        -- Parse bundled items
        if #grounds > 0 then self:parseGrounds(grounds) end
    end
end

function EditorConvert:convert(deploy)
    rc, msg = xpcall(function()
        print 'Begin convertion...'
        self:decode(self.filename)
        self:parse()
        self:encode('_tmp_level.json')
        os.execute(('cat _tmp_level.json | python -mjson.tool > ../data/S%02d/S%02dE%02d.json'):format(self.template.season,self.template.season,self.template.levelid))
        if deploy then
            self:createDeployScript();
            os.execute('python ../../tools/client/concli.py --conf ../../tools/client/concli.conf --lua refreshAssets_auto.lua')
        end
        print 'Convertion done!'
    end, function(err) print(err); return debug.traceback(err) end)
end

function EditorConvert:createDeployScript()
    local script = [[
    -- Auto generated by EditorConvert.lua. Do NOT edit this file manually.
    local urls = {
        'data/S%02d/S%02dE%02d.json',
        -- COCOSBUILDER
        -- 'data/ccb/pause.ccbi',
        -- 'data/ccb/winscene.ccbi',
        -- 'data/ccb/levels.ccbi',
        -- SPRITES
        -- 'hd/stars_texture.png'
        -- 'hd/season1_background.png',
        -- 'hd/cloud_parallax1.png',
        -- 'hd/cloud_parallax2.png',
        -- 'hd/wave_texture_1.png',
        -- 'hd/wave_texture_2.png',
        'hd/actions.plist',
        'hd/actions.png',
        -- 'hd/balloon_rope.png',
        -- 'hd/rainbow.png',
        -- 'hd/ghost_fire_particle.png',
        -- 'hd/loading_sprite.png',
        -- 'hd/star_particle_2.png',
        -- LUA MODULES
        -- 'lua/main.lua', -- Not a module. It will not reload until the application restarts.
        -- 'lua/class.lua',
        'lua/util.lua',
        'lua/manager.lua',
        -- 'lua/anim.lua',
        -- 'lua/settings.lua',
        -- 'lua/mediator.lua',
        -- 'lua/scroll.lua',
        -- 'lua/mainmenu.lua',
        'lua/factory.lua',
        -- 'lua/hud.lua',
        'lua/level.lua',
        -- 'lua/grid.lua',
        -- 'lua/physics.lua',
        -- 'lua/particle.lua',
        -- 'lua/particles/ghostfire.lua',
        -- 'lua/particles/stars2.lua',
        -- 'lua/refreshAssets.lua',
    }

    -- Package name are the name used in the `require` command (that is the package filename)
    package.loaded.remotecontrol = nil
    package.loaded.dummydb = nil
    package.loaded.settings = nil
    package.loaded.util = nil
    package.loaded.manager = nil
    package.loaded.notification = nil
    package.loaded.hud = nil
    package.loaded.mainmenu = nil
    package.loaded.anim = nil
    package.loaded.factory = nil
    package.loaded.level = nil
    package.loaded.mediator = nil
    package.loaded.scroll = nil
    package.loaded.physics = nil
    package.loaded.class = nil
    package.loaded.grid = nil
    package.loaded.particle = nil
    package.loaded['particles/ghostfire'] = nil
    package.loaded['particles/stars2'] = nil

    local vec = std.vector_std__string_:new_local()
    for i,v in ipairs(urls) do
        vec:push_back(v)
    end
    pix2d_console.Command():refreshAssets('http://192.168.1.10:80/gameplay/',vec)

    -- reload required packages
    local manager = require 'manager'
    local mediator = require 'mediator'
    local util = require 'util'

    manager:init() -- manager was unloaded. Must call init again.
    -- Don't call release memory here or it will crash because of CCParticleBatchNode
    -- but memory should be release in the loading scene
    -- util.releaseMemory()
    -- manager:resetGame()
    mediator:publish(mediator.ns.runLevelScene,%d,%d,true) -- season, level, releaseMemory
    ]]
    local season = self.template.season
    local level = self.template.levelid
    local file = io.open('refreshAssets_auto.lua','w')
    file:write(string.format(script,season,season,level,season,level))
    file:close()
end

function EditorConvert:init(filename)
    self.filename = filename
    return self
end

-- Return this package
return EditorConvert
-- EOF
