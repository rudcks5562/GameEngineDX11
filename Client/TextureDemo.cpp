#include "pch.h"
#include "TextureDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"

void TextureDemo::Init()
{
	_shader = make_shared<Shader>(L"Texture.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();

	GeometryHelper::CreateQuad(_geometry); 


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

	


}

void TextureDemo::Update()
{

	_camera->Update();



}

void TextureDemo::Render()
{

	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)& Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);



	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();


	DC->IASetVertexBuffers(0,1, _vertexBuffer->GetComPtr().GetAddressOf(),&stride,&offset);

	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);


	//_shader->Draw(0, 1, 3);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);

}
