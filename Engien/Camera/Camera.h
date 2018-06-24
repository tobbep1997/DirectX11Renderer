#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
private:
	XMFLOAT4A		_position;
	XMFLOAT4A		_direction;
	XMFLOAT4A		_up, _forward;

	XMFLOAT4X4A		_viewMatrix;
	XMFLOAT4X4A		_projectionMatrix;
	XMFLOAT4X4A		_viewProjectionMatrix;

	float			_speed;
	float			_sense;

	float			_pitch;
	float			_yaw;

protected:
	void _createViewMatrix();
	void _createPerspectivProjectionMatrix(float fovRad = XM_PI / 2, float aspectRatio = 16.0f/9.0f, float nearPlane = 1.0f, float farPlane = 200.0f);
	void _createViewProjectionMatrix();

public:
	Camera();
	~Camera();

	void Init(float fovRad = XM_PI / 2, float aspectRatio = 16.0f / 9.0f, float nearPlane = 1.0f, float farPlane = 200.0f);

	void SetPosition(float x, float y, float z, float w = 1);
	void SetDirection(float x, float y, float z, float w = 0);

	void SetPosition(XMFLOAT4A position);
	void SetDirection(XMFLOAT4A direction);

	void Update(float deltaTime = 1.0);

	void SetSpeed(float speed);
	void SetSense(float sense);

	XMFLOAT4X4A GetViewMatrix() const;
	XMFLOAT4X4A GetProjectionMatrix() const;
	XMFLOAT4X4A GetViewProjectionMatrix() const;

	XMFLOAT4A	GetPosition() const;
};

