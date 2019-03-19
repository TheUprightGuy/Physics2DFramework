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
		
		b2Vec2 velA = fixtureB->GetBody()->GetLinearVelocity();
		glm::vec3 velA3 = { velA.x, velA.y, 0.0f };
		float speedA = glm::length(velA3);

		b2Vec2 velB = fixtureA->GetBody()->GetLinearVelocity();
		glm::vec3 velB3 = { velB.x, velB.y, 0.0f };
		float speedB = glm::length(velB3);

		if (fixtureA->m_Dynamic)
		{
			int aHealth = fixtureA->GetHealth();
			if (speedB > topBracket)
			{
				
				fixtureA->SetHealth(aHealth - 3);
			} 
			else if (speedB < topBracket && speedB> midBracket)
			{
				fixtureA->SetHealth(aHealth - 2);
			}
			else if (speedB < midBracket && speedB> 100)
			{
				fixtureA->SetHealth(aHealth - 1);
			}

			if (speedA > topBracket)
			{
				fixtureA->SetHealth(aHealth - 3);
			}
			else if (speedA < topBracket && speedA> midBracket)
			{
				fixtureA->SetHealth(aHealth - 2);
			}
			else if (speedA < midBracket && speedA> 100)
			{
				fixtureA->SetHealth(aHealth - 1);
			}
		}

		if (fixtureB->m_Dynamic)
		{
			int bHealth = fixtureB->GetHealth();
			if (speedA > topBracket)
			{
				fixtureB->SetHealth(bHealth - 3);
			}
			else if (speedA < topBracket && speedA> midBracket)
			{
				fixtureB->SetHealth(bHealth - 2);
			}
			else if (speedA < midBracket && speedA> 100)
			{
				fixtureB->SetHealth(bHealth - 1);
			}

			if (speedB > topBracket)
			{

				fixtureB->SetHealth(bHealth - 3);
			}
			else if (speedB < topBracket && speedB> midBracket)
			{
				fixtureB->SetHealth(bHealth - 2);
			}
			else if (speedB < midBracket && speedB> 100)
			{
				fixtureB->SetHealth(bHealth - 1);
			}

		}
	}
	void EndContact(b2Contact* contact)
	{

	}
private:
	const int topBracket = 150;
	const int midBracket = 100;
	const int lowBracket = 50;
};

#endif
