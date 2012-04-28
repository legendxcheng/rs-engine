#pragma once
class Spaceship
{
public:
	Spaceship(void);
	~Spaceship(void);

private:
	float x, y, z;// coordination
	float rx, ry, rz;// rotation
	float sx, sy, sz;// scale
};

