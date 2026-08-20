#include "CollisionManager.h"

#include "Object.h"

void CollisionManager::CollBrute(Object* const* objectList, int objectCount)
{
	for (int i = 0; i < objectCount; ++i)
	{
		for (int j = i + 1; j < objectCount; ++j)
		{
			CollCheck(objectList[i], objectList[j]);
		}
	}
}

void CollisionManager::CollCheck(Object* object1, Object* object2)
{
	if (!CircleCheck(object1, object2))
	{
		return;
	}

	object1->Collision(object2);
	object2->Collision(object1);
}

bool CollisionManager::CircleCheck(const Object* object1, const Object* object2)
{
	const FVector& location1 = object1->GetLocation();
	const FVector& location2 = object2->GetLocation();

	const float distanceX = location2.x - location1.x;
	const float distanceY = location2.y - location1.y;
	const float radiusSum = object1->GetRadius() + object2->GetRadius();

	return radiusSum * radiusSum >= distanceX * distanceX + distanceY * distanceY;
}
