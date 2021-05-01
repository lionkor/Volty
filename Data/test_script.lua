local ax = 0
local ay = 0
local bx = 0
local by = 0
local move = false

local speed = 5.5

function update(dt)
    if not move then
        return
    end
    ax, ay = Entity.position()
    local dirx = bx - ax
    local diry = by - ay
    if Vec.length(dirx, diry) > speed then
        dirx, diry = Vec.normalize(dirx, diry)
        dirx = dirx * speed
        diry = diry * speed
        Entity.move_by(dirx, diry)
    end
end

function on_mouse_move(x, y)
    if move then
        bx = x
        by = y
    end
end

function on_mouse_down(mb, x, y)
    if mb == MouseButton.LMB then
        Engine.log_info("LMB down")
        move = true
        bx = x
        by = y 
    end
end

function on_mouse_up(mb, x, y)
    if mb == MouseButton.LMB then
        Engine.log_info("LMB up")
        move = false
    end
end

