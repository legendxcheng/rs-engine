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
	vetxCount[1] = 50
end

function updateFrame()
	currentFrame = currentFrame + 1
	local tmpt = 1
	for i=1, 50 do
		--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
		vetx[tmpt] = 100 * math.sin(currentFrame - i)
		tmpt = tmpt + 1
		vetx[tmpt] = 100 * math.cos(currentFrame - i)
		tmpt = tmpt + 1
		vetx[tmpt] = - currentFrame + i
		tmpt = tmpt + 1
	end
end

function updateInterpolation(intp)
	--vetx = {} -- empty array
	local tmpt = 1
	for i=1, 50 do
		--vetx[(i - 1) * 3 + 1] = math.sin(currentFrame - i)
		vetx[tmpt] = 100 * math.sin(currentFrame - i + intp)
		tmpt = tmpt + 1
		vetx[tmpt] = 100 * math.cos(currentFrame - i + intp)
		tmpt = tmpt + 1
		vetx[tmpt] = - currentFrame + i + intp
		tmpt = tmpt + 1
	end
end

function isDone()
	if (currentFrame > maxFrame) then
		return 1
	end;
	return 0
end