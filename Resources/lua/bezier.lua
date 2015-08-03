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

-- Packages dependencies
local path_bezier3 = require 'lib/path2d/path_bezier3'
local path_line = require 'lib/path2d/path_line'

-- The package table
local Bezier = {}; Bezier.__index = Bezier

setmetatable(Bezier,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            -- package variables
        }, Bezier)
    end
})

-- Returns x,y
function Bezier:pointAt(t)
    return path_bezier3.point(t,self.x1,self.y1,self.x2,self.y2,self.x3,self.y3,self.x4,self.y4)
end

-- Returns x,y
function Bezier:derivativeAt(t)
    return
        path_bezier3.derivative1_for(t,self.ax,self.bx,self.cx),
        path_bezier3.derivative1_for(t,self.ay,self.by,self.cy)
end

function Bezier:length(t)
    return path_bezier3.length(t,self.x1,self.y1,self.x2,self.y2,self.x3,self.y3,self.x4,self.y4)
end

-- Cast a line to a bezier. Return this bezier initialized with a line.
function Bezier:lineToBezier(x1,y1,x2,y2)
    return self:init(path_line.to_bezier3(x1,y1,x2,y2))
end

-- TODO implement other path_bezier3 functions

-- init with unpacked parameters: init(x1,y1,x2,y2,x3,y3,x4,y4)
-- where x2,y2 and x3,y3 are control points and x1,y1 and x4,y4 are end points
function Bezier:init(x1,y1,x2,y2,x3,y3,x4,y4)
    self.x1 = x1
    self.y1 = y1
    self.x2 = x2
    self.y2 = y2
    self.x3 = x3
    self.y3 = y3
    self.x4 = x4
    self.y4 = y4
    self.ax,self.bx,self.cx = path_bezier3.coefficients(x1,x2,x3,x4)
    self.ay,self.by,self.cy = path_bezier3.coefficients(y1,y2,y3,y4)
    return self
end

function Bezier:initWithPoints(p1,p2,p3,p4)
    return self:init(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y)
end

-- Return this package
return Bezier
-- EOF
