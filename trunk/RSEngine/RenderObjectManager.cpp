#include "RenderObjectManager.h"
#include "RenderObject.h"

RenderObjectManager::RenderObjectManager(void)
{
}


RenderObjectManager::~RenderObjectManager(void)
{
}

void RenderObjectManager::Render()
{
	for (std::vector<RenderObject*>::iterator iter = this->m_renderObjList.begin(); iter != this->m_renderObjList.end(); ++iter)
	{
		RenderObject* rob = *iter;
		if (rob->IsVisible())
		{
			rob->Render();
		}
	}
}

void RenderObjectManager::Initialize()
{
	this->m_renderObjList.clear();
}

void RenderObjectManager::Shutdown()
{
	for (std::vector<RenderObject*>::iterator iter = this->m_renderObjList.begin(); iter != this->m_renderObjList.end(); ++iter)
	{
		RenderObject* rob = *iter;
		rob->Shutdown();
	}
	this->m_renderObjList.clear();
}

void RenderObjectManager::InsertRenderObject(RenderObject* rob)
{
	this->m_renderObjList.push_back(rob);
}


void RenderObjectManager::RemoveRenderObject(RenderObject* rob)
{
	for (std::vector<RenderObject*>::iterator iter = this->m_renderObjList.begin(); iter != this->m_renderObjList.end(); ++iter)
	{
		if (rob == *iter)
		{
			this->m_renderObjList.erase(iter);
			return;
		}
	}
}

