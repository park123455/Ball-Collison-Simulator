#include "BallManager.h"

#include <cstdlib>

#include "Ball.h"
#include "CollisionManager.h"
#include "Object.h"

namespace
{
	constexpr float RadiusScale = 0.01f;
	constexpr float PositionScale = 0.01f;
	constexpr float VelocityScale = 0.001f;
}

BallManager::~BallManager()
{
	Clear();
}

void BallManager::Init()
{
	if (!BallList.empty())
	{
		return;
	}

	BallList.push_back(new Ball(
		FVector(0.0f, 0.0f, 0.0f),
		FVector(0.003f, 0.002f, 0.0f),
		0.07f));
}

void BallManager::Update()
{
	CollisionManager::CollBrute(BallList.data(), GetBallCount());

	for (Object* ball : BallList)
	{
		ball->Update();
	}
}

void BallManager::Render(
	URenderer& renderer,
	ID3D11Buffer* vertexBuffer,
	unsigned int vertexCount)
{
	for (Object* ball : BallList)
	{
		ball->Render(renderer, vertexBuffer, vertexCount);
	}
}

void BallManager::SetBallCount(int ballCount)
{
	if (ballCount < 1)
	{
		ballCount = 1;
	}

	while (GetBallCount() < ballCount)
	{
		AddRandomBall();
	}

	while (GetBallCount() > ballCount)
	{
		RemoveRandomBall();
	}
}

void BallManager::Clear()
{
	for (Object* ball : BallList)
	{
		delete ball;
	}

	BallList.clear();
}

int BallManager::GetBallCount() const
{
	return static_cast<int>(BallList.size());
}

void BallManager::AddRandomBall()
{
	const float radius = (std::rand() % 6 + 5) * RadiusScale;
	float x;
	float y;

	do
	{
		x = (std::rand() % 161 - 80) * PositionScale;
		y = (std::rand() % 161 - 80) * PositionScale;
	} while (!CanPlaceBall(x, y, radius));

	const float velocityX = (std::rand() % 11 - 5) * VelocityScale;
	const float velocityY = (std::rand() % 11 - 5) * VelocityScale;

	BallList.push_back(new Ball(
		FVector(x, y, 0.0f),
		FVector(velocityX, velocityY, 0.0f),
		radius));
}

void BallManager::RemoveRandomBall()
{
	const int randomIndex = std::rand() % GetBallCount();

	delete BallList[randomIndex];
	BallList[randomIndex] = BallList.back();
	BallList.pop_back();
}

bool BallManager::CanPlaceBall(float x, float y, float radius) const
{
	for (const Object* ball : BallList)
	{
		const float distanceX = x - ball->GetLocation().x;
		const float distanceY = y - ball->GetLocation().y;
		const float radiusSum = radius + ball->GetRadius();

		if (distanceX * distanceX + distanceY * distanceY < radiusSum * radiusSum)
		{
			return false;
		}
	}

	return true;
}
