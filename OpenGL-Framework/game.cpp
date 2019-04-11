#include "game.h"

enum GravSet
{
	GRAVUP,
	GRAVNONE,
	GRAVDOWN
};

CGame::CGame()
{
}

void CGame::InitLvl1(b2World * _world)
{
	Lvl levelOne;
	levelOne.world = _world;
	levelOne.listener = new CB2DListener();

	_world->SetContactListener(levelOne.listener);

	b2FixtureDef enviroFixture;
	enviroFixture.density = 30.0f;
	enviroFixture.friction = 0.5f;
	enviroFixture.restitution = 0.0f;

	b2RevoluteJointDef revoluteJointDef; //Revolute Joint
	revoluteJointDef.collideConnected = false;

	//Right box
	CBox2DObject* tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 90.0f, 20.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	//Left box
	enviroFixture.density = 300.0f;
	tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 70.0f, 20.0f }, { 2.0f, 2.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	//Pillar box
	tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 10.0f }, { 1.5f, 7.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	revoluteJointDef.bodyA = tempObj->GetBody();
	revoluteJointDef.localAnchorA.Set(0, 5);
	levelOne.objects.push_back(tempObj);

	tempObj = nullptr;

	//Platform Box
	enviroFixture.density = 30.0f;
	tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 80.0f, 17.5f }, { 15.0f, 1.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	revoluteJointDef.bodyB = tempObj->GetBody();
	revoluteJointDef.localAnchorB.Set(0, 0);

	levelOne.objects.push_back(tempObj);
	tempObj = nullptr;

	levelOne.joints.push_back(levelOne.world->CreateJoint(&revoluteJointDef));

	 //Left Pillar
	tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 70.0f, 9.0f }, { 1.5f, 5.5f });
	tempObj->SetHealth(4);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);

	//Right Pillar
	tempObj = new CBox2DObject(levelOne.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 90.0f, 9.0f }, { 1.5f, 5.5f });
	tempObj->SetHealth(2);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelOne.objects.push_back(tempObj);

	


	b2FixtureDef PigObjfixtureDef;
	PigObjfixtureDef.density = 90.0f;
	PigObjfixtureDef.friction = 0.7f;
	PigObjfixtureDef.restitution = 0.1f;

	CBox2DObject* PigObj = new CBox2DObject(levelOne.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 86.0f, 19.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelOne.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 74.0f, 19.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelOne.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 80.0f, 20.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelOne.enemies.push_back(PigObj);
	PigObj = nullptr;

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 80.0f;
	thrownObjfixtureDef.friction = 1.0f;
	thrownObjfixtureDef.restitution = 0.2f;

	CBox2DObject* bird = new CBox2DObject(levelOne.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", slingFromPoint, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(NORMAL);
	levelOne.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelOne.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { 16.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPLITTER);
	levelOne.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelOne.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird1.png", { 12.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPEEDER);
	levelOne.birds.push_back(bird);
	bird = nullptr;

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 1.0f;

	CBox2DObject* groundObj = new CBox2DObject(levelOne.world, BOX, fixtureDef, false, "Resources/groundobj.jpg", { 50.0f, -5.0f }, { 50.0f, 10.0f });
	CBox2DObject* leftObj = new CBox2DObject(levelOne.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { -1.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(levelOne.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 51.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(levelOne.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 101.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* barrierObj = new CBox2DObject(levelOne.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 6.0f }, { 2.0f, 2.0f });
	barrierObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	levelOne.boundsObjects.push_back(groundObj);
	levelOne.boundsObjects.push_back(leftObj);
	levelOne.boundsObjects.push_back(topObj);
	levelOne.boundsObjects.push_back(rightObj);
	levelOne.boundsObjects.push_back(barrierObj);

	m_levels[0] = levelOne;
}

void CGame::InitLvl2(b2World * _world)
{
	Lvl levelTwo;
	levelTwo.world = _world;
	levelTwo.listener = new CB2DListener();
	_world->SetContactListener(levelTwo.listener);

	b2FixtureDef enviroFixture;
	enviroFixture.density = 30.0f;
	enviroFixture.friction = 0.5f;
	enviroFixture.restitution = 0.0f;

	b2WeldJointDef weldJointDef; //Weld Joint
	weldJointDef.collideConnected = false;
	
	//Platform Box
	CBox2DObject* tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, false, "Resources/boxEmpty.png", { 75.0f, 25.0f }, { 35.0f, 1.0f });
	tempObj->SetHealth(9999);
	tempObj->SetRotation(35);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	weldJointDef.bodyA = tempObj->GetBody();
	weldJointDef.localAnchorA.Set(20, 0);

	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//Wall box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 90.0f, 42.0f }, { 1.0f, 7.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	weldJointDef.bodyB = tempObj->GetBody();
	weldJointDef.localAnchorB.Set(0, -5);
	levelTwo.joints.push_back(levelTwo.world->CreateJoint(&weldJointDef));

	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//top box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, false, "Resources/boxEmpty.png", { 82.0f, 32.0f }, { 5.0f, 1.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//middle box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, false, "Resources/boxEmpty.png", { 68.0f, 23.0f }, { 5.0f, 1.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//bottom box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, false, "Resources/boxEmpty.png", { 55.0f, 15.0f }, { 5.0f, 1.0f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;


	//top box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 78.0f, 34.0f }, { 1.5f, 1.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//middle box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 64.0f, 25.0f }, { 1.5f, 1.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	//bottom box
	tempObj = new CBox2DObject(levelTwo.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 52.0f, 17.0f }, { 1.5f, 1.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	enviroFixture.density = 100.0f;
	tempObj = new CBox2DObject(levelTwo.world, CIRCLE, enviroFixture, true, "Resources/boulder.png", { 93.0f, 45.0f }, { 4.0f, 4.0f });
	tempObj->SetHealth(10);
	levelTwo.objects.push_back(tempObj);
	tempObj = nullptr;

	b2FixtureDef PigObjfixtureDef;
	PigObjfixtureDef.density = 90.0f;
	PigObjfixtureDef.friction = 0.7f;
	PigObjfixtureDef.restitution = 0.1f;

	CBox2DObject* PigObj = new CBox2DObject(levelTwo.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 82.0f, 34.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelTwo.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelTwo.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 68.0f, 25.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelTwo.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelTwo.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 56.0f, 17.0f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	PigObj->GetBody()->SetActive(false);
	levelTwo.enemies.push_back(PigObj);
	PigObj = nullptr;

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 80.0f;
	thrownObjfixtureDef.friction = 1.0f;
	thrownObjfixtureDef.restitution = 0.2f;

	CBox2DObject* bird = new CBox2DObject(levelTwo.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", { 16.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(NORMAL);
	levelTwo.birds.push_back(bird);

	bird = nullptr;
	bird = new CBox2DObject(levelTwo.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { 16.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPLITTER);
	levelTwo.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelTwo.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { 12.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPLITTER);
	levelTwo.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelTwo.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { 8.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPLITTER);
	levelTwo.birds.push_back(bird);
	bird = nullptr;

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 1.0f;
	CBox2DObject* groundObj = new CBox2DObject(levelTwo.world, BOX, fixtureDef, false, "Resources/groundobj.jpg", { 50.0f, -5.0f }, { 50.0f, 10.0f });
	CBox2DObject* leftObj = new CBox2DObject(levelTwo.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { -1.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(levelTwo.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 51.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(levelTwo.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 101.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* barrierObj = new CBox2DObject(levelTwo.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 6.0f }, { 2.0f, 2.0f });
	barrierObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	levelTwo.boundsObjects.push_back(groundObj);
	levelTwo.boundsObjects.push_back(leftObj);
	levelTwo.boundsObjects.push_back(topObj);
	levelTwo.boundsObjects.push_back(rightObj);
	levelTwo.boundsObjects.push_back(barrierObj);

	m_levels[1] = levelTwo;
}

void CGame::InitLvl3(b2World * _world)
{
	Lvl levelTree;
	levelTree.world = _world;
	levelTree.listener = new CB2DListener();
	_world->SetContactListener(levelTree.listener);


	
	//Enviroment
	/***************************************************************************************************/
	b2FixtureDef enviroFixture;
	enviroFixture.density = 50.0f;
	enviroFixture.friction = 0.5f;
	enviroFixture.restitution = 0.0f;

	b2WeldJointDef weldJointDef1; //Weld Joint
	weldJointDef1.collideConnected = false;

	b2WeldJointDef weldJointDef2; //Weld Joint
	weldJointDef2.collideConnected = false;

	b2WheelJointDef wheelJointDef1; //wheel joint
	wheelJointDef1.collideConnected = false;
	wheelJointDef1.frequencyHz = 50000;
	wheelJointDef1.enableMotor = true;

	b2WheelJointDef wheelJointDef2;//wheel joint
	wheelJointDef2.collideConnected = false;
	wheelJointDef2.frequencyHz = 50000;
	wheelJointDef2.enableMotor = true;
	//Platform Box
	CBox2DObject* tempObj = new CBox2DObject(levelTree.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 75.0f, 12.0f }, { 15.0f, 1.0f });
	tempObj->SetHealth(7);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	//Welds
	weldJointDef1.bodyA = tempObj->GetBody(); //Weld Def 1
	weldJointDef1.localAnchorA = { -10, 0 };

	weldJointDef2.bodyA = tempObj->GetBody(); //Weld Def 2
	weldJointDef2.localAnchorA = { 10, 0 };

	//Wheels
	wheelJointDef1.bodyA = tempObj->GetBody();
	wheelJointDef1.localAnchorA = { -10, -4 };
	wheelJointDef1.localAxisA = { 0, 1 };

	wheelJointDef2.bodyA = tempObj->GetBody();
	wheelJointDef2.localAnchorA = { 10, -4 };
	wheelJointDef2.localAxisA = { 0, 1 };

	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;

	//Left Wheel
	tempObj = new CBox2DObject(levelTree.world, CIRCLE, enviroFixture, true, "Resources/boulder.png", { 65.0f, 10.0f }, { 3.0f, 3.0f });
	tempObj->SetHealth(99);
	wheelJointDef1.bodyB = tempObj->GetBody();
	wheelJointDef1.localAnchorB = { 0, 0 };
	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;
	
	//Right Wheel
	enviroFixture.density = 70.0f;
	tempObj = new CBox2DObject(levelTree.world, CIRCLE, enviroFixture, true, "Resources/boulder.png", { 85.0f, 10.0f }, { 3.0f, 3.0f });
	tempObj->SetHealth(99);
	wheelJointDef2.bodyB = tempObj->GetBody();
	wheelJointDef2.localAnchorB = { 0, 0 };

	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;


	tempObj = new CBox2DObject(levelTree.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 65.0f, 18.0f }, { 1.0f, 5.0f });
	tempObj->SetHealth(7);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	weldJointDef1.bodyB = tempObj->GetBody(); //Weld Def 1
	weldJointDef1.localAnchorB = {0.0f, -5.0f};

	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;

	tempObj = new CBox2DObject(levelTree.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 85.0f, 20.0f }, { 1.0f, 7.0f });
	tempObj->SetHealth(7);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	weldJointDef2.bodyB = tempObj->GetBody(); //Weld Def 2
	weldJointDef2.localAnchorB = { 0.0f, -5.0f };

	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;

	//Right box
	 tempObj = new CBox2DObject(levelTree.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 77.0f, 14.5f }, { 1.5f, 1.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;

	//Left box
	tempObj = new CBox2DObject(levelTree.world, BOX, enviroFixture, true, "Resources/boxEmpty.png", { 73.0f, 14.5f }, { 1.5f, 1.5f });
	tempObj->SetHealth(3);
	tempObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });
	levelTree.objects.push_back(tempObj);
	tempObj = nullptr;

	//Pigs
	/***************************************************************************************************/
	b2FixtureDef PigObjfixtureDef;
	PigObjfixtureDef.density = 90.0f;
	PigObjfixtureDef.friction = 0.7f;
	PigObjfixtureDef.restitution = 0.1f;

	CBox2DObject* PigObj = new CBox2DObject(levelTree.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 75.0f, 14.5f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	//PigObj->GetBody()->SetActive(false);
	levelTree.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelTree.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 70.0f, 14.5f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	//PigObj->GetBody()->SetActive(false);
	levelTree.enemies.push_back(PigObj);
	PigObj = nullptr;

	PigObj = new CBox2DObject(levelTree.world, CIRCLE, PigObjfixtureDef, true, "Resources/Pig.png", { 80.0f, 14.5f }, { 1.8f, 1.8f });
	PigObj->SetHealth(2);
	//PigObj->GetBody()->SetActive(false);
	levelTree.enemies.push_back(PigObj);
	PigObj = nullptr;

	//birds
	/***************************************************************************************************/

	b2FixtureDef thrownObjfixtureDef;
	thrownObjfixtureDef.density = 80.0f;
	thrownObjfixtureDef.friction = 1.0f;
	thrownObjfixtureDef.restitution = 0.2f;

	CBox2DObject* bird = new CBox2DObject(levelTree.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird.png", slingFromPoint, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(NORMAL);
	levelTree.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelTree.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird1.png", { 16.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPEEDER);
	levelTree.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelTree.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird1.png", { 12.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPEEDER);
	levelTree.birds.push_back(bird);
	bird = nullptr;

	bird = new CBox2DObject(levelTree.world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird1.png", { 8.0f, 6.5f }, { 2.0f, 2.0f });
	bird->GetBody()->SetActive(false);
	bird->SetHealth(999);
	bird->SetBirdType(SPEEDER);
	levelTree.birds.push_back(bird);
	bird = nullptr;

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 1.0f;

	CBox2DObject* groundObj = new CBox2DObject(levelTree.world, BOX, fixtureDef, false, "Resources/groundobj.jpg", { 50.0f, -5.0f }, { 50.0f, 10.0f });
	CBox2DObject* leftObj = new CBox2DObject(levelTree.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { -1.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* topObj = new CBox2DObject(levelTree.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 51.0f }, { 100.0f, 1.0f });
	CBox2DObject* rightObj = new CBox2DObject(levelTree.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 101.0f, 50.0f }, { 1.0f, 100.0f });
	CBox2DObject* barrierObj = new CBox2DObject(levelTree.world, BOX, fixtureDef, false, "Resources/boxEmpty.png", { 50.0f, 6.0f }, { 2.0f, 2.0f });
	barrierObj->ChangeTexture({ 0.0f, 0.0f }, { 0.5f, 1.0f });

	levelTree.boundsObjects.push_back(groundObj);
	levelTree.boundsObjects.push_back(leftObj);
	levelTree.boundsObjects.push_back(topObj);
	levelTree.boundsObjects.push_back(rightObj);
	levelTree.boundsObjects.push_back(barrierObj);


	levelTree.joints.push_back(levelTree.world->CreateJoint(&weldJointDef1));
	levelTree.joints.push_back(levelTree.world->CreateJoint(&weldJointDef2));
	levelTree.joints.push_back(levelTree.world->CreateJoint(&wheelJointDef1));
	levelTree.joints.push_back(levelTree.world->CreateJoint(&wheelJointDef2));
	m_levels[2] = levelTree;

}

void CGame::ResetLvl(int _lvl)
{
	int size = m_levels[_lvl].objects.size();
	for (int i = 0; i < size; i++)
	{
		delete m_levels[_lvl].objects[i];
		m_levels[_lvl].objects[i] = nullptr;
		//m_levels[_lvl].objects.erase(m_levels[_lvl].objects.begin() + i);
	}

	size = m_levels[_lvl].enemies.size();
	for (int i = 0; i < size; i++)
	{
		delete m_levels[_lvl].enemies[i];
		m_levels[_lvl].enemies[i] = nullptr;
		//m_levels[_lvl].enemies.erase(m_levels[_lvl].enemies.begin() + i);
	}

	size = m_levels[_lvl].birds.size();
	for (int i = 0; i < size; i++)
	{
		delete m_levels[_lvl].birds[i];
		m_levels[_lvl].birds[i] = nullptr;
		//m_levels[_lvl].birds.erase(m_levels[_lvl].birds.begin() + i);
	}

	m_levels[_lvl].objects.clear();
	m_levels[_lvl].enemies.clear();
	m_levels[_lvl].birds.clear();

	switch (_lvl)
	{
	case 0:
	{
		InitLvl1(m_levels[_lvl].world);
		break;
	}
	case 1:
	{
		InitLvl2(m_levels[_lvl].world);
		break;
	}
	case 2:
	{
		InitLvl3(m_levels[_lvl].world);
		break;
	}
	default:
		break;
	}
	m_CurrentBird = 0;
}

void CGame::Init()
{
	m_audio = new CAudioManager();
	m_audio->Init();

	m_audio->LoadAudio("Resources/SoundFiles/bird.wav", "bird_sound", FMOD_DEFAULT);
	m_audio->LoadAudio("Resources/SoundFiles/pigsplat.mp3", "pig_sound", FMOD_DEFAULT);

	m_slingShotObjectBack = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotback.png", MESH_2D_SPRITE);
	m_slingShotObjectBack->Translate({ slingFromPoint.x, 12.0f, 0.0f });
	m_slingShotObjectBack->Scale({ 5.0f, 8.0f, 0.0f });

	m_slingShotObjectFront = new CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/slingshotfront.png", MESH_2D_SPRITE);
	m_slingShotObjectFront->Translate({ slingFromPoint.x, 12.0f, 0.0f });
	m_slingShotObjectFront->Scale({ 5.0f, 8.0f, 0.0f });

	m_CurrentBird = 0;

	b2Vec2 grav = { 0.0f, -300.0f };

	m_levels.resize(3);

	InitLvl1(new b2World(grav));
	InitLvl2(new b2World(grav));
	InitLvl3(new b2World(grav));

	//m_levels.resize(3);
}

bool CGame::Process(int levelNum)
{

	for (auto&& x : m_levels[levelNum].boundsObjects)
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

			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f}, { slingFromPoint.x, slingFromPoint.y, 0.0f }, 2500.0f);
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

			m_levels[levelNum].birds[m_CurrentBird]->SetPos(slingFromPoint);
			fired = false;
			birdAbility = false;
		}
		else if(m_CurrentBird == m_levels[levelNum].birds.size() - 1 && speed < 10.0f)
		{
			m_CurrentBird++;
		}

		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !birdAbility && m_levels[levelNum].birds[m_CurrentBird]->GetBirdType() == SPEEDER)
		{
			b2Vec2 slingForce = GetSlingForce({ GetMouse().x, GetMouse().y, 0.0f }, { m_levels[levelNum].birds[m_CurrentBird]->GetPos().x, m_levels[levelNum].birds[m_CurrentBird]->GetPos().y, 0.0f }, 3500.0f);
			m_levels[levelNum].birds[m_CurrentBird]->GetBody()->ApplyLinearImpulse(-slingForce, m_levels[levelNum].birds[m_CurrentBird]->GetPos(), true);


			birdAbility = true;
		}
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD && !birdAbility && m_levels[levelNum].birds[m_CurrentBird]->GetBirdType() == SPLITTER)
		{
	
			b2FixtureDef thrownObjfixtureDef;
			thrownObjfixtureDef.density = 50.0f;
			thrownObjfixtureDef.friction = 0.7f;
			thrownObjfixtureDef.restitution = 0.2f;

			b2Vec2 pos = m_levels[levelNum].birds[m_CurrentBird]->GetPos();
			CBox2DObject* bird1 = new CBox2DObject(m_levels[levelNum].world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { pos.x, pos.y + 5.0f }, { 1.5f, 1.5f });
			bird1->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird1->SetHealth(999);
			bird1->SetBirdType(MINI_SPLITTER);

			CBox2DObject* bird2 = new CBox2DObject(m_levels[levelNum].world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { pos.x, pos.y }, { 1.5f, 1.5f });
			bird2->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird2->SetHealth(999);
			bird2->SetBirdType(MINI_SPLITTER);

			CBox2DObject* bird3 = new CBox2DObject(m_levels[levelNum].world, CIRCLE, thrownObjfixtureDef, true, "Resources/bird2.png", { pos.x, pos.y - 5.0f }, { 1.5f, 1.5f });
			bird3->GetBody()->SetLinearVelocity(m_levels[levelNum].birds[m_CurrentBird]->GetBody()->GetLinearVelocity());
			bird3->SetHealth(999);
			bird3->SetBirdType(MINI_SPLITTER);

			delete m_levels[levelNum].birds[m_CurrentBird];
			m_levels[levelNum].birds[m_CurrentBird] = nullptr;
			m_levels[levelNum].birds.erase(m_levels[levelNum].birds.begin() + m_CurrentBird);

			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird1);
			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird2);
			m_levels[levelNum].birds.insert(m_levels[levelNum].birds.begin() + m_CurrentBird, bird3);

			m_CurrentBird += 2;
			birdAbility = true;
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
	m_levels[levelNum].world->Step(timeStep, velocityIterations, positionIterations);

	std::cout << m_CurrentBird << std::endl;
	if (m_levels[levelNum].enemies.empty())
	{
		m_winner = 0;
		fired = false;
		return(true);
	}
	else if (m_CurrentBird > m_levels[levelNum].birds.size() - 1)
	{
		m_winner = 1;
		fired = false;
		return(true);
	}
	else
	{
		return(false);
	}
	
}

void CGame::Render(int levelNum)
{

	m_slingShotObjectBack->Render(CCameraManager::GetInstance().GetOrthoCam());

	for (CBox2DObject* x: m_levels[levelNum].boundsObjects)
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
