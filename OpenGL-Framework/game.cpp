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
	b2Vec2 gravity(0.0f, -300.0f);

	m_audio = new CAudioManager();
	m_audio->Init();

	m_audio->LoadAudio("Resources/SoundFiles/bird.wav", "bird_sound", FMOD_DEFAULT);
	m_audio->LoadAudio("Resources/SoundFiles/pigsplat.mp3", "pig_sound", FMOD_DEFAULT);

	m_world = new b2World(gravity);
	m_listener = new CB2DListener();
	m_world->SetContactListener(m_listener);

	m_CurrentBird = 0;

	b2FixtureDef fixtureDef;

	CBox2DObject* groundObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/groundobj.jpg", { 50.0f, -5.0f }, { 50.0f, 10.0f });
	CBox2DObject* leftObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { -1.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 51.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 101.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* barrierObj = new CBox2DObject(m_world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 6.0f }, { 2.0f, 2.0f });
	barrierObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	m_boundsObjects.push_back(groundObj);
	m_boundsObjects.push_back(leftObj);
	m_boundsObjects.push_back(topObj);
	m_boundsObjects.push_back(rightObj);
	m_boundsObjects.push_back(barrierObj);


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
	enviroFixture.restitution = 0.0f;

	Lvl levelOne;

	b2RevoluteJointDef revoluteJointDef; //Weldjoint
	revoluteJointDef.collideConnected = false;
	
	//Right box
	CBox2DObject* tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 90.0f, 20.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	//Left box
	enviroFixture.density = 70.0f;
	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 70.0f, 20.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	//Pillar box
	enviroFixture.density = 30.0f;
	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 10.0f }, { 1.5f, 7.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	revoluteJointDef.bodyA = tempObj->GetBody();
	revoluteJointDef.localAnchorA.Set(0, 5);
	levelOne.objects.push_back(tempObj);

	tempObj = nullptr;
	 
	//Platform Box
	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 17.5f }, { 15.0f, 1.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	
	revoluteJointDef.bodyB = tempObj->GetBody();
	revoluteJointDef.localAnchorB.Set(0, 0);

	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	levelOne.joints.push_back(m_world->CreateJoint(&revoluteJointDef));

	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 90.0f, 9.0f }, { 1.5f, 5.5f });
	tempObj->SetHealth(2);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);

	tempObj = new CBox2DObject(m_world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 70.0f, 9.0f }, { 1.5f, 5.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);

	


	b2FixtureDef PigObjfixtureDef;
	PigObjfixtureDef.density = 90.0f;
	PigObjfixtureDef.friction = 0.7f;
	PigObjfixtureDef.restitution = 0.1f;

	CBox2DObject* PigObj = new CBox2DObject(m_world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", {86.0f, 19.0f}, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(m_world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 74.0f, 19.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(m_world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 80.0f, 20.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr; 

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 80.0f;
	thrownObjfixtureDef.friction = 1.0f;
	thrownObjfixtureDef.restitution = 0.2f;

	CBox2DObject* bird = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", slingFromPoint, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(NORMAL);
	levelOne.birds.push_back(bird);

	bird = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", {16.0f, 6.5f}, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPLITTER);
	levelOne.birds.push_back(bird);

	bird = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", { 12.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPEEDER);
	levelOne.birds.push_back(bird);

	m_levels.push_back(levelOne);

}

