#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Tank/Tank.fbx");//fbx->memory

		//memory->customdata
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");
		//customdata->memory
	}
	{
		//shared_ptr<Converter> converter = make_shared<Converter>();
		//converter->ReadAssetFile(L"Tower/Tower.fbx");//fbx->memory

		//memory->customdata
		//converter->ExportMaterialData(L"Tower/Tower");
		//converter->ExportModelData(L"Tower/Tower");
		//customdata->memory


	}


}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
