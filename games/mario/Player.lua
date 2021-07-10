Player = Class{}

require 'Animation'

local MOVE_SPEED = 90
local JUMP_VELOCITY = 350

local candbjump = true
local spaceReleased = false

isOver = false


function Player:init(map)
    self.width = 16
    self.height = 20

    self.x = 0
    self.y = 0

    self.map = map
    self.texture = love.graphics.newImage('graphics/blue_alien.png')
    self.frames = generateQuads(self.texture, 16, 20)

    self.sounds = {
        ['jump'] = love.audio.newSource('sounds/jump.wav', 'static'),
        ['hit'] = love.audio.newSource('sounds/hit.wav', 'static'),
        ['coin'] = love.audio.newSource('sounds/coin.wav', 'static'),
        ['dbjump'] = love.audio.newSource('sounds/powerup-reveal.wav', 'static')
    }

    self.currentFrame = nil

    self.state = 'idle'
    self.direction = 'right'

    self.dx = 0
    self.dy = 0

    self.y = map.tileHeight * ((map.mapHeight - 2) / 2) - self.height
    self.x = map.tileWidth * 10

    self.animations = {
        ['idle'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[1], self.frames[2]
            },
            interval = 0.4
        },
        ['walking'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[9], self.frames[10], self.frames[11]
            },
            interval = 0.15
        },
        ['jumping'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[8]
            },
        },
        ['falling'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[5]
            },
        },
        ['dbjump'] = Animation {
            -- Failed attempt to make a "flip" animation
            texture = self.texture,
            frames = {
                self.frames[4], self.frames[7], self.frames[8]
            },
            interval = 0.15
        },
        ['victory'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[3]
            }
        }
    }

    self.animation = self.animations['idle']
    self.currentFrame = self.animation:getCurrentFrame()

    self.behaviors = {
        ['idle'] = function(dt)
            if love.keyboard.wasPressed('space') then
                self.dy = -JUMP_VELOCITY
                self.state = 'jumping'
                self.animation = self.animations['jumping']
                self.sounds['jump']:play()
            elseif love.keyboard.isDown('a') or love.keyboard.isDown('left') then
                self.dx = -MOVE_SPEED 
                self.animation = self.animations['walking']
                self.direction = 'left'
            elseif love.keyboard.isDown('d') or love.keyboard.isDown('right') then
                self.dx = MOVE_SPEED 
                self.animation = self.animations['walking']
                self.direction = 'right'
            else
                self.animation = self.animations['idle']
                self.dx = 0
            end

            self:checkRightCollision()
            self:checkLeftCollision()
            
            candbjump = true

            if not self.map:collides(self.map:tileAt(self.x + 2, self.y + self.height)) and
                not self.map:collides(self.map:tileAt(self.x + self.width - 4, self.y + self.height)) then
                
                -- ADD FALLING ANIMATION/BEHAVIOR
                self.state = 'falling'
                self.animation = self.animations['falling']
            end
        end,
        ['walking'] = function(dt)
            if love.keyboard.wasPressed('space') then
                self.dy = -JUMP_VELOCITY
                self.state = 'jumping'
                self.animation = self.animations['jumping']
                self.sounds['jump']:play()
            elseif love.keyboard.isDown('a') or love.keyboard.isDown('left') then
                self.dx = -MOVE_SPEED
                self.direction = 'left'
                self.state = 'walking'
            elseif love.keyboard.isDown('d') or love.keyboard.isDown('right') then
                self.dx = MOVE_SPEED 
                self.direction = 'right'
                self.state = 'walking'
            else
                self.dx = 0
                self.state = 'idle'
                self.animation = self.animations['idle']
            end

            self:checkRightCollision()
            self:checkLeftCollision()

            if not self.map:collides(self.map:tileAt(self.x + 2, self.y + self.height)) and
                not self.map:collides(self.map:tileAt(self.x + self.width - 4, self.y + self.height)) then
                
                -- ADD FALLING ANIMATION/BEHAVIOR
                self.state = 'falling'
                self.animation = self.animations['falling']
            end
        end,
        ['jumping'] = function(dt)
            if love.keyboard.wasReleased('space') then
                spaceReleased = true
            end
            if love.keyboard.wasPressed('space') and candbjump and spaceReleased then
                candbjump = false
                self.dy = -JUMP_VELOCITY
                self.state = 'dbjump'
                self.animation = self.animations['dbjump']
                self.animations['dbjump']:restart()
                self.sounds['dbjump']:play()
            elseif love.keyboard.isDown('a') or love.keyboard.isDown('left') then
                self.direction = 'left'
                self.dx = -MOVE_SPEED
            elseif love.keyboard.isDown('d') or love.keyboard.isDown('right') then
                self.direction = 'right'
                self.dx = MOVE_SPEED
            else
                self.dx = 0
            end

            self.dy = self.dy + self.map.gravity
            
            if self.dy > 0 then
                self.state = 'falling'
                self.animation = self.animations['falling']
            end

            self:checkRightCollision()
            self:checkLeftCollision()
        end,
        ['falling'] = function(dt)
            if self.y > 300 then
                self.y = 0
            end
            
            self.dy = self.dy + self.map.gravity

            if self.dy > JUMP_VELOCITY then
                self.dy = 300
            end

            if love.keyboard.wasReleased('space') then
                spaceReleased = true
            end

            if love.keyboard.wasPressed('space') and candbjump and spaceReleased then
                candbjump = false
                self.dy = -JUMP_VELOCITY
                self.state = 'dbjump'
                self.animation = self.animations['dbjump']
                self.animations['dbjump']:restart()
                self.sounds['dbjump']:play()
            elseif love.keyboard.isDown('a') or love.keyboard.isDown('left') then
                self.direction = 'left'
                self.dx = -MOVE_SPEED
            elseif love.keyboard.isDown('d') or love.keyboard.isDown('right') then
                self.direction = 'right'
                self.dx = MOVE_SPEED
            else
                self.dx = 0
            end
            
            if self.map:collides(self.map:tileAt(self.x, self.y + self.height)) or
                self.map:collides(self.map:tileAt(self.x + self.width - 1, self.y + self.height)) then
                
                self.dy = 0
                self.state = 'idle'
                self.animation = self.animations['idle']
                self.y = (self.map:tileAt(self.x, self.y + self.height).y - 1) * self.map.tileHeight - self.height
            end

            self:checkRightCollision()
            self:checkLeftCollision()
        end,
        ['dbjump'] = function(dt)
            if love.keyboard.isDown('a') or love.keyboard.isDown('left') then
                self.direction = 'left'
                self.dx = -MOVE_SPEED
            elseif love.keyboard.isDown('d') or love.keyboard.isDown('right') then
                self.direction = 'right'
                self.dx = MOVE_SPEED
            else
                self.dx = 0
            end

            self.dy = self.dy + self.map.gravity
            
            if self.dy > 0 then
                self.state = 'falling'
                self.animation = self.animations['falling']
            end

            self:checkRightCollision()
            self:checkLeftCollision()
        end, 
        ['victory'] = function(dt)
            self.dx = 0
            self.dy = 8
            isOver = true
            map.music:stop()

            if self.map:collides(self.map:tileAt(self.x - 1, self.y + self.height -1)) or
                self.map:collides(self.map:tileAt(self.x + self.width, self.y + self.height -1)) then
                self.dy = 0
                map.sounds['victory']:stop()
                return
            end
            map.sounds['victory']:setLooping(false)
            map.sounds['victory']:setVolume(0.4)
            map.sounds['victory']:play()
        end
    }
