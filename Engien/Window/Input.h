#pragma once
#include "Window.h"

class Input
{
	friend class Window;
private:
	static bool m_keys[256];

	static bool m_mouseKeys[3];
	static DirectX::XMFLOAT2 m_mousePos;
	static DirectX::XMFLOAT2 m_preMousePos;
	static DirectX::XMFLOAT2 m_mouseDelta;
	static float m_scrollDelta;
private:
	static void _setKey(UINT k, bool value);
	static void _setMouseKey(UINT k, bool value);

	static void _setMousePos(DirectX::XMFLOAT2 pos);
	static void _setScrollDelta(float delta);
public:

	static bool GetKeyDown(int key);

	static bool GetLeftMouse();
	static bool GetMiddleMouse();
	static bool GetRightMouse();

	static DirectX::XMFLOAT2 GetMousePos();
	static DirectX::XMFLOAT2 GetMousePosDelta();
	static float GetMouseScroll();

	Input();
	~Input();
};

