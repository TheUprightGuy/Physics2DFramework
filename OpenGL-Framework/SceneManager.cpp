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

	m_pCamera = new CCamera(true);

	b2Vec2 gravity(0.0f, -200.0f);
	world = new b2World(gravity);


	b2FixtureDef fixtureDef; 
	//fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	//body->CreateFixture(&fixtureDef);

	PhysicsObject = new CBox2DObject(world, BOX, fixtureDef, true, { 15.0f, 15.0f }, { 2.0f, 2.0f });
	PhysicsObject->GetBody()->SetAwake(false);
	GroundPhysicsObject = new CBox2DObject(world, BOX, fixtureDef, false, { 50.0f, 0.0f }, { 100.0f, 1.0f });;

}

void CSceneManager::Render()
{
	GroundPhysicsObject->Render(CCameraManager::GetInstance().GetOrthoCam());
	PhysicsObject->Render(CCameraManager::GetInstance().GetOrthoCam());
}

void CSceneManager::Process()
{
	PhysicsObject->Process();
	GroundPhysicsObject->Process();

	glm::vec3 mousePoint = CInput::GetInstance().GetMousePos();

	float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

	mousePoint.x = mousePoint.x / ( fWidth / 100);
	mousePoint.y = mousePoint.y / (fHeight / 100);
	mousePoint.y = 100 - mousePoint.y; // :)

	const glm::vec3 slingPoint = { 15.0f, 15.0f ,0.0f };

	static bool fire = false;

	if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD)
	{
		PhysicsObject->GetBody()->SetAwake(true);
		PhysicsObject->SetPos({ slingPoint.x, slingPoint.y });
		fire = true;
	}

	glm::vec3 forceApplied;;
	glm::vec3 directiontoObject;
	float distance = 0.0f;

	distance = glm::distance(mousePoint, slingPoint);
	directiontoObject = slingPoint - mousePoint;
	glm::vec3 direction = glm::normalize(directiontoObject);

	float fForce = (200.0f * distance);
	forceApplied = direction * fForce;


	if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE && fire /*&& distance > 0.5f*/ && (directiontoObject.x &&  directiontoObject.y > 0.0f))
	{
		PhysicsObject->GetBody()->ApplyLinearImpulse({ forceApplied.x, forceApplied.y}, PhysicsObject->GetBody()->GetPosition(), true);
		fire = false;
	}



	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);

}


