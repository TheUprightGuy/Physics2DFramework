#include "SceneManager.h"

CSceneManager* CSceneManager::s_pSceneManager = nullptr;

CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
}

CSceneManager& CSceneManager::GetInstance()
{
	if (s_pSceneManager == nullptr)
	{
		s_pSceneManager = new CSceneManager();
	}

	return(*s_pSceneManager);
}

void CSceneManager::DestroyInstance()
{
	delete s_pSceneManager;
	s_pSceneManager = nullptr;
}

void CSceneManager::Init()
{
	m_program = CProgrammerManager::GetInstance().GetProgram(DEFAULT);

	m_MainGame = new CGame();
	m_MainGame->Init();

	m_menuType = PAUSED;
	gamePlaying = false;
	m_bLevelSelect = false;
	m_iLevel = 0;
	m_bPaused = false;
	m_bWinner = 0;

	/*Main Menu*/
	/********************************************************************************/
	m_background = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/BaCKgROUND.png", MESH_2D_SPRITE);
	m_background->Translate({ 50.0f, 25.0f, 0.0f });
	m_background->Scale({ 50.0f, 25.0f, 0.0f });

	m_title = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/Title.png", MESH_2D_SPRITE);
	m_title->Translate({ 70.0f, 25.0f, 0.0f });
	m_title->Scale({ 22.0f, 18.0f, 0.0f });

	CObject* tempObj = new CObject(m_program, "Resources/green_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 20.0f, 40.0f, 0.0f });
	tempObj->Scale({ 15.0f, 5.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_button_credits.png", MESH_2D_SPRITE);
	tempObj->Translate({ 20.0f, 25.0f, 0.0f });
	tempObj->Scale({ 15.0f, 5.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/red_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 20.0f, 10.0f, 0.0f });
	tempObj->Scale({ 15.0f, 5.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;
	/********************************************************************************/
	/*Levels Select*/
	/********************************************************************************/
	tempObj = new CObject(m_program, "Resources/green_panel_lvl1.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_panel_lvl2.png", MESH_2D_SPRITE);
	tempObj->Translate({ 70.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_panel_lvl3.png", MESH_2D_SPRITE);
	tempObj->Translate({ 90.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
	tempObj = nullptr;
	/********************************************************************************/

	m_BackPanel  = new CObject(m_program, "Resources/panel.png", MESH_2D_SPRITE);
	m_BackPanel->Translate({ 50.0f, 25.0f, 0.0f });
	m_BackPanel->Scale({ 17.0f, 21.0f, 0.0f });

	/*Mid Game Menus*/
	/********************************************************************************/ //Pause

	tempObj = new CObject(m_program, "Resources/green_button_resume.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 28.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_pausemenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_button_return.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 20.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_pausemenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/red_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 12.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_pausemenu.push_back(tempObj);
	tempObj = nullptr;

	/*Mid Game Menus*/
	/********************************************************************************/ //Win Menu
	m_pigs = new CObject(m_program, "Resources/pig.png", MESH_2D_SPRITE);
	m_pigs->Translate({ 50.0f, 38.0f, 0.0f });
	m_pigs->Scale({ 5.0f, 5.0f, 0.0f });


	tempObj = new CObject(m_program, "Resources/green_button_next.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 28.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_winmenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_button_return.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 20.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_winmenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/red_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 12.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_winmenu.push_back(tempObj);
	tempObj = nullptr;

	/*Mid Game Menus*/
	/********************************************************************************/ //Lose Menu
	m_birds = new CObject(m_program, "Resources/bird.png", MESH_2D_SPRITE);
	m_birds->Translate({ 50.0f, 38.0f, 0.0f });
	m_birds->Scale({ 5.0f, 5.0f, 0.0f });

	tempObj = new CObject(m_program, "Resources/green_button_retry.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 28.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_losemenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/green_button_return.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 20.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_losemenu.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CObject(m_program, "Resources/red_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 12.0f, 0.0f });
	tempObj->Scale({ 14.0f, 3.5f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_losemenu.push_back(tempObj);
	tempObj = nullptr;
}

void CSceneManager::Render()
{
	m_background->Render(CCameraManager::GetInstance().GetOrthoCam());

	if (gamePlaying)
	{
		m_MainGame->Render(m_iLevel);
		if (m_bPaused)
		{
			m_BackPanel->Render(CCameraManager::GetInstance().GetOrthoCam());
			switch (m_menuType)
			{
			case PAUSED:
				
				for (CObject* x : m_pausemenu)
				{
					x->Render(CCameraManager::GetInstance().GetOrthoCam());
				}
				break;
			case WINNER:
				m_birds->Render(CCameraManager::GetInstance().GetOrthoCam());
				for (CObject* x : m_winmenu)
				{
					x->Render(CCameraManager::GetInstance().GetOrthoCam());
				}
				break;
			case LOSER:
				m_pigs->Render(CCameraManager::GetInstance().GetOrthoCam());
				for (CObject* x : m_losemenu)
				{
					
					x->Render(CCameraManager::GetInstance().GetOrthoCam());
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		int iCount = 0;

		if (!m_bLevelSelect)
		{
			m_title->Render(CCameraManager::GetInstance().GetOrthoCam());
		}

		for (CObject* x : m_menu)
		{
			if (iCount < 3)
			{
				x->Render(CCameraManager::GetInstance().GetOrthoCam());
			}
			else if (m_bLevelSelect)
			{
				x->Render(CCameraManager::GetInstance().GetOrthoCam());
			}

			iCount++;
		}
	}
}

void CSceneManager::Process()
{

	if (gamePlaying)
	{	
		if (m_bPaused)
		{
			int iCount = 0;
			bool bSelected = false;
			bSelected = false;

			switch (m_menuType)
			{
			case PAUSED:
			{
				//Menu Things
				/**************************************************/
				for (CObject* i : m_pausemenu)
				{
					float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
					float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

					float fMouseX = CInput::GetInstance().GetMousePos().x / (fWidth / 100);
					float fMouseY = CInput::GetInstance().GetMousePos().y / (fHeight / 50);

					fMouseY = 50 - fMouseY;

					if ((i->GetPos().x + i->GetScale().x > fMouseX) &&
						(i->GetPos().x - i->GetScale().x < fMouseX) &&
						(i->GetPos().y + i->GetScale().y > fMouseY) &&
						(i->GetPos().y - i->GetScale().y < fMouseY))
					{
						m_iCurrentSelected = iCount;
						bSelected = true;
					}

					iCount++;
				}

				if (!bSelected)
				{
					for (CObject* x : m_pausemenu)
					{
						x->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
					}
				}
				else
				{
					m_pausemenu[m_iCurrentSelected]->ChangeTexture({ 0.0f, 0.5f }, { 1.0f, 0.5f });
				}

				break;
			}
			case WINNER:
			{
				//Menu Things
				/**************************************************/
				for (CObject* i : m_winmenu)
				{
					float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
					float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

					float fMouseX = CInput::GetInstance().GetMousePos().x / (fWidth / 100);
					float fMouseY = CInput::GetInstance().GetMousePos().y / (fHeight / 50);

					fMouseY = 50 - fMouseY;

					if ((i->GetPos().x + i->GetScale().x > fMouseX) &&
						(i->GetPos().x - i->GetScale().x < fMouseX) &&
						(i->GetPos().y + i->GetScale().y > fMouseY) &&
						(i->GetPos().y - i->GetScale().y < fMouseY))
					{
						m_iCurrentSelected = iCount;
						bSelected = true;
					}

					iCount++;
				}

				if (!bSelected)
				{
					for (CObject* x : m_winmenu)
					{
						x->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
					}
				}
				else
				{
					m_winmenu[m_iCurrentSelected]->ChangeTexture({ 0.0f, 0.5f }, { 1.0f, 0.5f });
				}

				break;
			}
			case LOSER:
			{
				//Menu Things
				/**************************************************/
				for (CObject* i : m_losemenu)
				{
					float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
					float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

					float fMouseX = CInput::GetInstance().GetMousePos().x / (fWidth / 100);
					float fMouseY = CInput::GetInstance().GetMousePos().y / (fHeight / 50);

					fMouseY = 50 - fMouseY;

					if ((i->GetPos().x + i->GetScale().x > fMouseX) &&
						(i->GetPos().x - i->GetScale().x < fMouseX) &&
						(i->GetPos().y + i->GetScale().y > fMouseY) &&
						(i->GetPos().y - i->GetScale().y < fMouseY))
					{
						m_iCurrentSelected = iCount;
						bSelected = true;
					}

					iCount++;
				}

				if (!bSelected)
				{
					for (CObject* x : m_losemenu)
					{
						x->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
					}
				}
				else
				{
					m_losemenu[m_iCurrentSelected]->ChangeTexture({ 0.0f, 0.5f }, { 1.0f, 0.5f });
				}

				break;
			}
			default:
				break;
			}

			static bool keyHold = false;
			if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && bSelected && !keyHold)
			{
				keyHold = true;
				switch (m_iCurrentSelected)
				{
				case 0:
				{
					if (m_menuType == WINNER)
					{
						m_MainGame->ResetLvl(m_iLevel);
						if (m_iLevel == 2)
						{
							m_iLevel = 0;
						}
						else
						{
							m_iLevel++;
						}
					}
					else if(m_menuType == LOSER)
					{
						m_MainGame->ResetLvl(m_iLevel);
					}

					m_bPaused = false;
					m_menuType = PAUSED;
					break;
				}
				case 1:
				{
					gamePlaying = false;
					m_MainGame->ResetLvl(m_iLevel);
					m_bPaused = false;
					break;
				}
				case 2:
				{
					glutLeaveMainLoop();
					break;
				}
				default:
					break;
				}
			}

			if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE)
			{
				keyHold = false;
			}

		}
		else if (m_MainGame->Process(m_iLevel))
		{
			m_menuType = (m_MainGame->GetWinner()) ? LOSER : WINNER;
			m_bPaused = true;
		
		}

		static bool esckeyHold = false;
		if (CInput::GetInstance().GetKeyState(27) == INPUT_RELEASE)
		{
			esckeyHold = false;
		}
		if (CInput::GetInstance().GetKeyState(27) == INPUT_HOLD && !esckeyHold && (m_menuType == PAUSED))
		{
			m_bPaused = !m_bPaused;
			m_menuType == PAUSED;
			esckeyHold = true;
		}
	}

	else
	{
		int iCount = 0;
		bool bSelected = false;
		for (CObject* i : m_menu)
		{
			float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
			float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

			float fMouseX = CInput::GetInstance().GetMousePos().x / (fWidth / 100);
			float fMouseY = CInput::GetInstance().GetMousePos().y / (fHeight / 50);

			fMouseY = 50 - fMouseY;

			if ((i->GetPos().x + i->GetScale().x > fMouseX) && 
				(i->GetPos().x - i->GetScale().x < fMouseX) &&
				(i->GetPos().y + i->GetScale().y > fMouseY) &&
				(i->GetPos().y - i->GetScale().y < fMouseY))
			{
				m_iCurrentSelected = iCount;
				bSelected = true;
			}

			iCount++;
		}

		if (!bSelected)
		{
			for (CObject* x : m_menu)
			{
				x->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
			}
		}
		else
		{
			m_menu[m_iCurrentSelected]->ChangeTexture({ 0.0f, 0.5f }, { 1.0f, 0.5f });
		}

		static bool keyHold = false;
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && bSelected && !keyHold)
		{
			keyHold = true;
			switch (m_iCurrentSelected)
			{
			case 0:
			{
				m_bLevelSelect = !m_bLevelSelect;
				break;
			}
			case 1:
			{
				break;
			}
			case 2:
			{
				glutLeaveMainLoop();
				break;
			}
			case 3:
			{
				if (m_bLevelSelect)
				{
					m_iLevel = 0;
					gamePlaying = true;
					break;
				}
				
			}
			case 4:
			{
				if (m_bLevelSelect)
				{
					m_iLevel = 1;
					gamePlaying = true;
					break;
				}
				
			}
			case 5:
			{
				if (m_bLevelSelect)
				{
					m_iLevel = 2;
					gamePlaying = true;
					break;
				}
				
			}
			default:
				break;
			}
		}

		if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE)
		{
			keyHold = false;
		}

		

	}

}


