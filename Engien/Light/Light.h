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

	void SetPosition(float x, float y, float z, float w = 1);
	void SetColor(float r, float g, float b, float a = 1);
	void SetPosition(XMFLOAT4A position);
	void SetColor(XMFLOAT4A color);

	XMFLOAT4A GetPosition();
	XMFLOAT4A GetDirection();
	XMFLOAT4A GetColor();
	int	GetInfo();
};

