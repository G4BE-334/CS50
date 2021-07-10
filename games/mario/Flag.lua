Flag = Class{}

require 'Animation'

function Flag:init(map)
    self.width = map.tileWidth
    self.height = map.tileHeight

    self.x = 0
    self.y = 0

    self.map = map
    self.texture = love.graphics.newImage('graphics/spritesheet.png')
    self.frames = generateQuads(self.texture, 16, 16)

    self.currentFrame = nil

    self.state = 'waving'

    self.dx = 0
    self.dy = 0

    self.y = map.tileHeight * (map.mapHeight / 2 - 4) - self.height
    self.x = map.tileWidth * 56 - self.width / 2

    self.animations = {
        ['waving'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[13], self.frames[14], self.frames[15]
            },
            interval = 0.15
        },
        ['end'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[13]
            },
        }
    }

    self.animation = self.animations['waving']
    self.currentFrame = self.animation:getCurrentFrame()

    self.behaviors = {
        ['waving'] = function(dt)            
            self.dy = 0
            
            if isOver then
                self.animation = self.animations['end']
                self.state = 'end'
            end
        end,
        ['end'] = function(dt)
            self.dy = 8

            if self.map:collides(self.map:tileAt(self.x - 1, self.y + self.height -1)) or
                self.map:collides(self.map:tileAt(self.x + self.width, self.y + self.height -1)) then
                self.dy = 0
            end
        end
    }
end

function Flag:update(dt)
    self.behaviors[self.state](dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()
    self.y = self.y + self.dy * dt
end

function Flag:render()
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