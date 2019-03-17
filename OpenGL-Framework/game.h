#ifndef __GAME_H__
#define __GAME_H__
#include "Box2DObject.h"
#include "utils.h"
#include "input.h"
#include "Dependencies/Box2D/Box2D.h"
#include "CameraManager.h"

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Process();
	void Render();

	glm::vec3 GetMouse();
	b2Vec2 GetSlingForce(glm::vec3 _pointA, glm::vec3 _pointB, float _springRetension);
	
private:
	b2World * m_world;

	const b2Vec2 slingFromPoint = { 20.0f, 18.0f };
	std::vector<CBox2DObject*> m_boundsObjects;

	std::vector<CBox2DObject*> m_LevelObjects;

	CObject * m_slingShotObjectBack;
	CObject * m_slingShotObjectFront;
	CObject * m_background;
	CBox2DObject * ThrownObj;
	CBox2DObject * GroundPhysicsObject;
};

#endif
