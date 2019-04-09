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
	b2World * world;
	CB2DListener* listener;
	std::vector<CBox2DObject*> objects;
	std::vector<CBox2DObject*> enemies;
	std::vector<CBox2DObject*> birds;
	std::vector<CBox2DObject*> boundsObjects;
	std::vector<b2Joint*> joints;
};

class CGame
{
public:
	CGame();
	~CGame();


	void InitLvl1(b2World * _world);
	void InitLvl2(b2World * _world);
	void InitLvl3(b2World * _world);

	void ResetLvl(int _lvl);

	void Init();
	bool Process(int levelNum);
	void Render(int levelNum);

	glm::vec3 GetMouse();
	b2Vec2 GetSlingForce(glm::vec3 _pointA, glm::vec3 _pointB, float _springRetension);
	
	void ProcessCollisions(b2Contact* _contact);

	//0 = pigs, 1 = birds;
	bool GetWinner() { return(m_winner); }
private:
	b2World * m_world;
	CB2DListener * m_listener;

	const b2Vec2 slingFromPoint = { 20.0f, 18.0f };

	std::vector<CBox2DObject*> m_boundsObjects;

	std::vector<Lvl> m_levels;

	CAudioManager* m_audio;

	int m_CurrentBird;
	bool m_winner;
	CObject * m_slingShotObjectBack;
	CObject * m_slingShotObjectFront;

};

#endif
