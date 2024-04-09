local MAPWIDTH = 2000
local MAPHEIGHT = 2000

local function isValidMove(x, y)
    return x >= 0 and x < MAPWIDTH and y >= 0 and y < MAPHEIGHT
end

-- �����̵� �Լ�
function findPath(startX, startY, targetX, targetY)
    local dx = { 0, 0, -1, 1 }
    local dy = { -1, 1, 0, 0 }
    local visited = {}
    local stack = {}
    local priorityQueue = {}

    -- ��� ��ũ��Ʈ���� �켱���� ť�� ����ϱ� ���� �Լ�
    function push(element)
        table.insert(priorityQueue, element)
        table.sort(priorityQueue, function(a, b) return a.cost < b.cost end)
    end

    function pop()
        return table.remove(priorityQueue, 1)
    end

    -- A*�˰����� ���� ����� �Լ�
    local function heuristic(x, y, targetX, targetY)
        return math.pow(targetX - x, 2) + math.pow(targetY - y, 2)
    end

    -- �ʱ� ��ġ �� ��� �߰�
    push({ x = startX, y = startY, step = 0, cost = heuristic(startX, startY, targetX, targetY) })

    while #priorityQueue > 0 do
        local current = pop()
        -- ��� ����
        while #stack > 0 and stack[1].step >= current.step do
            table.remove(stack, 1)
        end
        table.insert(stack, current)

        -- ��ǥ ��ġ�� �����ϸ� ����
        if current.x == targetX and current.y == targetY then
            if stack[2] == nil then
                return current.x, current.y
            else
                return stack[2].x, stack[2].y
            end
        end

        -- ��� Ž��
        for i = 1, 4 do
            local newX = current.x + dx[i]
            local newY = current.y + dy[i]
            if isValidMove(newX, newY) and not visited[newX] then
                visited[newX] = {}
            end
            if isValidMove(newX, newY) and not visited[newX][newY] then
                visited[newX][newY] = true
                push({ x = newX, y = newY, step = current.step + 1, cost = heuristic(newX, newY, targetX, targetY) })
            end
        end
    end

    -- ���� �Ұ����� ���(����� �׻� ���� ����)
    return -1, -1
end

-- ��Ȳ�̵� �Լ�
function randomMove(startX, startY)
    local x, y    
    math.randomseed(os.time())

    while true do
        x = startX
        y = startY
        local dir = math.random(1, 4)

        if dir == 1 then 
            y = y - 1
        elseif dir == 2 then 
            y = y + 1
        elseif dir == 3 then 
            x = x - 1
        else 
            x = x + 1
        end

        if isValidMove(x, y) then 
            break;
        end
    end

    return x, y
end