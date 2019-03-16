#include "game.h"

CGame::CGame()
{
	Init();
}

void CGame::Init()
{
	b2Vec2 gravity(0.0f, -200.0f);
	m_world = new b2World(gravity);

	b2FixtureDef fixtureDef;

	CBox2DObject* groundObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/grass.png", { 50.0f, 0.0f }, { 100.0f, 1.0f });
	CBox2DObject* leftObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 0.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 100.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 100.0f, 50.0f }, { 1.0f, 100.0f });

	m_boundsObjects.push_back(groundObj);
	m_boundsObjects.push_back(leftObj);
	m_boundsObjects.push_back(topObj);
	m_boundsObjects.push_back(rightObj);

	m_slingShotObjectBack = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotback.png", MESH_2D_SPRITE);
	m_slingShotObjectBack->Translate({ slingFromPoint.x, 5.0f, 0.0f });
	m_slingShotObjectBack->Scale({ 5.0f, 8.0f, 0.0f });

	m_slingShotObjectFront = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotfront.png", MESH_2D_SPRITE);
	m_slingShotObjectFront->Translate({ slingFromPoint.x, 5.0f, 0.0f });
	m_slingShotObjectFront->Scale({ 5.0f, 8.0f, 0.0f });

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 50.0f;
	thrownObjfixtureDef.friction = 0.5f;
	thrownObjfixtureDef.restitution = 0.5f;
	ThrownObj = new CBox2DObject(m_world, BOX, thrownObjfixtureDef, true, "Resources/FeelsBadMan.png", slingFromPoint, { 2.0f, 2.0f });
	ThrownObj->GetBody()->SetActive(false);

}

void CGame::Process()
{
	for (auto&& x : m_boundsObjects)
	{
		x->Process();
	}

	static bool dragging = false;
	static bool fired = false;

	if (!fired)
	{
		float distancefromsling = (glm::distance(GetMouse(), { slingFromPoint.x, slingFromPoint.y, 0.0f }));
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD &&
			distancefromsling < 2.0f &&
			!dragging)
		{
			dragging = true;
		}
		if ((distancefromsling <= 18.0f) && //Being dragged
			CInput::GetInstance().GetMouseState(0) == INPUT_HOLD &&
			dragging)
		{
			ThrownObj->SetPos({GetMouse().x, GetMouse().y});
		}
		else if ((distancefromsling <= 18.0f) && //Being fired
			dragging)
		{
			dragging = false;
			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f}, { slingFromPoint.x, slingFromPoint.y, 0.0f }, 10000.0f);
			ThrownObj->GetBody()->SetActive(true);
			ThrownObj->GetBody()->ApplyLinearImpulse(slingForce, ThrownObj->GetBody()->GetPosition(), true);
			fired = true;
		}
		else //Sling snapped
		{
			ThrownObj->SetPos(slingFromPoint);
			dragging = false;
		}
	}

	ThrownObj->Process();
	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world->Step(timeStep, velocityIterations, positionIterations);
}

void CGame::Render()
{
	m_slingShotObjectBack->Render(CCameraManager::GetInstance().GetOrthoCam());

	for (CBox2DObject* x: m_boundsObjects)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}

	ThrownObj->Render(CCameraManager::GetInstance().GetOrthoCam());

	m_slingShotObjectFront->Render(CCameraManager::GetInstance().GetOrthoCam());

}

glm::vec3 CGame::GetMouse()
{
	glm::vec3 mousePoint = CInput::GetInstance().GetMousePos();

	float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

	mousePoint.x = mousePoint.x / (fWidth / 100);
	mousePoint.y = mousePoint.y / (fHeight / 50);
	mousePoint.y = 50 - mousePoint.y; // :)

	return mousePoint;
}

b2Vec2 CGame::GetSlingForce(glm::vec3 _pointA, glm::vec3 _pointB, float _springRetension)
{
	glm::vec3 forceApplied;;
	glm::vec3 directiontoObject;
	float distance = 0.0f;

	distance = glm::distance(_pointA, _pointB);
	directiontoObject = _pointB - _pointA;
	glm::vec3 direction = glm::normalize(directiontoObject);

	float fForce = (_springRetension * distance);
	forceApplied = direction * fForce;

	b2Vec2 output = { forceApplied.x, forceApplied.y };
	return(output);
}
