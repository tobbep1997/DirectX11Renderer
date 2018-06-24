#include "Light.h"
#include "../Window/Extern.h"


void Light::_createViewMatrix()
{
	XMVECTOR pos = XMLoadFloat4A(&this->_position);
	XMVECTOR direction = XMLoadFloat4A(&this->_direction);
	XMVECTOR up = XMLoadFloat4A(&this->_up);
	XMStoreFloat4x4A(&this->_viewMatrix, XMMatrixTranspose(XMMatrixLookToLH(pos, direction, up)));
}

void Light::_createProjectionMatrix()
{
	
	XMStoreFloat4x4A(&this->_projectionMatrix, XMMatrixTranspose(XMMatrixOrthographicLH(4096 / 64, 4096 / 64, 1, 20)));
}

Light::Light()
{
	this->_position = XMFLOAT4A(0, 0, 0, 1);
	this->_direction = XMFLOAT4A(0, 0, 0, 0);
	this->_color = XMFLOAT4A(1, 1, 1, 1);
	this->_up = XMFLOAT4A(0, 1, 0, 1);
	this->type = 0;
	this->castShadow = false;
}


Light::~Light()
{
}

void Light::Draw()
{
	DX::lights.push_back(this);
}

void Light::SetPosition(float x, float y, float z, float w)
{
	this->SetPosition(XMFLOAT4A(x, y, z, w));
}

void Light::SetDirection(float x, float y, float z, float w)
{
	this->SetDirection(XMFLOAT4A(x, y, z, w));
}

void Light::SetColor(float x, float y, float z, float w)
{
	this->SetColor(XMFLOAT4A(x, y, z, w));
}

void Light::SetPosition(XMFLOAT4A position)
{
	this->_position = position;
}

void Light::SetDirection(XMFLOAT4A direction)
{
	XMVECTOR dir = XMLoadFloat4A(&direction);
	dir = XMVector4Normalize(dir);
	XMStoreFloat4A(&this->_direction, dir);
}

void Light::SetColor(XMFLOAT4A color)
{
	this->_color = color;
}

void Light::SetLightType(LIGHT_TYPE lightType)
{
	this->type = lightType;
}

void Light::CreateMatrixes()
{
	this->_createViewMatrix();
	this->_createProjectionMatrix();

	XMMATRIX view = XMLoadFloat4x4A(&this->_viewMatrix);
	XMMATRIX projection = XMLoadFloat4x4A(&this->_projectionMatrix);

	XMStoreFloat4x4A(&this->_viewProjectionMatrix, projection * view);
}

bool Light::CastShadow()
{
	if (type == LIGHT_TYPE::point)
		return false;
	else
	{
		this->CreateMatrixes();
		DX::shadowViewProjection = this->_viewProjectionMatrix;
		this->castShadow = true;
		return true;
	}
}

XMFLOAT4A Light::GetPosition()
{
	return this->_position;
}

XMFLOAT4A Light::GetDirection()
{
	return this->_direction;
}

XMFLOAT4A Light::GetColor()
{
	return this->_color;
}

int Light::GetInfo()
{
	return this->type;
}

bool Light::GetCastShadow() const
{
	return castShadow;
}
