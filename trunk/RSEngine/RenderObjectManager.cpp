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
	for (std::vector<RenderObject*>::iterator iter = this->renderObjList.begin(); iter != this->renderObjList.end(); ++iter)
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
	this->renderObjList.clear();
}

void RenderObjectManager::Shutdown()
{
	for (std::vector<RenderObject*>::iterator iter = this->renderObjList.begin(); iter != this->renderObjList.end(); ++iter)
	{
		RenderObject* rob = *iter;
		rob->Shutdown();
	}
	this->renderObjList.clear();
}

void RenderObjectManager::InsertRenderObject(RenderObject* rob)
{
	this->renderObjList.push_back(rob);
}


void RenderObjectManager::RemoveRenderObject(RenderObject* rob)
{
	for (std::vector<RenderObject*>::iterator iter = this->renderObjList.begin(); iter != this->renderObjList.end(); ++iter)
	{
		if (rob == *iter)
		{
			this->renderObjList.erase(iter);
			return;
		}
	}
}

