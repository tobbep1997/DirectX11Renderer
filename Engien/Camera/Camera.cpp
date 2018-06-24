#include "Camera.h"
#include "../Window/Input.h"


void Camera::_createViewMatrix()
{
	XMVECTOR pos = XMLoadFloat4A(&this->_position);
	XMVECTOR direction = XMLoadFloat4A(&this->_direction);
	XMVECTOR up = XMLoadFloat4A(&this->_up);
	XMStoreFloat4x4A(&this->_viewMatrix, XMMatrixTranspose(XMMatrixLookToLH(pos, direction, up)));
}

void Camera::_createPerspectivProjectionMatrix(float fovRad, float aspectRatio, float nearPlane, float farPlane)
{
	XMStoreFloat4x4A(&this->_projectionMatrix, XMMatrixTranspose(XMMatrixPerspectiveFovLH(fovRad, aspectRatio, nearPlane, farPlane)));
}

void Camera::_createViewProjectionMatrix()
{
	XMMATRIX view = XMLoadFloat4x4A(&this->_viewMatrix);
	XMMATRIX projection = XMLoadFloat4x4A(&this->_projectionMatrix);

	XMStoreFloat4x4A(&this->_viewProjectionMatrix, projection * view);
}

Camera::Camera()
{
	this->_position = XMFLOAT4A(0, 0, 0, 1);
	this->_direction = XMFLOAT4A(0, 0, -1, 0);
	this->_up = XMFLOAT4A(0, 1, 0, 0);
	this->_forward = XMFLOAT4A(0, 0, 1, 0);
	this->_speed = 1.f;
	this->_sense = 1.f;
	this->_pitch = 0;
	this->_yaw = 0;
}


Camera::~Camera()
{
}

void Camera::Init(float fovRad, float aspectRatio, float nearPlane, float farPlane)
{
	this->_createViewMatrix();
	this->_createPerspectivProjectionMatrix(fovRad, aspectRatio, nearPlane, farPlane);
	this->_createViewProjectionMatrix();

}

void Camera::SetPosition(float x, float y, float z, float w)
{
	this->SetPosition(XMFLOAT4A(x, y, z, w));
}

void Camera::SetDirection(float x, float y, float z, float w)
{
	this->SetDirection(XMFLOAT4A(x, y, z, w));
}

void Camera::SetPosition(XMFLOAT4A position)
{
	this->_position = position;
	this->_createViewMatrix();
	this->_createViewProjectionMatrix();

}

void Camera::SetDirection(XMFLOAT4A direction)
{
	XMStoreFloat4A(&this->_direction, XMVector4Normalize(XMLoadFloat4A(&direction)));
	this->_createViewMatrix();
	this->_createViewProjectionMatrix();

}

void Camera::Update(float deltaTime)
{
	XMVECTOR pos = XMLoadFloat4A(&this->_position);
	XMVECTOR direction = XMLoadFloat4A(&this->_direction);
	XMVECTOR up = XMLoadFloat4A(&this->_up);


	DirectX::XMFLOAT2 mouseDelta = Input::GetMousePosDelta();
	
	_pitch += mouseDelta.y * this->_sense * deltaTime;
	_yaw += mouseDelta.x * this->_sense * deltaTime;

	if (_pitch > XM_PI / 2.1f)
		_pitch = XM_PI / 2.1f;

	if (_pitch < -XM_PI / 2.1f)
		_pitch = -XM_PI / 2.1f;

	XMMATRIX rotMatrixX = XMMatrixRotationRollPitchYaw(_pitch, _yaw, 0);
	direction = XMVector3TransformCoord(XMLoadFloat4(&this->_forward), rotMatrixX);
	direction = XMVector3Normalize(direction);

	XMVECTOR right = XMVector3Normalize(XMVector3Cross(up, direction));
	XMVECTOR forward = XMVector3Normalize(XMVector3Cross(right, up));
	
	if (Input::GetKeyDown('A'))
	{
		pos -= right * _speed * deltaTime;
	}
	if (Input::GetKeyDown('D'))
	{
		pos += right * _speed * deltaTime;
	}
	if (Input::GetKeyDown('W'))
	{
		pos += forward * _speed * deltaTime;
	}
	if (Input::GetKeyDown('S'))
	{
		pos -= forward * _speed * deltaTime;
	}

	

	XMStoreFloat4A(&this->_direction, direction);
	XMStoreFloat4A(&this->_position, pos);

	this->_createViewMatrix();
	this->_createViewProjectionMatrix();
}

void Camera::SetSpeed(float speed)
{
	this->_speed = speed;
}

void Camera::SetSense(float sense)
{
	this->_sense = sense;
}


XMFLOAT4X4A Camera::GetViewMatrix() const
{
	return this->_viewMatrix;
}

XMFLOAT4X4A Camera::GetProjectionMatrix() const
{
	return this->_projectionMatrix;
}

XMFLOAT4X4A Camera::GetViewProjectionMatrix() const
{
	return this->_viewProjectionMatrix;
}

XMFLOAT4A Camera::GetPosition() const
{
	return this->_position;
}
