#pragma once

#include <vector>

class Object;
class URenderer;
struct ID3D11Buffer;

class BallManager
{
public:
	~BallManager();

	void Init();
	void Update();
	void Render(URenderer& renderer, ID3D11Buffer* vertexBuffer, unsigned int vertexCount);
	void SetBallCount(int ballCount);
	void Clear();

	int GetBallCount() const;

private:
	void AddRandomBall();
	void RemoveRandomBall();
	bool CanPlaceBall(float x, float y, float radius) const;

	std::vector<Object*> BallList;
};
