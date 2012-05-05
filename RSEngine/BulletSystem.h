#pragma once

class BulletStorm;
#include <vector>

class BulletSystem
{
public:
	BulletSystem(void);
	~BulletSystem(void);

	void Initialize();// clear m_bulletStorms
	void ShutDown();
	void InsertBulletStorm(BulletStorm* bs);
	void UpdateFrame();
	void UpdateInterpolate(float interpoloate);
	//TODO
	// a function to fill all the vertexes in a render object
	bool IsCollided(float cameraAngle, float shipx, float shipy, float shipz);
	bool FillVertexBuffer(void* vb);
private:
	std::vector<BulletStorm*> m_bulletStorms;
};

