#include "Box2DObject.h"

CBox2DObject::CBox2DObject(b2World *_world, ColliderShape _colliderShape, b2FixtureDef& _fixtureDef, bool _isDynamic, b2Vec2 _initPos, b2Vec2 _initSize)
	: CObject(CProgrammerManager::GetInstance().GetProgram(DEFAULT), "Resources/RayMan.jpg", MESH_2D_SPRITE),
	m_world(_world)
{
	b2BodyDef bodyDef;
	bodyDef.position = _initPos;
	m_objPosition = { _initPos.x, _initPos.y, 0.0f };

	if (_isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}

	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(_initSize.x, _initSize.y);
	m_objScale = { _initSize.x, _initSize.y, 1.0f };

	_fixtureDef.shape = &boxShape;
	m_body->CreateFixture(&_fixtureDef);
}

void CBox2DObject::Process()
{
	m_objPosition = glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f);
	Rotation(m_body->GetAngle());
}

void CBox2DObject::SetPos(b2Vec2 NewPos)
{
	m_body->SetTransform(NewPos, m_body->GetAngle());
	m_objPosition = glm::vec3( NewPos.x, NewPos.y, 0.0f );
}

