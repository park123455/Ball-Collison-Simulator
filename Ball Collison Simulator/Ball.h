#pragma once

#include "Object.h"

class Ball : public Object
{
public:
	Ball(FVector location, FVector velocity, float radius);
	~Ball() override = default;

	void Update() override;
	void Render(URenderer& renderer, ID3D11Buffer* vertexBuffer, unsigned int numVertices) override;
	void Collision(Object* other) override;

	const FVector& GetLocation() const override { return Location; }
	const FVector& GetVelocity() const override { return Velocity; }
	float GetRadius() const override { return Radius; }
	float GetMass() const override { return Mass; }

	static bool Gravity;
	static float GravityNum;

private:
	void ApplyGravity();
	void PhysicsOn();
	void WallTurnBack();

	FVector Location;
	FVector Velocity;
	float Radius;
	float Mass;

	FVector Acceleration;
	FVector ForceSum;
	FVector CollVeloSum;
};
