#pragma once
#ifndef __BOX2DOBJECT_H__
#define __BOX2DOBJECT_H___

//#include "game.h"
#include "utils.h"
#include "object.h"
#include "ProgramManager.h"
#include "Dependencies/Box2D/Box2D.h"

enum ColliderShape
{
	BOX,
	CIRCLE
};

enum BirdType
{
	NORMAL,
	SPLITTER,
	MINI_SPLITTER,
	SPEEDER
};
class CBox2DObject : public CObject
{
public:
	CBox2DObject(b2World *_world, ColliderShape _colliderShape, b2FixtureDef& _fixtureDef, bool _isDynamic, std::string ObjTexture, b2Vec2 _initPos = { 0.0f, 0.0f }, b2Vec2 _initSize = {1.0f, 1.0f});
	~CBox2DObject();

	void Process();
	b2Body* GetBody() { return(m_body); }

	void SetPos(b2Vec2 NewPos);
	b2Vec2 GetPos() { return(m_body->GetPosition()); }

	void SetRotation(float _degrees);
	float GetRotation() { return(glm::degrees(m_body->GetAngle())); }
	int GetHealth() { return(m_iHealth); }
	void SetHealth(int _iHealth) { m_iHealth = _iHealth; }
	
	void SetBirdType(BirdType _birdType) { m_birdtype = _birdType; }
	BirdType GetBirdType() { return(m_birdtype); }

	bool m_Dynamic;
private:

	b2World* m_world;
	b2Body* m_body;
	ColliderShape m_Collider;

	BirdType m_birdtype;
	int m_iHealth;
};
#endif // !__PHYSICSOBJECT_H__
