#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Mesh.fbx");//fbx->memory

		//memory->customdata
		converter->ExportMaterialData(L"Kachujin/Kachujin");
		converter->ExportModelData(L"Kachujin/Kachujin");
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
