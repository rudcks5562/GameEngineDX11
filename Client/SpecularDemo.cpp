#include "pch.h"
#include "SpecularDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"

void SpecularDemo::Init()
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
		 _shader = make_shared<Shader>(L"Light_Specular.fx");
		//_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{

		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		//_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		//_obj->GetMeshRenderer()->SetTexture(texture);
	}
	 //obj2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{0.5f,0.f,2.f});
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		//_shader = make_shared<Shader>(L"GlobalTest.fx");
		//_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{

		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		//_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		//_obj2->GetMeshRenderer()->SetTexture(texture);
	}









	RENDER->Init(_shader);// scene
}

void SpecularDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	//
	Vec4 light{ 1.f };
	_shader->GetVector("LightSpecular")->SetFloatVector((float*)&light);
	Vec3 lightDir{ 1.f,0.f,0.f };
	lightDir.Normalize();
	_shader->GetVector("LightDir")->SetFloatVector((float*)&lightDir);

	{
		Vec4 material(1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&material);


		_obj->Update();
	}
	{
		Vec4 material(1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&material);

		_obj2->Update();
	}


}

void SpecularDemo::Render()
{

}
