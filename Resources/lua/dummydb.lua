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

local settings = require 'settings'()
local status = settings.defaultLevelStatus -- lock = -2, unlock = -1, completed = 0, score = 1,2 or 3 stars
local defaultThreshold = 20

local db = {}; db.__index = db

setmetatable(db,
{
    __call = function(t,k)
        return {
            version = '0.1',
            defaults = {
                -- Users defaults
                cSeasonid = 1, -- Current active season
                cLevelid = 1, -- Current active level
                cCostume = 0 -- Current player's costume
            },
            assets = {
                costumes = {
                    'chicken',
                    'rabbit',
                    'pineapple',
                    'cat',
                    'bear',
                    'dog',
                    'strawberry',
                    'penguin',
                    'orange',
                    'octopus',
                    'apple',
                    'cow',
                    'lion',
                    'pig',
                }
            },
            -- List of seasons
            seasons = {
                {
                    threshold = 0,
                    levels = {
                        -- level status can be: locked (status), unlocked (-1), completed (0), bonus1 (1), bonus2 (2), bonus3 (3)
                        { score = -1 }, -- the very first level must be unlocked
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                    }
                }, {
                    threshold = defaultThreshold,
                    levels = {
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                    }
                }, {
                    threshold = defaultThreshold,
                    levels = {
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                    }
                }, {
                    threshold = defaultThreshold,
                    levels = {
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                        { score = status },
                    }
                }
            }
        }
    end
})

return db
