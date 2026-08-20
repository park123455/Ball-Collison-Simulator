#pragma once

class Object;

class CollisionManager
{
public:
	static void CollBrute(Object* const* objectList, int objectCount);

private:
	static void CollCheck(Object* object1, Object* object2);
	static bool CircleCheck(const Object* object1, const Object* object2);
};
