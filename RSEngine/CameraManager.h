#pragma once
#include <vector>
class CameraClass;
class CameraManager
{
public:
	CameraManager(void);
	~CameraManager(void);

private:
	std::vector<CameraClass*> m_cameraList;
};