end

function Player:update(dt)
    self.behaviors[self.state](dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()

    self.x = self.x + self.dx * dt
    
    self:calculateJumps()
    self:endGame()

    self.y = self.y + self.dy * dt
end

function Player:calculateJumps()
    if self.dy < 0 then
        if (self.map:tileAt(self.x, self.y).id ~= TILE_EMPTY and self.map:tileAt(self.x, self.y).id ~= CLOUD_LEFT and self.map:tileAt(self.x, self.y).id ~= CLOUD_RIGHT) or 
            (self.map:tileAt(self.x + self.width - 1, self.y).id ~= TILE_EMPTY and self.map:tileAt(self.x + self.width - 1, self.y).id ~= CLOUD_RIGHT and self.map:tileAt(self.x + self.width -1, self.y).id ~= CLOUD_LEFT)  then
            -- reset dy velocity
            self.dy = 0
            
            local playCoin = false
            local playHit = false

            if self.map:tileAt(self.x, self.y).id == JUMP_BLOCK then
                self.map:setTile(math.floor(self.x / self.map.tileWidth) + 1,
                    math.floor(self.y / self.map.tileHeight) + 1, JUMP_BLOCK_HIT)
                playCoin = true
            else
                playHit = true
            end
            if self.map:tileAt(self.x + self.width - 1, self.y).id == JUMP_BLOCK then
                self.map:setTile(math.floor((self.x + self.width - 1) / self.map.tileWidth) + 1,
                    math.floor(self.y / self.map.tileHeight) + 1, JUMP_BLOCK_HIT)
                playCoin = true
            else
                playHit = true    
            end

            if playCoin then
                self.sounds['coin']:play()
            else
                self.sounds['hit']:play()
            end
        end
    end
end

function Player:endGame()
    if self.map:isEnd(self.map:tileAt(self.x - 1, self.y)) or 
        self.map:isEnd(self.map:tileAt(self.x - 1, self.y + self.height -1)) or
        self.map:isEnd(self.map:tileAt(self.x + self.width, self.y)) or
        self.map:isEnd(self.map:tileAt(self.x + self.width, self.y + self.height -1)) then
            self.state = 'victory'
            self.animation = self.animations['victory']
    end
end

function Player:checkLeftCollision()
    if self.dx < 0 then

        if self.map:collides(self.map:tileAt(self.x - 1, self.y)) or
            self.map:collides(self.map:tileAt(self.x - 1, self.y + self.height -1)) or
            self.x < 1 then
            
            self.dx = 0
            self.x = self.map:tileAt(self.x - 1, self.y).x * self.map.tileWidth
        end
    end
end

function Player:checkRightCollision()
    if self.dx > 0 then

        if self.map:collides(self.map:tileAt(self.x + self.width, self.y)) or
            self.map:collides(self.map:tileAt(self.x + self.width, self.y + self.height -1)) or
            self.x > map.mapWidthPixels - self.width then
            
            self.dx = 0
            self.x = (self.map:tileAt(self.x + self.width, self.y).x - 1) * self.map.tileWidth - self.width
        end
    end
end

function Player:render()
    local scaleX
    if self.direction == 'right' then
        scaleX = 1
    else
        scaleX = -1
    end
    
    love.graphics.draw(self.texture, self.animation:getCurrentFrame(),
        math.floor(self.x + self.width/2), math.floor(self.y + self.height/2),
        0, scaleX, 1,
        self.width/2, self.height/2)
end
