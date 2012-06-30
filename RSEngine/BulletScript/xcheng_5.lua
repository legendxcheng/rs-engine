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
	maxFrame = 2400 -- max frame count, if current frame is bigger than maxFrame, then the bulletstorm will be removed from system
	-- 4 waves
	lineCount = 0 -- line count
	line = {} -- stotre line index in vetx
	lineUpdated = 0 -- 0 for not updated since last call 1 for updated since last call
	stripCount = 1
	vetxCount[1] = 200
	math.randomseed(os.time())
end

function updateFrame()
	local tframe = 0
	currentFrame = currentFrame + 1
	local phy = 0
	local waveOff = math.fmod(currentFrame, 600)
	local offy = 0 
	if (waveOff == 1) then -- new phy
		 phy = math.rad(math.random(1, 360))
		 offy = (math.random(1, 100)  - 50) * 2
	end

	local tmpt = 1
	for i=1, 60 do
		--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
		--x
		local theta = 3.1415926 / 30 * i
		local tx = 200 * math.sin(theta)
		local ty = 200 * math.cos(theta) * math.sin(phy)
		local tz = 200 * math.cos(theta) * math.cos(phy)

		vetx[tmpt] = 500 - waveOff * 2 + i * 2 + tx
			
		tmpt = tmpt + 1
			--y
		vetx[tmpt] = ty + offy
		tmpt = tmpt + 1
			--z
		vetx[tmpt] = tz
		tmpt = tmpt + 1
	end
end

function updateInterpolation(intp)
	local tframe = 0
	currentFrame = currentFrame + 1
	local phy = 0
	local offy = 0
	local waveOff = math.fmod(currentFrame, 600)
	if (waveOff == 1) then -- new phy
		 phy = math.rad(math.random(1, 360))
		 offy =  (math.random(1, 100)  - 50) * 2
	end

	local tmpt = 1
	for i=1, 60 do
		--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
		--x
		local theta = 3.1415926 / 30 * i
		local tx = 200 * math.sin(theta)
		local ty = 200 * math.cos(theta) * math.sin(phy)
		local tz = 200 * math.cos(theta) * math.cos(phy)

		vetx[tmpt] = 500 - waveOff * 2 - intp * 2 + i * 2 + tx
			
		tmpt = tmpt + 1
			--y
		vetx[tmpt] = ty + offy
		tmpt = tmpt + 1
			--z
		vetx[tmpt] = tz
		tmpt = tmpt + 1
	end
end

function isDone()
	if (currentFrame > maxFrame) then
		return 1
	end;
	return 0
end

function calcRadius(para)
	para = math.abs(para)
	local tk1 = math.floor(para / 100)
	local tk2 = math.floor(math.fmod(tk1, 2))
	local tk3 = math.fmod(para, 100)
	if (tk2 == 0) then
		return math.sqrt(math.sqrt(tk3 / 100));
	elseif (tk2 == 1) then
		return 1 - math.sqrt(math.sqrt(tk3 / 100));
	end
end
