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
	maxFrame = 800 -- max frame count, if current frame is bigger than maxFrame, then the bulletstorm will be removed from system
	lineCount = 0 -- line count
	line = {} -- stotre line index in vetx
	lineUpdated = 0 -- 0 for not updated since last call 1 for updated since last call
	stripCount = 1
	vetxCount[1] = 400
end

function updateFrame()
	currentFrame = currentFrame + 1
	local tmpt = 1
	for i=1, 400 do
		--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
		--x

		vetx[tmpt] = 400 - currentFrame + i * 2
		local rr = calcRadius(vetx[tmpt] / 2 + currentFrame)
		tmpt = tmpt + 1
		--y
		vetx[tmpt] = rr * 300 * math.sin(currentFrame / 200 - i / 5)
		tmpt = tmpt + 1
		--z
		vetx[tmpt] = rr * 300 * math.cos(currentFrame / 200 - i / 5)
		tmpt = tmpt + 1

	end
end

function updateInterpolation(intp)
	--vetx = {} -- empty array
	local tmpt = 1
	for i=1, 400 do
			--x
		vetx[tmpt] = 400 - currentFrame - intp + i * 2
		local rr = calcRadius(vetx[tmpt] / 2 + currentFrame)
		tmpt = tmpt + 1
		--y
		vetx[tmpt] = rr * 300 * math.sin((currentFrame + intp)/ 200 - i / 5)
		tmpt = tmpt + 1
		--z
		vetx[tmpt] = rr * 300 * math.cos((currentFrame + intp)/ 200 - i / 5)
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
	local tk1 = math.floor(para / 200)
	local tk2 = math.floor(math.fmod(tk1, 2))
	local tk3 = math.fmod(para, 200)
	if (tk2 == 0) then
		return math.sqrt(math.sqrt(tk3 / 200));
	elseif (tk2 == 1) then
		return 1 - math.sqrt(math.sqrt(tk3 / 200));
	end
end
