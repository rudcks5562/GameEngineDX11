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
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Idle.fbx");//fbx->memory
		converter->ExportAnimationData(L"Kachujin/Idle");
	}
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Run.fbx");//fbx->memory
		converter->ExportAnimationData(L"Kachujin/Run");
	}
	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		converter->ReadAssetFile(L"Kachujin/Slash.fbx");//fbx->memory
		converter->ExportAnimationData(L"Kachujin/Slash");
	}


}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
