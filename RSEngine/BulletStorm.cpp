#include "BulletStorm.h"
#include "BulletStrip.h"
#include "Structures.h"
#include "lua_head.h"

#pragma comment(lib,"lua.lib")


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

float GetField (lua_State* L, const char *key) 
{
	float result = 0.0f;
	lua_pushstring(L, key);
	lua_gettable(L, -2);
	result = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return result;
}

void BulletStorm::LoadBulletStorm(char* fileName)
{
	// now just test lua
	int rett;
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs (L);
	rett = luaL_loadfile(L, fileName);
	rett = lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "background");
	int outputd = (int)GetField(L, "b");
}
