#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

/*
	0 = point
	1 = dir
	2 = spotlight
*/

enum LIGHT_TYPE
{
	point,
	directional,
	spotlight
};

using namespace DirectX;
class Light
{
private:
	XMFLOAT4A	_position;
	XMFLOAT4A	_direction;
	XMFLOAT4A	_color;

	XMFLOAT4A	_up;

	XMFLOAT4X4A _viewMatrix;
	XMFLOAT4X4A _projectionMatrix;
	XMFLOAT4X4A _viewProjectionMatrix;
	int type;
protected:
	void _createViewMatrix();
	void _createProjectionMatrix();
public:
	Light();
	~Light();

	void Draw();

	void SetPosition(float x, float y, float z, float w = 1);
	void SetDirection(float x, float y, float z, float w = 0);
	void SetColor(float r, float g, float b, float a = 1);
	void SetPosition(XMFLOAT4A position);
	void SetDirection(XMFLOAT4A direction);
	void SetColor(XMFLOAT4A color);

	void SetLightType(LIGHT_TYPE lightType);

	void CreateMatrixes();

	bool CastShadow();

	XMFLOAT4A GetPosition();
	XMFLOAT4A GetDirection();
	XMFLOAT4A GetColor();
	int	GetInfo();
};

