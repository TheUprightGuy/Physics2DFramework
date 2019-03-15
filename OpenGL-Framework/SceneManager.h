#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include <map>
#include <string.h>

#include "Dependencies/Box2D/Box2D.h"

#include "utils.h"
#include "input.h"
#include "camera.h"
#include "TextLabel.h"
#include "object.h"
#include "AudioManager.h"
#include "ProgramManager.h"
#include "CameraManager.h"
#include "Box2DObject.h"

struct Scene
{
	int iSceneID;
	std::vector<CObject*> Sprites;
	std::vector<TextLabel*> Texts;
	CAudioManager* AudioManager;
};
class CSceneManager
{
public:
	~CSceneManager();

	static CSceneManager& GetInstance();
	static void DestroyInstance();

	//Initalize any scenes in here
	void Init();

	void Render();
	void Process();

protected:
	static CSceneManager* s_pSceneManager;

private:
	CSceneManager();
	CSceneManager(const CSceneManager& _kr) = delete;
	CSceneManager& operator= (const CSceneManager& _kr) = delete;

	//Variables
	GLuint m_program;

	//Global input
	CInput* m_pInput;

	//Global Camera
	CCamera* m_pCamera;

	CObject* mySprite;
	CObject* otherSprite;
	//Playing with physics
	b2World* world;
	b2Body* groundBody;
	b2Body* body;

	CBox2DObject* PhysicsObject;
	CBox2DObject* GroundPhysicsObject;
};

#endif // !__SCENEMANAGER_H__

