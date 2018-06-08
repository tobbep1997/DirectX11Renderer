#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class Camera
{
private:
	XMFLOAT4A		_position;
	XMFLOAT4A		_direction;
	XMFLOAT4A		_up;

	XMFLOAT4X4A		_viewMatrix;
	XMFLOAT4X4A		_projectionMatrix;
	XMFLOAT4X4A		_viewProjectionMatrix;

protected:
	void _createViewMatrix();
	void _createPerspectivProjectionMatrix(float fovRad = XM_PI / 2, float aspectRatio = 16.0f/9.0f, float nearPlane = 1.0f, float farPlane = 20.0f);
	void _createViewProjectionMatrix();
public:
	Camera();
	~Camera();

	void Init(float fovRad = XM_PI / 2, float aspectRatio = 16.0f / 9.0f, float nearPlane = 1.0f, float farPlane = 20.0f);

	void SetPosition(XMFLOAT4A position);
	void SetDirection(XMFLOAT4A direction);

	XMFLOAT4X4A GetViewMatrix() const;
	XMFLOAT4X4A GetProjectionMatrix() const;
	XMFLOAT4X4A GetViewProjectionMatrix() const;
};

