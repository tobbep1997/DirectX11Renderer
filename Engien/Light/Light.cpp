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
