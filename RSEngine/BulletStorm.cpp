#include "BulletStorm.h"
#include "Structures.h"


#pragma comment(lib,"lua.lib")

/*
	load lua script
	call lua function
	fetch vertex
	put vertex in vertex buffer (some middle procedure)
*/
BulletStorm::BulletStorm(void)
{
}


BulletStorm::~BulletStorm(void)
{
}

int BulletStorm::GetVertexes(void* dest)
{
	int bytesCopy = 0;
	//memcpy(dest, m_vertexList, sizeof(VertexType) * m_vertexCount);
	for (std::vector<BulletType>::iterator iter = m_vertexList.begin();
			iter != m_vertexList.end(); ++iter)
	{
		memcpy(dest, &(*iter), sizeof(BulletType));
		dest = (void*)((char*)dest + sizeof(BulletType));
		bytesCopy += sizeof(BulletType);
	}
	
	return bytesCopy;
}

void BulletStorm::GetLines(void* dest)
{
	//memcpy(dest, m_lineList, sizeof(std::pair<unsigned int, unsigned int>) * m_lineCount);
}

// release all the resources
void BulletStorm::ShutDown()
{
	lua_close(m_luaState);
	//free(m_vertexList);

}

void BulletStorm::UpdateInterpolation(float delta)
{
	lua_getglobal(m_luaState, "updateInterpolation");
	lua_pushnumber(m_luaState, delta);
	lua_pcall(m_luaState, 1, 0, 0);
}

void BulletStorm::UpdateFrame()
{
	lua_getglobal(m_luaState, "updateFrame");
	int rett = lua_pcall(m_luaState, 0, 0, 0);
	const char* error = lua_tostring(m_luaState, -1);//��ӡ������

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
	lua_State *L = luaL_newstate();
	m_luaState = L;
	luaL_openlibs(L);
	rett = luaL_loadfile(L, fileName);
	rett = lua_pcall(L, 0, 0, 0);
	lua_getglobal(m_luaState, "initialize");
	rett = lua_pcall(m_luaState, 0, 0, 0);
	const char* error = lua_tostring(L, -1);//��ӡ������
// 	rett = lua_pcall(L, 0, 0, 0);
// 	lua_getglobal(L, "background");
// 	int outputd = (int)GetField(L, "b");
}

float getNumber(lua_State* L, const lua_Number num) 
{
	float result = 0.0f;
	lua_pushnumber(L, num);
	lua_gettable(L, -2);
	result = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return result;
}

void BulletStorm::FetchBullets()
{
	// fetch lines
	lua_getglobal(m_luaState, "lineUpdated");
	int lineUpdated = (int)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState,1);
	if (lineUpdated)
	{
		lua_getglobal(m_luaState, "lineCount");
		m_lineCount = (int)lua_tonumber(m_luaState, -1);
		lua_pop(m_luaState, 1);
		m_lineList.clear();
		lua_getglobal(m_luaState, "line");
		for (int i = 0 ; i < m_lineCount; ++i)
		{
			std::pair<unsigned int, unsigned int> tpair;
			tpair.first = (int)getNumber(m_luaState, i * 2 + 1) - 1;
			tpair.second = (int)getNumber(m_luaState, i * 2 + 2) - 1;
			m_lineList.push_back(tpair);
		}
		lua_pop(m_luaState,1);// pop the table
	}

	// fetch vertexs
	lua_getglobal(m_luaState, "stripCount");
	int stripCount = (int)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState, 1);

	m_vertexList.clear();
	int totId = 1;
	for (int i = 0; i < stripCount; ++i)
	{
		lua_getglobal(m_luaState, "vetxCount");	
		int stripSize = (int)getNumber(m_luaState, i + 1);
		lua_pop(m_luaState, 1);

		lua_getglobal(m_luaState, "vetx");
		int tcount = 0;
		while (tcount < stripSize)
		{
			BulletType tmp;
			tmp.position.x = getNumber(m_luaState, totId);
			++totId;
			tmp.position.y = getNumber(m_luaState, totId);
			++totId;
			tmp.position.z = getNumber(m_luaState, totId);
			++totId;

			m_vertexList.push_back(tmp);

			++tcount;
		}
		lua_pop(m_luaState, 1);// pop the vetx table
	}
}

bool BulletStorm::IsDone()
{
	lua_getglobal(m_luaState, "updateInterpolation");
	lua_pcall(m_luaState, 0, 1, 0);
	int ret = (int)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState, 1);
	if (ret == 0)
		return false;
	return true;
}


bool BulletStorm::IsCollided(float cameraAngle, float shipx, float shipy, float shipz)
{
	return true;
}