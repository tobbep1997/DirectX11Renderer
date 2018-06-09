#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

/*
	0 = point
	1 = dir
	2 = spotlight
*/

using namespace DirectX;
class Light
{
private:
	XMFLOAT4A _position;
	XMFLOAT4A _direction;
	XMFLOAT4A _color;
	int type;
protected:
public:
	Light();
	~Light();

	void Draw();

	void SetColor(float x, float y, float z, float w);
	void SetColor(XMFLOAT4A color);

	XMFLOAT4A GetPosition();
	XMFLOAT4A GetDirection();
	XMFLOAT4A GetColor();
	int	GetInfo();
};

