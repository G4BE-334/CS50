Paddle = Class{}

function Paddle:init(x, y, width, height)
    self.x = x
    self.y = y
    self.width = width
    self.height = height

    self.dY = 0
end

function Paddle:update(dt)
    if self.dY < 0 then
        self.y = math.max(0, self.y + self.dY * dt)
    elseif self.dY > 0 then
        self.y = math.min(VIRTUAL_HEIGHT - 20, self.y + self.dY * dt)
    end
end

function Paddle:render()
    love.graphics.rectangle('fill', self.x, self.y, self.width, self.height)
end
