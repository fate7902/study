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
      if y > 0 then
         y = y - 1
      end
   elseif randomInt == 2 then
      if y < 2000 then
         y = y + 1
      end
   elseif randomInt == 3 then
      if x > 0 then
         x = x - 1
      end
   else 
      if x < 2000 then
         x = x + 1
      end
   end
end