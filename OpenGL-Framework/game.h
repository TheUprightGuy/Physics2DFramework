#ifndef __GAME_H__
#define __GAME_H__

#include "Dependencies/Box2D/Box2D.h"

#include "ContactListener.h"
#include "utils.h"
#include "input.h"
#include "CameraManager.h"
#include "Box2DObject.h"
#include "AudioManager.h"

struct Lvl
{
	std::vector<CBox2DObject*> objects;
	std::vector<CBox2DObject*> enemies;
	std::vector<CBox2DObject*> birds;
	std::vector<b2Joint*> joints;
};

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Process(int levelNum);
	void Render(int levelNum);

	glm::vec3 GetMouse();
	b2Vec2 GetSlingForce(glm::vec3 _pointA, glm::vec3 _pointB, float _springRetension);
	
	void ProcessCollisions(b2Contact* _contact);
private:
	b2World * m_world;
	CB2DListener * m_listener;

	const b2Vec2 slingFromPoint = { 20.0f, 18.0f };

	std::vector<CBox2DObject*> m_boundsObjects;

	std::vector<CBox2DObject*> m_LevelObjects;
	std::vector<CBox2DObject*> m_pigs;
	CBox2DObject * ThrownObj;

	std::vector<Lvl> m_levels;

	CAudioManager* m_audio;

	int m_CurrentBird;

	CObject * m_slingShotObjectBack;
	CObject * m_slingShotObjectFront;
	CObject * m_background;
};

#endif
