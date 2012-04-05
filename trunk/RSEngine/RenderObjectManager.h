#pragma once

#include <vector>
class RenderObject;

class RenderObjectManager
{
public:
	RenderObjectManager(void);
	~RenderObjectManager(void);
	
	void InsertRenderObject(RenderObject* rob);
	void Render();
	void Initialize();
	void Shutdown();
	void RemoveRenderObject(RenderObject* rob);


private:
	std::vector<RenderObject*> renderObjList;


};

