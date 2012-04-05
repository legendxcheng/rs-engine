#pragma once
class RenderObject
{
public:
	RenderObject(void);
	~RenderObject(void);

	void SetVisible(bool v);
	bool IsVisible();
	virtual void Shutdown(){};
	virtual void Render(){};// just one call to handle all the render related logic
	virtual void Initialize(){};

protected:
	bool m_visible;
};

