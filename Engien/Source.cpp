#include "Window/Window.h"
#include "Graphics/Quad.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Graphics\Mesh\Mesh.h"
#include "Graphics\Mesh\MeshLoader.h"
#include "Window\Input.h"
#include <chrono>

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
	wnd.Init(SCREEN_WIDTH, SCREEN_HIGHT, "This is the window", false);

	Camera camera;
	camera.Init(XM_PI / 2, static_cast<float>(SCREEN_WIDTH) / SCREEN_HIGHT);
	camera.SetPosition(XMFLOAT4A(0, 2, 5, 1));
	camera.SetDirection(XMFLOAT4A(1, 0, 0, 0));
	camera.SetSense(15.f);
	camera.SetSpeed(5.0f);
	
	std::chrono::high_resolution_clock clock;	

	Mesh * draw = new Mesh();
	Mesh * floor = new Mesh();

	draw->SetMeshes(MeshLoader::LoadMesh("Mesh/Quad.obj"));
	draw->LoadTexture("Texture/stone2.jpg");
	draw->LoadNormalMap("Texture/NormalMap2.png");
	draw->LoadSpecularHighlightMap("Texture/SpecularMap2.png");

	floor->SetMeshes(MeshLoader::LoadMesh("Mesh/Quad.obj"));
	floor->LoadTexture("Texture/Brick.png");
	floor->LoadNormalMap("Texture/BrickNormal.png");
	floor->LoadSpecularHighlightMap("Texture/BrickSpec.png");

	draw->SetPosition(0, 0, 5);
	floor->SetPosition(0, -2, 5);

	draw->SetScale(1, 1, 1);
	floor->SetScale(5, 1, 5);



	Light * light = new Light();
	light->SetLightType(LIGHT_TYPE::directional);
	light->SetColor(1, 1, 1);
	light->SetPosition(0, 5, 0);
	light->SetDirection(0, -1, 1);
	light->CastShadow();
	
	__int64 post = 0;
	__int64 pre = 0;

	
	while (wnd.isOpen())
	{	
		wnd.PollEvents();
		wnd.Clear(); 
		post = clock.now().time_since_epoch().count();
		float delta = static_cast<float>(post - pre) / 1000000000.0f;
	
		camera.Update(delta);

		draw->SetRotation(0, draw->GetRotation().y + (.1f * XM_PI * 2 * delta), 0);		
		draw->Draw();
		floor->Draw();

		light->Draw();
		
		wnd.Flush(&camera);
		pre = post;
	}

	delete light;
	delete draw;
	delete floor;
	return 0;
}