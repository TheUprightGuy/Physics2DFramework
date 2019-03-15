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

	PhysicsObject = new CBox2DObject(world, BOX, fixtureDef, true, { 50.0f, 50.0f }, { 2.0f, 2.0f });
	GroundPhysicsObject = new CBox2DObject(world, BOX, fixtureDef, false, { 50.0f, 0.0f }, { 100.0f, 1.0f });;
}

void CSceneManager::Render()
{
	GroundPhysicsObject->Render(CCameraManager::GetInstance().GetOrthoCam());
	PhysicsObject->Render(CCameraManager::GetInstance().GetOrthoCam());
}

void CSceneManager::Process()
{
	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	PhysicsObject->Process();
	GroundPhysicsObject->Process();

	
	glm::vec3 mousePoint = CInput::GetInstance().GetMousePos();
	static glm::vec3 mouseonPress;

	float fWidth = (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
	float fHeight = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);

	mousePoint.x = mousePoint.x / ( fWidth / 100);
	mousePoint.y = mousePoint.y / (fHeight / 100);
	mousePoint.y = 100 - mousePoint.y; // :)

	glm::vec3 forceApplied;;
	glm::vec3 directiontoObject;
	float distance = 0.0f;
	static bool fire = false;
	static bool setMouse = false;


	if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !setMouse)
	{
		mouseonPress = mousePoint;
		setMouse = true;
	}
	else if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && setMouse)
	{
		PhysicsObject->SetPos({ mouseonPress.x, mouseonPress.y });
		fire = true;
	}

	distance = glm::distance(mousePoint, mouseonPress);
	directiontoObject = mouseonPress - mousePoint;
	if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASE && fire && distance > 0.5f && (directiontoObject.x &&  directiontoObject.y > 0.0f))
	{

		directiontoObject = mouseonPress - mousePoint;
		glm::vec3 direction = glm::normalize(directiontoObject);

		float fForce = (200.0f * distance);
		forceApplied = direction * fForce ;

		PhysicsObject->GetBody()->ApplyLinearImpulse({ forceApplied.x, forceApplied.y}, PhysicsObject->GetBody()->GetPosition(), true);
		fire = false;
		setMouse = false;
	}

	world->Step(timeStep, velocityIterations, positionIterations);

}


