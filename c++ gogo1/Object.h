#pragma once

#include "MathTypes.h"

class URenderer;
struct ID3D11Buffer;

class Object
{
public:
	virtual ~Object();

	virtual void Update() = 0;
	virtual void Render(URenderer& renderer, ID3D11Buffer* vertexBuffer, unsigned int numVertices) = 0;
	virtual void Collision(Object* other) = 0;

	virtual const FVector& GetLocation() const = 0;
	virtual const FVector& GetVelocity() const = 0;
	virtual float GetRadius() const = 0;
	virtual float GetMass() const = 0;
};
