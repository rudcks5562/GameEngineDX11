#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "triangleDemo.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	GameDesc desc;
	desc.appName = L"MyProgram";
	desc.hInstance = hinstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.5f, 0.5f, 0.5f,0.5f);
	desc.app = make_shared<triangleDemo>();

	GAME->Run(desc);


	return 0;
}
