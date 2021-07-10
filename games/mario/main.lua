WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

push = require 'push'

Class = require 'class'

require 'Util'
require 'Map'


function love.load()
    math.randomseed(os.time())
    
    map = Map()

    love.graphics.setDefaultFilter('nearest', 'nearest')

    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        resizable = true,
        vsync = true
    })

    love.window.setTitle('Space Boy')

    love.keyboard.keysPressed = {}
    love.keyboard.keysReleased = {}
end

function love.resize(width, height)
    push:resize(width, height)
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end

    love.keyboard.keysPressed[key] = true
end

function love.keyboard.wasPressed(key)
    return love.keyboard.keysPressed[key]
end

function love.keyboard.wasReleased(key)
    return love.keyboard.keysReleased[key]
end

function love.keyreleased(key)
    love.keyboard.keysReleased[key] = true
end

function love.update(dt)
    map:update(dt)

    love.keyboard.keysPressed = {}
    love.keyboard.keysReleased = {}
end

function love.draw()
    push:apply('start')
    
    love.graphics.translate(math.floor(-map.camX + 0.5), math.floor(-map.camY + 0.5))

    love.graphics.clear(108/255, 140/255, 1, 1)
    map:render()

    if map.player.state == 'victory' then
        love.graphics.printf("CONGRATULATIONS!! YOU BEAT THE GAME", 530, VIRTUAL_HEIGHT/4, VIRTUAL_WIDTH, 'center')
    end
    
    push:apply('end')
end