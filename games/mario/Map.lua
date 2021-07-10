-- Require classes
require 'Player'
require 'Flag'
require 'Util'

Map = Class()

-- Define spritesheet quads
TILE_BRICK = 1
TILE_EMPTY = 4

CLOUD_LEFT = 6
CLOUD_RIGHT = 7

BUSH_LEFT = 2
BUSH_RIGHT = 3

MUSHROOM_TOP = 10
MUSHROOM_BOTTOM = 11

JUMP_BLOCK = 5
JUMP_BLOCK_HIT = 9

FLAG_POLE_TOP = 8
FLAG_POLE_MIDDLE = 12
FLAG_POLE_BOTTOM = 16

FLAG1 = 13
FLAG2 = 14
FLAG3 = 15

local SCROLL_SPEED = 62

-- Initialize the map
function Map:init()
    self.spritesheet = love.graphics.newImage('graphics/spritesheet.png')
    self.tileWidth = 16
    self.tileHeight = 16
    self.mapWidth = 60
    self.mapHeight = 28

    self.tiles = {}

    -- Gravity's velocity
    self.gravity = 15

    -- Player object
    self.player = Player(self)

    -- Flag object
    self.flag = Flag(self)

    -- Position where at the camera starts
    self.camX = 0
    self.camY = -3

    -- Call the generateQuads function to create tiles from the spritesheet
    self.tileSprites = generateQuads(self.spritesheet, self.tileWidth, self.tileHeight)

    self.music = love.audio.newSource('sounds/music.wav', 'static')

    self.sounds = { 
        ['victory'] = love.audio.newSource('sounds/Victory.mid', 'static')
    }

    self.mapWidthPixels = self.mapWidth * self.tileWidth
    self.mapHeightPixels = self.mapHeight * self.tileHeight

    -- Filling the map with empty tiles
    for y = 1, self.mapHeight do
        for x = 1, self.mapWidth do
            self:setTile(x, y, TILE_EMPTY)
        end
    end

    -- Fill the map with tiles and obstacles
    local x = 1
    while x < self.mapWidth - 16 do

        -- Generate clouds throughout the map but the last block
        if x < self.mapWidth - 2 then
            -- 10% chance of generating clouds
            if math.random(10) == 1 then
                
                local cloudStart = math.random(self.mapHeight / 2 - 6)

                self:setTile(x, cloudStart, CLOUD_LEFT)
                self:setTile(x + 1, cloudStart, CLOUD_RIGHT)
            end
        end

        -- Generate on ground obstacles
        -- 5% chance of generating mushroom/pipe
        if math.random(20) == 1 then

            self:setTile(x, self.mapHeight / 2 - 2, MUSHROOM_TOP)
            self:setTile(x, self.mapHeight / 2 - 1, MUSHROOM_BOTTOM)

            -- Always generate bricks beneath on groun obstacles
            for y = self.mapHeight / 2, self.mapHeight do
                self:setTile(x, y, TILE_BRICK)
            end

            x = x + 1
        
        -- 10% chance of generating bushes
        elseif math.random(10) == 1 and x < self.mapWidth - 3 then
            local bushLevel = self.mapHeight / 2 -1

            -- Left bush tile
            self:setTile(x, bushLevel, BUSH_LEFT)
            for y = self.mapHeight / 2, self.mapHeight do
                self:setTile(x, y, TILE_BRICK)
            end
            x = x + 1

            -- Right bush tile
            self:setTile(x, bushLevel, BUSH_RIGHT)
            for y = self.mapHeight / 2, self.mapHeight do
                self:setTile(x, y, TILE_BRICK)
            end
            x = x + 1

        -- 10% chance of not having bricks on the walkway
        elseif math.random(10) ~= 1 then
            for y = self.mapHeight / 2, self.mapHeight do
                self:setTile(x, y, TILE_BRICK)
            end

            -- 1 in 15 chance of having a jump block above
            if math.random(15) == 1 then
                self:setTile(x, self.mapHeight / 2 - 4, JUMP_BLOCK)
            end

            x = x + 1
        else
            x = x + 2
        end
    end

    local a = 1
    -- Generate end of level obstacles
    while x < self.mapWidth + 1 do
        -- Create the walkway
        if x < self.mapWidth - 8 then 
            for y = self.mapHeight / 2, self.mapHeight do
                self:setTile(x, y, TILE_BRICK)
            end
            x = x + 1
        end

        -- Generate the ladder for SpaceBoy
        if a < 8 then
            for i = 1, a do
                self:setTile(x, self.mapHeight / 2 - i, TILE_BRICK)
            end
            a = a + 1
        else
            -- Prepare the land
            if a >= 12 then
                for y = self.mapHeight / 2, self.mapHeight do
                    self:setTile(x, y, TILE_BRICK)
                end
            end
            
            -- Populate the flag pole and flag 
            if a == 13 then
                self:setTile(x, self.mapHeight / 2 - 4, FLAG_POLE_TOP)
                self:setTile(x, self.mapHeight / 2 - 3, FLAG_POLE_MIDDLE)
                self:setTile(x, self.mapHeight / 2 - 2, FLAG_POLE_MIDDLE)
                self:setTile(x, self.mapHeight / 2 - 1, FLAG_POLE_BOTTOM)
            end
            a = a + 1
            x = x + 1
        end

    end

    self.music:setLooping(true)
    self.music:setVolume(0.25)
    self.music:play()
end

function Map:collides(tile)
    local collidables = {
        TILE_BRICK, JUMP_BLOCK, JUMP_BLOCK_HIT, MUSHROOM_BOTTOM, MUSHROOM_TOP
    }

    for _, v in ipairs(collidables) do
        if tile.id == v then
            return true
        end
    end

    return false
end

function Map:isEnd(tile)
    local flagTiles = {
        FLAG_POLE_TOP, FLAG_POLE_BOTTOM, FLAG_POLE_MIDDLE
    }

    for _, v in ipairs(flagTiles) do
        if tile.id == v then
            return true
        end
    end

    return false
end

function Map:update(dt)
    self.player:update(dt)
    self.flag:update(dt)

    self.camX = math.max(0, math.min(self.player.x - VIRTUAL_WIDTH / 2, 
        math.min(self.mapWidthPixels - VIRTUAL_WIDTH, self.player.x)))
end

function Map:tileAt(x, y)
    return {
        x = math.floor(x / self.tileWidth) + 1,
        y = math.floor(y / self.tileHeight) + 1,
        id = self:getTile(math.floor(x / self.tileWidth) + 1, math.floor(y / self.tileHeight) + 1)
    }
end

function Map:getTile(x, y)
    return self.tiles[(y - 1) * self.mapWidth + x]
end

function Map:setTile(x, y, id)
    -- Index as a one dimensional array as it were a two dimensional array
    self.tiles[(y - 1) * self.mapWidth + x] = id
end

function Map:render()
    for y = 1, self.mapHeight do
        for x = 1, self.mapWidth do
            local  tile = self:getTile(x, y)
            if tile ~= TILE_EMPTY then
                love.graphics.draw(self.spritesheet, self.tileSprites[tile],
                    (x-1) * self.tileWidth, (y-1) * self.tileHeight)
            end
        end
    end

    self.flag:render()
    self.player:render()
end