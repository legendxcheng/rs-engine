#pragma once

#include <vector>
class RenderObject;

class RenderObjectManager
{
public:

	~RenderObjectManager(void);
	
	void InsertRenderObject(RenderObject* rob);
	void Render();
	void Initialize();
	void Shutdown();
	void RemoveRenderObject(RenderObject* rob);

	static RenderObjectManager* GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new RenderObjectManager();
		}
		return m_instance;
	}

private:
	RenderObjectManager(void);

private:
	std::vector<RenderObject*> m_renderObjList;
	static RenderObjectManager* m_instance;

};

