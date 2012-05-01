#pragma once

#include <vector>
//#include "Structures.h"
class BulletStrip;
struct VertexType;
class BulletStorm
{
public:
	BulletStorm(void);
	~BulletStorm(void);

public:
	void GetVertexes(void* dest);
	void GetLines(void* dest);
	//load .lua file and initialize the bullet storm
	void LoadBulletStorm(char* fileName);
	virtual void UpdateFrame();
	virtual void UpdateInterpolation(float delta);
	void ShutDown();

protected:
	unsigned int m_frameCount;
	unsigned int m_vertexCount;
	unsigned int m_lineCount;

	VertexType* m_vertexList;
	unsigned int m_stripCount;// number of bullet strip
	std::vector<BulletStrip*> m_stripList;
	std::pair<unsigned int, unsigned int>* m_lineList;

};

