#include "game.h"

enum GravSet
{
	GRAVUP,
	GRAVNONE,
	GRAVDOWN
};

CGame::CGame()
{
	Init();
}

void CGame::Init()
{
	b2Vec2 gravity(0.0f, -200.0f);


	m_world = new b2World(gravity);
	m_listener = new CB2DListener();
	m_world->SetContactListener(m_listener);


	b2FixtureDef fixtureDef;

	CBox2DObject* groundObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/groundobj.jpg", { 50.0f, -5.0f }, { 50.0f, 10.0f });
	CBox2DObject* leftObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { -1.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 51.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 101.0f, 50.0f }, { 1.0f, 100.0f });

	m_boundsObjects.push_back(groundObj);
	m_boundsObjects.push_back(leftObj);
	m_boundsObjects.push_back(topObj);
	m_boundsObjects.push_back(rightObj);


	m_slingShotObjectBack = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotback.png", MESH_2D_SPRITE);
	m_slingShotObjectBack->Translate({ slingFromPoint.x, 12.0f, 0.0f });
	m_slingShotObjectBack->Scale({ 5.0f, 8.0f, 0.0f });

	m_slingShotObjectFront = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotfront.png", MESH_2D_SPRITE);
	m_slingShotObjectFront->Translate({ slingFromPoint.x, 12.0f, 0.0f });
	m_slingShotObjectFront->Scale({ 5.0f, 8.0f, 0.0f });

	m_background = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/BaCKgROUND.png", MESH_2D_SPRITE);
	m_background->Translate({ 50.0f, 25.0f, 0.0f });
	m_background->Scale({ 50.0f, 25.0f, 0.0f });

	b2FixtureDef enviroFixture;
	enviroFixture.density = 30.0f;
	enviroFixture.friction = 0.5f;
	enviroFixture.restitution = 0.5f;

	CBox2DObject* tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 88.0f, 25.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	m_LevelObjects.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 72.0f, 25.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	m_LevelObjects.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 12.5f }, { 1.5f, 7.0f });
	tempObj->SetHealth(3);
	m_LevelObjects.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 21.0f }, { 10.0f, 1.0f });
	tempObj->SetHealth(3);
	m_LevelObjects.push_back(tempObj);
	tempObj = nullptr;

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 50.0f;
	thrownObjfixtureDef.friction = 0.1f;
	thrownObjfixtureDef.restitution = 0.7f;
	ThrownObj = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", slingFromPoint, { 2.0f, 2.0f });
	ThrownObj->GetBody()->SetActive(false);
}

void CGame::Process()
{
	for (auto&& x : m_boundsObjects)
	{
		x->Process();
	}

	for (auto&& x : m_LevelObjects)
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
		if ((distancefromsling <= 25.0f) && //Being dragged
			CInput::GetInstance().GetMouseState(0) == INPUT_HOLD &&
			dragging)
		{
			ThrownObj->SetPos({GetMouse().x, GetMouse().y});
		}
		else if ((distancefromsling <= 25.0f) && //Being fired
			dragging)
		{
			dragging = false;
			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f}, { slingFromPoint.x, slingFromPoint.y, 0.0f }, 2500.0f);
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

	if (CInput::GetInstance().GetKeyState('r') == INPUT_HOLD)
	{
		ThrownObj->GetBody()->SetTransform(slingFromPoint, 0.0f);
		ThrownObj->GetBody()->SetActive(false);
		fired = false;
	}

	static GravSet currentGrav = GRAVDOWN;
	
	if (CInput::GetInstance().GetKeyState('t') == INPUT_HOLD && currentGrav != GRAVUP)
	{
		m_world->SetGravity({ 0.0f, 200.0f });
		currentGrav = GRAVUP;
	}
	else if (CInput::GetInstance().GetKeyState('g') == INPUT_HOLD && currentGrav != GRAVNONE)
	{
		m_world->SetGravity({ 0.0f, 0.0f });
		currentGrav = GRAVNONE;
	}
	else if (CInput::GetInstance().GetKeyState('b') == INPUT_HOLD && currentGrav != GRAVDOWN)
	{
		m_world->SetGravity({ 0.0f, -200.0f });
		currentGrav = GRAVDOWN;
	}
	
	if (CInput::GetInstance().GetKeyState('|')  == INPUT_HOLD)
	{
		b2Vec2 vel = ThrownObj->GetBody()->GetLinearVelocity();
		glm::vec3 vel3 = { vel.x, vel.y, 0.0f };
		std::cout << glm::length(vel3) << std::endl;
	}
	ThrownObj->Process();
	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world->Step(timeStep, velocityIterations, positionIterations);
}

void CGame::Render()
{
	m_background->Render(CCameraManager::GetInstance().GetOrthoCam());

	m_slingShotObjectBack->Render(CCameraManager::GetInstance().GetOrthoCam());

	for (CBox2DObject* x: m_boundsObjects)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}

	for (CBox2DObject* x : m_LevelObjects)
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

void CGame::ProcessCollisions(b2Contact* _contact)
{
	void * userDataA = _contact->GetFixtureA()->GetBody()->GetUserData();
	void * userDataB = _contact->GetFixtureB()->GetBody()->GetUserData();

	CBox2DObject* objA = static_cast<CBox2DObject*>(userDataA);
	CBox2DObject* objB = static_cast<CBox2DObject*>(userDataB);


}
