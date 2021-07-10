function generateQuads(atlas, tileWidth, tileHeight)
    local sheetWidth = atlas:getWidth() / tileWidth
    local sheetHeight = atlas:getHeight() / tileHeight

    local sheetCounter = 1
    local quads = {}

    -- Everything in Lua starts at 1 index not 0 like most programming languages
    -- However, pixels specification starts at 0 so y = 0
    for y = 0, sheetHeight - 1 do
        for x = 0, sheetWidth - 1 do
            quads[sheetCounter] = love.graphics.newQuad(x * tileWidth, y * tileHeight, tileWidth, tileHeight, atlas:getDimensions() )
            sheetCounter = sheetCounter + 1
        end
    end

    return quads
end