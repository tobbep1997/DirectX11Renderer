#include "Window\Window.h"

#include "Graphics\Drawable.h"

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

	Drawable * draw = new Drawable();

	while (wnd.isOpen())
	{
		wnd.PollEvents();
		wnd.Clear();
		draw->Draw();
		wnd.Flush();
	}
	delete draw;
	//delete wnd;
	return 0;
}