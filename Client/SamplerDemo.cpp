#include "pch.h"
#include "SamplerDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"

void SamplerDemo::Init()
{
	_shader = make_shared<Shader>(L"Sampler.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();

	GeometryHelper::CreateGrid(_geometry,256,256); 


	// 쉐이더 경로 상대경로 아닌 깔끔히.

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	//geo = 정점 데이터 (구조체) 를 벡터로 들고있음
	// geohelp: 실제로 그리는데 보조하는 클래스.

	_camera = make_shared<GameObject>();// obj create
	_camera->GetOrAddTransform();//trs add
	_camera->AddComponent(make_shared<Camera>());// component add
	_camera->AddComponent(make_shared<CameraScript>());// sc add

	_texture=RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");

	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -2.f));

}

void SamplerDemo::Update()
{

	_camera->Update();



}

void SamplerDemo::Render()
{

	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)& Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());


	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	enum ADDRESS_VALUE {
		ADDRESS_WRAP=0,
		ADDRESS_MIRROR=1,
		ADDRESS_CLAMP=2,
		ADDRESS_BORDER=3,
	};

	_shader->GetScalar("Address")->SetInt(ADDRESS_WRAP);

	DC->IASetVertexBuffers(0,1, _vertexBuffer->GetComPtr().GetAddressOf(),&stride,&offset);

	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);


	//_shader->Draw(0, 1, 3);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);

}
