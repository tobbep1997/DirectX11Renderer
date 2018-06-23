#include "Input.h"

bool Input::m_keys[256];
bool Input::m_mouseKeys[3];
DirectX::XMFLOAT2 Input::m_mousePos;
DirectX::XMFLOAT2 Input::m_preMousePos;


float Input::m_scrollDelta;

void Input::_setKey(UINT k, bool value)
{
	m_keys[k] = value;
}

void Input::_setMouseKey(UINT k, bool value)
{
	m_mouseKeys[k] = value;
}

void Input::_setMousePos(DirectX::XMFLOAT2 pos)
{
	m_mousePos = pos;
}

void Input::_setScrollDelta(float delta)
{
	m_scrollDelta = delta;
}

bool Input::GetKeyDown(int key)
{
	return m_keys[key];
}

bool Input::GetLeftMouse()
{
	return m_mouseKeys[0];
}

bool Input::GetMiddleMouse()
{
	return m_mouseKeys[1];
}

bool Input::GetRightMouse()
{
	return m_mouseKeys[2];
}

DirectX::XMFLOAT2 Input::GetMousePos()
{
	return m_mousePos;
}

DirectX::XMFLOAT2 Input::GetMousePosDelta()
{
	DirectX::XMFLOAT2 value;
	value.x = m_mousePos.x - m_preMousePos.x;
	value.y = m_mousePos.y - m_preMousePos.y;
	//if (value.x != 0 || value.y != 0)
	//{
	//	std::cout << value.x << " " << value.y << std::endl;
	//}
	m_preMousePos = m_mousePos;	
	return value;
}

float Input::GetMouseScroll()
{
	float value = m_scrollDelta;
	m_scrollDelta = 0.0f;
	return value;
}

Input::Input()
{
}


Input::~Input()
{
}
