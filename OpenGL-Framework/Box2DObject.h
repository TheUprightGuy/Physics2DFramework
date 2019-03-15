#pragma once
#ifndef __BOX2DOBJECT_H__
#define __BOX2DOBJECT_H___

#include "utils.h"
#include "object.h"
#include "ProgramManager.h"
#include "Dependencies/Box2D/Box2D.h"

enum ColliderShape
{
	BOX,
	CIRCLE
};
class CBox2DObject : public CObject
{
public:
	CBox2DObject(b2World *_world, ColliderShape _colliderShape, b2FixtureDef& _fixtureDef, bool _isDynamic, b2Vec2 _initPos = { 0.0f, 0.0f }, b2Vec2 _initSize = {1.0f, 1.0f});

	void Process();
	b2Body* GetBody() { return(m_body); }

	void SetPos(b2Vec2 NewPos);
	b2Vec2 GetPos() { return(m_body->GetPosition()); }

	~CBox2DObject();

private:
	b2World* m_world;
	b2Body* m_body;
	ColliderShape m_Collider;
};
#endif // !__PHYSICSOBJECT_H__