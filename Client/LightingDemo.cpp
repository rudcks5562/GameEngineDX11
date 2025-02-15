#include "pch.h"
#include "LightingDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"

void LightingDemo::Init()
{
	RESOURCES->Init();
	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f,0.f,-10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		 _shader = make_shared<Shader>(L"Lighting.fx");
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{

		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}
	 //obj2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{0.5f,0.f,2.f});
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		//_shader = make_shared<Shader>(L"GlobalTest.fx");
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{

		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}









	RENDER->Init(_shader);// scene
}

void LightingDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		RENDER->PushLightData(lightDesc);
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.2f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		//desc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

		RENDER->PushMaterialData(desc);
		_obj->Update();
	}
	
	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(1.f);
		//desc.specular = Color(0.5f, 0.5f, 0.5f, 1.f);
		//desc.emissive = Color(1.f, 0.f, 0.f, 1.f);

		RENDER->PushMaterialData(desc);
		_obj2->Update();
	}	


}

void LightingDemo::Render()
{

}
