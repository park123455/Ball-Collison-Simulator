#include "Ball.h"

#include <cmath>

#include "URenderer.h"

bool Ball::Gravity = true;
float Ball::GravityNum = 0.002f;

Ball::Ball(FVector location, FVector velocity, float radius)
	: Location(location)
	, Velocity(velocity)
	, Radius(radius)
	, Mass(radius / 0.05f)
{
}

void Ball::Update()
{
	ApplyGravity();
	PhysicsOn();
	WallTurnBack();
}

void Ball::Render(URenderer& renderer, ID3D11Buffer* vertexBuffer, unsigned int numVertices)
{
	renderer.UpdateConstant(Location, Radius);
	renderer.RenderPrimitive(vertexBuffer, numVertices);
}

void Ball::Collision(Object* other)
{
	const FVector& otherLocation = other->GetLocation();
	const FVector& otherVelocity = other->GetVelocity();

	const float distanceX = otherLocation.x - Location.x;
	const float distanceY = otherLocation.y - Location.y;
	const float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

	if (distance <= 0.000001f)
	{
		return;
	}

	const float normalX = distanceX / distance;
	const float normalY = distanceY / distance;
	const float relativeX = otherVelocity.x - Velocity.x;
	const float relativeY = otherVelocity.y - Velocity.y;
	const float normalSpeed = relativeX * normalX + relativeY * normalY;

	if (normalSpeed < 0.0f)
	{
		const float velocityChange =
			(2.0f * other->GetMass() / (Mass + other->GetMass())) * normalSpeed;
		CollVeloSum.x += velocityChange * normalX;
		CollVeloSum.y += velocityChange * normalY;
	}
}

void Ball::ApplyGravity()
{
	if (!Gravity)
	{
		return;
	}

	constexpr float GroundY = -1.0f;
	constexpr float MinDistance = 0.1f;

	const float distance = std::fabs(Location.y - GroundY);
	const float safeDistance = std::fmax(distance, MinDistance);
	const float gravityStrength = GravityNum / safeDistance;
	ForceSum.y -= Mass * gravityStrength;
}

void Ball::PhysicsOn()
{
	constexpr float DeltaTime = 1.0f;

	Acceleration.x = ForceSum.x / Mass;
	Acceleration.y = ForceSum.y / Mass;
	Acceleration.z = ForceSum.z / Mass;

	Velocity.x += Acceleration.x * DeltaTime;
	Velocity.y += Acceleration.y * DeltaTime;
	Velocity.z += Acceleration.z;

	Velocity.x += CollVeloSum.x;
	Velocity.y += CollVeloSum.y;
	Velocity.z += CollVeloSum.z;

	Location.x += Velocity.x * DeltaTime;
	Location.y += Velocity.y * DeltaTime;
	Location.z += Velocity.z;

	ForceSum = FVector();
	CollVeloSum = FVector();
}

void Ball::WallTurnBack()
{
	constexpr float LeftBorder = -1.0f;
	constexpr float RightBorder = 1.0f;
	constexpr float TopBorder = -1.0f;
	constexpr float BottomBorder = 1.0f;

	if (Location.x < LeftBorder + Radius)
	{
		Location.x = LeftBorder + Radius;
		if (Velocity.x < 0.0f)
		{
			Velocity.x *= -1.0f;
		}
	}
	else if (Location.x > RightBorder - Radius)
	{
		Location.x = RightBorder - Radius;
		if (Velocity.x > 0.0f)
		{
			Velocity.x *= -1.0f;
		}
	}

	if (Location.y < TopBorder + Radius)
	{
		Location.y = TopBorder + Radius;
		if (Velocity.y < 0.0f)
		{
			Velocity.y *= -1.0f;
		}
	}
	else if (Location.y > BottomBorder - Radius)
	{
		Location.y = BottomBorder - Radius;
		if (Velocity.y > 0.0f)
		{
			Velocity.y *= -1.0f;
		}
	}
}
