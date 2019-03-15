#pragma once
#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

#include "utils.h"
#include "camera.h"

class CCameraManager
{
public:
	~CCameraManager();

	void init();
	//Creates a new cam and returns the index
	int AddNewCam();

	void SetCam(int _i) { m_iCurrentCam = _i; }

	CCamera* GetCam(int _iIndex);
	CCamera* GetCam();

	CCamera* GetOrthoCam();

	static CCameraManager& GetInstance();
	static void DestroyInstance();
protected:
	static CCameraManager* s_pCameraManager;
private:
	CCameraManager(bool _createStarterCam = true);
	CCameraManager(const CCameraManager& _kr) = delete;
	CCameraManager& operator= (const CCameraManager& _kr) = delete;

	int m_iCurrentCam;

	std::vector<CCamera*> m_pCameras;
	CCamera* orthoCam;
};
#endif