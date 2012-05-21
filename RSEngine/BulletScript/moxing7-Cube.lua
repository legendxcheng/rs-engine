-- procedure
-- rsengine calls updateFrame() to move the vertex system to a new frame
-- rsengine calls updateInterpoloation() to work out the current position of vertexes with interpolation
-- rsengine get strip count and vetxCount to featch vertexes in vetx 

-- the start coordination is 0, and bullets go to -x direction


-- the template implements a simple bullet storm
-- x = sin(t) * 100
-- y = cos(t) * 100
-- z = t
-- stripCount == 1
-- vetxCount[1] = 50

function initialize()
	vetx = {} -- empty array
	stripCount = 1 -- modify here
	vetxCount = {} -- empty array to store vertex count for each strip
	currentFrame = 0 -- current frame
	maxFrame = 1200 -- max frame count, if current frame is bigger than maxFrame, then the bulletstorm will be removed from system
	lineCount = 0 -- line count
	line = {} -- stotre line index in vetx
	lineUpdated = 0 -- 0 for not updated since last call 1 for updated since last call
	stripCount = 1
	vetxCount[1] = 240
end

function updateFrame()
	currentFrame = currentFrame + 1/2
	local tmpt = 1
	local xgap = 200
		for i=1, 240 do 
			--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
			if (i <= 20) then
				vetx[tmpt] = 400 - currentFrame 
			elseif(i <= 40) then
			    vetx[tmpt] = 400 - currentFrame + xgap 
			elseif(i <= 60) then
			    vetx[tmpt] = 400 - currentFrame + 2 * xgap
			elseif(i <= 80) then
			    vetx[tmpt] = 400 - currentFrame + 3 * xgap
			elseif (i <= 100) then
				vetx[tmpt] = 400 - currentFrame + 20 * (i - 80)
			elseif(i <= 120) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 100) + xgap
			elseif(i <= 140) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 120)
			elseif(i <= 160) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 140) + xgap
			elseif (i <= 180) then
				vetx[tmpt] = 400 - currentFrame + 10 * (i - 160)
			elseif(i <= 200) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 180) + 2 * xgap
			elseif(i <= 220) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 200)
			elseif(i <= 240) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 220) + 2 * xgap
            end				
			tmpt = tmpt + 1
			if (i <= 20) then
				vetx[tmpt] = 220 - i * 25
			elseif(i <= 40) then
				vetx[tmpt] = 280 - (i - 20 ) * 25
			elseif(i <= 60) then
				vetx[tmpt] = 220 - (i - 40) * 25
			elseif(i <= 80) then
				vetx[tmpt] = 280 - (i - 60) * 25
			elseif(i <= 100) then
				vetx[tmpt] = 220 
			elseif(i <= 120) then
				vetx[tmpt] = 280 
			elseif(i <= 140) then
				vetx[tmpt] = -280
			elseif(i <= 160) then
				vetx[tmpt] = -220 
			elseif(i <= 180) then
				vetx[tmpt] = 220 + (i - 160) * 3
			elseif(i <= 200) then
				vetx[tmpt] = 220 + (i - 180) * 3 
			elseif(i <= 220) then
				vetx[tmpt] = -280 + (i - 200) * 3
			elseif(i <= 240) then
				vetx[tmpt] = -280 + (i - 220) * 3
			end			
			tmpt = tmpt + 1
			if (i <= 20) then
				vetx[tmpt] = 220
			elseif(i <= 40) then
				vetx[tmpt] = -220
			elseif(i <= 60) then
				vetx[tmpt] = 220
			elseif(i <= 80) then
				vetx[tmpt] = -220
			elseif(i <= 100) then
				vetx[tmpt] = 220 
			elseif(i <= 120) then
				vetx[tmpt] = -220 
			elseif(i <= 140) then
				vetx[tmpt] = 220
			elseif(i <= 160) then
				vetx[tmpt] = -220 
			elseif(i <= 180) then
				vetx[tmpt] = 220 
			elseif(i <= 200) then
				vetx[tmpt] = 220 
			elseif(i <= 220) then
				vetx[tmpt] = -220
			elseif(i <= 240) then
				vetx[tmpt] = -220 
			end	
			tmpt = tmpt + 1
		end
end

function updateInterpolation(intp)
	--vetx = {} -- empty array
	currentFrame = currentFrame + 1/2
	local tmpt = 1
	local xgap = 200
		for i=1, 240 do 
			--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
			if (i <= 20) then
				vetx[tmpt] = 400 - currentFrame - intp
			elseif(i <= 40) then
			    vetx[tmpt] = 400 - currentFrame + xgap - intp
			elseif(i <= 60) then
			    vetx[tmpt] = 400 - currentFrame + 2 * xgap - intp
			elseif(i <= 80) then
			    vetx[tmpt] = 400 - currentFrame + 3 * xgap - intp
			elseif (i <= 100) then
				vetx[tmpt] = 400 - currentFrame + 20 * (i - 80) - intp
			elseif(i <= 120) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 100) + xgap - intp
			elseif(i <= 140) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 120) - intp
			elseif(i <= 160) then
			    vetx[tmpt] = 400 - currentFrame + 20 * (i - 140) + xgap - intp
			elseif (i <= 180) then
				vetx[tmpt] = 400 - currentFrame + 10 * (i - 160) - intp
			elseif(i <= 200) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 180) + 2 * xgap - intp
			elseif(i <= 220) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 200) - intp
			elseif(i <= 240) then
			    vetx[tmpt] = 400 - currentFrame + 10 * (i - 220) + 2 * xgap - intp
            end				
			tmpt = tmpt + 1
			if (i <= 20) then
				vetx[tmpt] = 220 - i * 25
			elseif(i <= 40) then
				vetx[tmpt] = 280 - (i - 20 ) * 25
			elseif(i <= 60) then
				vetx[tmpt] = 220 - (i - 40) * 25
			elseif(i <= 80) then
				vetx[tmpt] = 280 - (i - 60) * 25
			elseif(i <= 100) then
				vetx[tmpt] = 220 
			elseif(i <= 120) then
				vetx[tmpt] = 280 
			elseif(i <= 140) then
				vetx[tmpt] = -280
			elseif(i <= 160) then
				vetx[tmpt] = -220 
			elseif(i <= 180) then
				vetx[tmpt] = 220 + (i - 160) * 3
			elseif(i <= 200) then
				vetx[tmpt] = 220 + (i - 180) * 3 
			elseif(i <= 220) then
				vetx[tmpt] = -280 + (i - 200) * 3
			elseif(i <= 240) then
				vetx[tmpt] = -280 + (i - 220) * 3
			end			
			tmpt = tmpt + 1
			if (i <= 20) then
				vetx[tmpt] = 220
			elseif(i <= 40) then
				vetx[tmpt] = -220
			elseif(i <= 60) then
				vetx[tmpt] = 220
			elseif(i <= 80) then
				vetx[tmpt] = -220
			elseif(i <= 100) then
				vetx[tmpt] = 220 
			elseif(i <= 120) then
				vetx[tmpt] = -220 
			elseif(i <= 140) then
				vetx[tmpt] = 220
			elseif(i <= 160) then
				vetx[tmpt] = -220 
			elseif(i <= 180) then
				vetx[tmpt] = 220 
			elseif(i <= 200) then
				vetx[tmpt] = 220 
			elseif(i <= 220) then
				vetx[tmpt] = -220
			elseif(i <= 240) then
				vetx[tmpt] = -220 
			end	
			tmpt = tmpt + 1
		end
end

function isDone()
	if (currentFrame > maxFrame) then
		return 1
	end;
	return 0
end