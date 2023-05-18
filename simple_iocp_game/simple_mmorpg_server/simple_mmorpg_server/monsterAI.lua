local STATE_IDLE = 0
local STATE_CHASE = 1

monster = {
   x = 0,
   y = 0,   
   view_range = 2,
   state = STATE_IDLE,
   target = nil,
}

function set_position(pos)
	x = pos.first
    y = pos.second
end

function move(monster, x, y)
   monster.x = x
   monster.y = y
end

function changeState(monster, newState)
   monster.state = newState
end

function heuristic(startX, startY, targetX, targetY)
   return math.abs(startX - targetX) + math.abs(startY - targetY)
end

function aStarSearch(startX, startY, targetX, targetY)   
   local openSet = {}
   table.insert(openSet, { x = startX, y = startY, g = 0, f = 0 })
   
   local visited = {}
   
   while #openSet > 0 do
      -- ���� ���� f���� ���� ��ǥ�� ã��
      local currentIndex = 1
      for i = 2, #openSet do
         if openSet[i].f < openSet[currentIndex].f then
            currentIndex = i
         end
      end
      
      local current = table.remove(openSet, currentIndex)
      
      -- ��ǥ ��ġ�� �����ϸ� ��θ� ��ȯ
      if current.x == targetX and current.y == targetY then
         return current.x, current.y
      end
      
      -- �̿��� ��ǥ�� ����Ͽ� Ž��
      local neighbors = {
         { x = current.x, y = current.y - 1 },
         { x = current.x, y = current.y + 1 },
         { x = current.x - 1, y = current.y },
         { x = current.x + 1, y = current.y }
      }
      
      for i, neighbor in ipairs(neighbors) do
         local newX = neighbor.x
         local newY = neighbor.y
         
         -- �̵� ������ ������ �߰��Ͽ��� �� (e.g., �� �˻�)
         local isValidMove = true
         
         -- �湮���� �ʾҰ� �̵� ������ ��ǥ�� ��쿡�� ó��
         if isValidMove and not visited[newX] then
            visited[newX] = {}
            visited[newX][newY] = true
            
            local g = current.g + 1
            local h = heuristic(newX, newY, targetX, targetY)
            local f = g + h
            
            table.insert(openSet, { x = newX, y = newY, g = g, f = f })
         end
      end
   end
   
   -- ��θ� ã�� ���� ��� ���� ��ġ�� ��ȯ�Ͽ� ���� ��ġ�� ����
   return startX, startY
end

function updateAI(monster, player)
   local dx = player.x - monster.x
   local dy = player.y - monster.y
   local distance = math.sqrt(dx * dx + dy * dy)
      
   if distance < monster.range then
      monster.target = player
      changeState(monster, STATE_CHASE)
   else
      monster.target = nil
      changeState(monster, STATE_IDLE)
   end
      
   if monster.state == STATE_CHASE and monster.target ~= nil then      
      local targetX, targetY = aStarSearch(monster.x, monster.y, monster.target.x, monster.target.y)
      move(monster, targetX, targetY)
   end
end
