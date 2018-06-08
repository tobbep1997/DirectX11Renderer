#include "Window\Window.h"
#include "Graphics/Quad.h"
#include "Camera\Camera.h"

#if _DEBUG
#include <iostream>
//Allocates memory to the console
void _alocConsole() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
}
#endif

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#if _DEBUG
	_alocConsole();
#endif

	//Start here
	Window wnd(hInstance);
	wnd.Init(1280, 720, "Hello world", false);

	Camera camera;
	camera.Init();
	camera.SetPosition(XMFLOAT4A(0, 0, 0, 1));
	camera.SetDirection(XMFLOAT4A(0, 0, 1, 0));
	//XMFLOAT4X4A test = camera.GetViewMatrix();
	Quad * draw = new Quad();
	draw->SetPosition(0, 0, 5);
	while (wnd.isOpen())
	{
		wnd.PollEvents();
		wnd.Clear(); 
		draw->SetRotation(0, draw->GetRotation().y + .01, 0);
		draw->Draw();
		wnd.Flush(&camera);
	}
	delete draw;
	//delete wnd;
	return 0;
}