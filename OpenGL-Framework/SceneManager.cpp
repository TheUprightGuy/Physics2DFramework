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

	gamePlaying = false;
	m_bLevelSelect = false;
	m_iLevel = 0;


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

	tempObj = new CObject(m_program, "Resources/green_button_credits.png", MESH_2D_SPRITE);
	tempObj->Translate({ 20.0f, 25.0f, 0.0f });
	tempObj->Scale({ 15.0f, 5.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);

	tempObj = new CObject(m_program, "Resources/red_button.png", MESH_2D_SPRITE);
	tempObj->Translate({ 20.0f, 10.0f, 0.0f });
	tempObj->Scale({ 15.0f, 5.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);

	/*Levels*/
	tempObj = new CObject(m_program, "Resources/green_panel_lvl1.png", MESH_2D_SPRITE);
	tempObj->Translate({ 50.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);

	tempObj = new CObject(m_program, "Resources/green_panel_lvl2.png", MESH_2D_SPRITE);
	tempObj->Translate({ 70.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);

	tempObj = new CObject(m_program, "Resources/green_panel.png", MESH_2D_SPRITE);
	tempObj->Translate({ 90.0f, 25.0f, 0.0f });
	tempObj->Scale({ 9.0f, 12.0f, 0.0f });
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 1.0f, 0.5f });
	m_menu.push_back(tempObj);
}

void CSceneManager::Render()
{
	m_background->Render(CCameraManager::GetInstance().GetOrthoCam());

	if (gamePlaying)
	{
		m_MainGame->Render(m_iLevel);
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
		if (m_MainGame->Process(m_iLevel))
		{
			gamePlaying = false;
			m_MainGame->ResetLvl(m_iLevel);
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
				m_iLevel = 0;
				gamePlaying = true;
				break;
			}
			case 4:
			{
				m_iLevel = 1;
				gamePlaying = true;
				break;
			}
			case 5:
			{
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

}


