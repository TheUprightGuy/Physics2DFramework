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
#include "game.h"

struct Scene
{
	int iSceneID;
	std::vector<CObject*> Sprites;
	std::vector<TextLabel*> Texts;
	CAudioManager* AudioManager;
};

enum MENUTYPE
{
	PAUSED,
	LOSER,
	WINNER
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

	std::vector<CObject*> m_menu;
	std::vector<CObject*> m_pausemenu;
	std::vector<CObject*> m_winmenu;
	std::vector<CObject*> m_losemenu;

	bool gamePlaying;
	bool m_bPaused;
	bool m_bGameOver;

	bool m_bWinner;
	bool m_bLevelSelect;

	int m_iCurrentSelected;
	int m_iLevel;
	
	MENUTYPE m_menuType;
	CObject * m_background;
	CObject * m_title;

	CObject * m_RedPanel;
	CObject * m_BackPanel;

	CObject * m_birds;
	CObject * m_pigs;

	CGame * m_MainGame;
	//Global input
	CInput* m_pInput;

	//Global Camera
	CCamera* m_pCamera;

};

#endif // !__SCENEMANAGER_H__