void CGame::Process(int levelNum)
{

	for (auto&& x : m_boundsObjects)
	{
		x->Process();
	}

	for (auto&& x : m_levels[levelNum].objects)
	{
		x->Process();
	}
	for (auto&& x : m_levels[levelNum].enemies)
	{
		x->Process();
	}
	for (auto&& x : m_levels[levelNum].birds)
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
			m_levels[levelNum].birds[m_CurrentBird]->SetPos({GetMouse().x, GetMouse().y});
		}
		else if ((distancefromsling <= 25.0f) && //Being fired
			dragging)
		{
			dragging = false;
			for (auto&& x : m_levels[levelNum].enemies)
			{
				x->GetBody()->SetActive(true);
			}

			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f}, { slingFromPoint.x, slingFromPoint.y, 0.0f }, 2000.0f);
			m_levels[levelNum].birds[m_CurrentBird]->GetBody()->SetActive(true);
			m_levels[levelNum].birds[m_CurrentBird]->GetBody()->ApplyLinearImpulse(slingForce, m_levels[levelNum].birds[m_CurrentBird]->GetPos(), true);

			m_audio->PlayAudio("bird_sound");
			fired = true;
		}
		else //Sling snapped
		{
			m_levels[levelNum].birds[m_CurrentBird]->SetPos(slingFromPoint);
			dragging = false;
		}
	}
	else
	{
		static bool birdAbility = false;
		b2Vec2 vel = m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity();
		glm::vec3 vel3 = { vel.x, vel.y, 0.0f };
		float speed = glm::length(vel3);

		if (speed < 10.0f && m_CurrentBird < m_levels[levelNum].birds.size() - 1)
		{
			m_CurrentBird++;

			while (m_levels[levelNum].birds[m_CurrentBird]->GetBirdType() == MINI_SPLITTER)
			{
				m_CurrentBird++;
			}

			m_levels[levelNum].birds[m_CurrentBird]->SetPos(slingFromPoint);
			fired = false;
			birdAbility = false;
		}

		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !birdAbility && m_levels[levelNum].birds[m_CurrentBird]->GetBirdType() == SPEEDER)
		{
			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f }, { m_levels[levelNum].birds[m_CurrentBird]->GetPos().x, m_levels[levelNum].birds[m_CurrentBird]->GetPos().y, 0.0f }, 3000.0f);
			m_levels[levelNum].birds[m_CurrentBird]->GetBody()->ApplyLinearImpulse(-slingForce, m_levels[levelNum].birds[m_CurrentBird]->GetPos(), true);


			birdAbility = true;
		}
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !birdAbility && m_levels[levelNum].birds[m_CurrentBird]->GetBirdType() == SPLITTER)
		{
			birdAbility = true;

			b2FixtureDef thrownObjfixtureDef;
			thrownObjfixtureDef.density = 50.0f;
			thrownObjfixtureDef.friction = 0.7f;
			thrownObjfixtureDef.restitution = 0.2f;

			b2Vec2 pos = m_levels[levelNum].birds[m_CurrentBird]->GetPos();
			CBox2DObject* bird1 = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", { pos.x, pos.y + 5.0f }, { 1.5f, 1.5f });
			bird1->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird1->SetHealth(999);
			bird1->SetBirdType(MINI_SPLITTER);

			CBox2DObject* bird2 = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", { pos.x, pos.y }, { 1.5f, 1.5f });
			bird2->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird2->SetHealth(999);
			bird2->SetBirdType(MINI_SPLITTER);
			CBox2DObject* bird3 = new CBox2DObject(m_world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", { pos.x, pos.y - 5.0f }, { 1.5f, 1.5f });
			bird3->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird3->SetHealth(999);
			bird3->SetBirdType(MINI_SPLITTER);

			delete m_levels[levelNum].birds[m_CurrentBird];
			m_levels[levelNum].birds[m_CurrentBird] = nullptr;
			m_levels[levelNum].birds.erase(m_levels[levelNum].birds.begin() + m_CurrentBird);

			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird1);
			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird2);
			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird3);
		}
	}

	for (int i = 0; i < m_levels[levelNum].objects.size(); i++)
	{
		if (m_levels[levelNum].objects[i]->GetHealth() <= 0)
		{
			delete m_levels[levelNum].objects[i];
			m_levels[levelNum].objects[i] = nullptr;
			m_levels[levelNum].objects.erase(m_levels[levelNum].objects.begin() + i);
		}
	}

	for (auto & object : m_levels[levelNum].objects)
	{
		if (object->GetHealth() < 2)
		{
			object->ChangeTexture({ 0.5f, 0.0f }, { 0.5f, 1.0f });
		}
	}
	for (int i = 0; i < m_levels[levelNum].enemies.size(); i++)
	{
		if (m_levels[levelNum].enemies[i]->GetHealth() <= 0)
		{
			delete m_levels[levelNum].enemies[i];
			m_levels[levelNum].enemies[i] = nullptr;
			m_levels[levelNum].enemies.erase(m_levels[levelNum].enemies.begin() + i);
			m_audio->PlayAudio("pig_sound");
		}
	}

	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world->Step(timeStep, velocityIterations, positionIterations);
}

void CGame::Render(int levelNum)
{
	m_background->Render(CCameraManager::GetInstance().GetOrthoCam());

	m_slingShotObjectBack->Render(CCameraManager::GetInstance().GetOrthoCam());
	for (CBox2DObject* x: m_boundsObjects)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}

	for (CBox2DObject* x : m_levels[levelNum].objects)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}
	for (CBox2DObject* x : m_levels[levelNum].enemies)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}
	for (CBox2DObject* x : m_levels[levelNum].birds)
	{
		x->Render(CCameraManager::GetInstance().GetOrthoCam());
	}

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
