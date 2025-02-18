#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"House/House.fbx");//fbx->memory

		//memory->customdata

		//customdata->memory
	}



}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
