#pragma once

struct FVertexSimple
{
	float x, y, z;
	float r, g, b, a;
};

struct FVector
{
	float x, y, z;

	FVector(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		: x(x), y(y), z(z)
	{
	}
};
