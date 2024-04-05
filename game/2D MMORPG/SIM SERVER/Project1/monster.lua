local MAPWIDTH = 2000
local MAPHEIGHT = 2000

local function isValidMove(x, y)
    return x >= 0 and x < MAPWIDTH and y >= 0 and y < MAPHEIGHT
end

-- 추적이동 함수
function findPath(startX, startY, targetX, targetY)
    local dx = { 0, 0, -1, 1 }
    local dy = { -1, 1, 0, 0 }
    local visited = {}
    local stack = {}
    local priorityQueue = {}

    -- 루아 스크립트에서 우선순위 큐를 사용하기 위한 함수
    function push(element)
        table.insert(priorityQueue, element)
        table.sort(priorityQueue, function(a, b) return a.cost < b.cost end)
    end

    function pop()
        return table.remove(priorityQueue, 1)
    end

    -- A*알고리즘에 사용될 비용계산 함수
    local function heuristic(x, y, targetX, targetY)
        return math.pow(targetX - x, 2) + math.pow(targetY - y, 2)
    end

    -- 초기 위치 및 비용 추가
    push({ x = startX, y = startY, step = 0, cost = heuristic(startX, startY, targetX, targetY) })

    while #priorityQueue > 0 do
        local current = pop()
        -- 경로 저장
        table.insert(stack, current)

        -- 목표 위치에 도착하면 종료
        if current.x == targetX and current.y == targetY then
            local firstStep = table.remove(stack, 2)
            if firstStep == nil then
                return startX, startY
            else
                return firstStep.x, firstStep.y
            end
        end

        -- 경로 탐색
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

    -- 도달 불가능할 경우(현재는 항상 도달 가능)
    return -1, -1
end

-- 방황이동 함수
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