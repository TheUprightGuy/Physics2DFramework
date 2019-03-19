#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__

#include "Dependencies/Box2D/Box2D.h"
#include "Box2DObject.h"

class CB2DListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		CBox2DObject* fixtureA;
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			fixtureA = static_cast<CBox2DObject*>(bodyUserData);
		}
		else
		{
			return;
		}

		CBox2DObject* fixtureB;
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
		{
			fixtureB = static_cast<CBox2DObject*>(bodyUserData);
		}
		else
		{
			return;
		}

		if (fixtureA->m_Dynamic)
		{
			b2Vec2 vel = fixtureB->GetBody()->GetLinearVelocity();
			glm::vec3 vel3 = { vel.x, vel.y, 0.0f };
			float speed = glm::length(vel3);

			int aHealth = fixtureA->GetHealth();
			if (speed > topBracket)
			{
				
				fixtureA->SetHealth(aHealth - 3);
			} 
			else if (speed < topBracket && speed> midBracket)
			{
				fixtureA->SetHealth(aHealth - 2);
			}
			else if (speed < midBracket && speed> 100)
			{
				fixtureA->SetHealth(aHealth - 1);
			}
		}

		if (fixtureB->m_Dynamic)
		{
			b2Vec2 vel = fixtureA->GetBody()->GetLinearVelocity();
			glm::vec3 vel3 = { vel.x, vel.y, 0.0f };
			float speed = glm::length(vel3);

			int bHealth = fixtureB->GetHealth();
			if (speed > topBracket)
			{
				fixtureB->SetHealth(bHealth - 3);
			}
			else if (speed < topBracket && speed> midBracket)
			{
				fixtureB->SetHealth(bHealth - 2);
			}
			else if (speed < midBracket && speed> 100)
			{
				fixtureB->SetHealth( - 1);
			}
		}
	}
	void EndContact(b2Contact* contact)
	{

	}
private:
	const int topBracket = 200;
	const int midBracket = 150;
	const int lowBracket = 50;
};

#endif
