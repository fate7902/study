monster = {
x = 0,
y = 0,
}

function SetPosition(new_x, new_y)
	monster.x = new_x
    monster.y = new_y
end

function TESTmove()
   local randomInt = math.random(1, 4)
   if randomInt == 1 then
      if monster.y > 0 then
         monster.y = monster.y - 1
      end
   elseif randomInt == 2 then
      if monster.y < 2000 then
         monster.y = monster.y + 1
      end
   elseif randomInt == 3 then
      if monster.x > 0 then
         monster.x = monster.x - 1
      end
   else 
      if monster.x < 2000 then
         monster.x = monster.x + 1
      end
   end
end