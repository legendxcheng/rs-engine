#include "BulletStorm.h"
#include "BulletStrip.h"
#include "Structures.h"

BulletStorm::BulletStorm(void)
{
}


BulletStorm::~BulletStorm(void)
{
}

void BulletStorm::GetVertexes(void* dest)
{
	memcpy(dest, m_vertexList, sizeof(VertexType) * m_vertexCount);
}

void BulletStorm::GetLines(void* dest)
{
	memcpy(dest, m_lineList, sizeof(std::pair<unsigned int, unsigned int>) * m_lineCount);
}

// release all the resources
void BulletStorm::ShutDown()
{
	for (std::vector<BulletStrip*>::iterator iter = m_stripList.begin(); iter != m_stripList.end(); ++iter)
	{
		(*iter)->ShutDown();
		delete (*iter);
	}
	m_stripList.clear();

}

void BulletStorm::UpdateInterpolation(float delta)
{

}

void BulletStorm::UpdateFrame()
{

}