#include "Window/Window.h"
#include "Graphics/Quad.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Graphics\Mesh\Mesh.h"
#include "Graphics\Mesh\MeshLoader.h"
#include "Window\Input.h"


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

const int SCREEN_WIDTH = 1280;
const int SCREEN_HIGHT = 720;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#if _DEBUG
	_alocConsole();
#endif

	//Start here
	Window wnd(hInstance);
	wnd.Init(SCREEN_WIDTH, SCREEN_HIGHT, "Hello world", false);

	Camera camera;
	camera.Init(XM_PI / 2, static_cast<float>(SCREEN_WIDTH) / SCREEN_HIGHT);
	camera.SetPosition(XMFLOAT4A(0, 2, 5, 1));
	camera.SetDirection(XMFLOAT4A(1, 0, 0, 0));
	

	Mesh * draw = new Mesh();
	Mesh * floor = new Mesh();
	Mesh * wall = new Mesh();
	draw->SetMeshes(MeshLoader::LoadMesh("Mesh/Quad.obj"));
	draw->LoadTexture("Texture/stone2.jpg");
	draw->LoadNormalMap("Texture/NormalMap2.png");
	floor->SetMeshes(MeshLoader::LoadMesh("Mesh/Tex.obj"));
	wall->SetMeshes(MeshLoader::LoadMesh("Mesh/Tex.obj"));
	

	draw->SetPosition(0, 0, 5);
	floor->SetPosition(0, -2, 5);
	wall->SetPosition(-10, 0, 5);
	wall->SetScale(1, 5, 10);

	draw->SetScale(1, 1, 1);
	floor->SetScale(10, 1, 10);



	Light * light = new Light();
	Light * light2 = new Light();
	Light * light3 = new Light();
	light->SetLightType(LIGHT_TYPE::directional);
	light->SetColor(1, 1, 1);
	light->SetPosition(0, 5, 0);
	light->SetDirection(0, -1, 1);
	light->CastShadow();

	light2->SetLightType(LIGHT_TYPE::spotlight);
	light2->SetColor(1, 1, 1);
	light2->SetPosition(-5, 0, 5);
	light2->SetDirection(0, -1, 0);

	light3->SetColor(1, 1, 1);
	light3->SetPosition(5, 0, 5);

	
	while (wnd.isOpen())
	{	
		wnd.PollEvents();
		wnd.Clear(); 
	
		camera.Update();


		draw->SetRotation(0, draw->GetRotation().y + .001f, 0);
		draw->Draw();
		floor->Draw();
		wall->Draw();

		light->Draw();
		light2->Draw();
		light3->Draw();
		
		
		wnd.Flush(&camera);
	}

	delete light;
	delete light2;
	delete light3;
	delete draw;
	delete floor;
	delete wall;
	return 0;
}