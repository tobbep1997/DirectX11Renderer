#include "Light.h"
#include "../Window/Extern.h"


Light::Light()
{
	this->_position = XMFLOAT4A(0, 0, 0, 1);
	this->_direction = XMFLOAT4A(0, 0, 0, 0);
	this->_color = XMFLOAT4A(1, 1, 1, 1);
	this->type = 0;
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
