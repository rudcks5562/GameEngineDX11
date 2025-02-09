#include "pch.h"
#include "HeightMapDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"Sampler.fx");
	_texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\Terrain\\height.png");
	_heightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Textures\\veigar.jpg");

	const int32 width = _heightMap->GetSize().x;
	const int32 height = _heightMap->GetSize().y;

	const DirectX::ScratchImage& info = _heightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();// 파일포맷을 체크한 후 해야함.원래
	//(자료형이 달라진다 . )



	_geometry = make_shared<Geometry<VertexTextureData>>();

	GeometryHelper::CreateGrid(_geometry,width,height); 

	{
		vector<VertexTextureData>& v= const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());
	//const delete
		for (int32 z = 0; z < height; z++) {

			for (int32 x = 0; x < width; x++) {

				int32 idx = width * z + x;//1차배열 변환시 인덱스
				uint8 height = pixelBuffer[idx] / 255.f * 25.f;// 보정?
				v[idx].position.y = height;

			}
		}
	
	}


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


	_camera->GetTransform()->SetPosition(Vec3(0.f, 5.f, 0.f));
	_camera->GetTransform()->SetRotation(Vec3(25.f, 0.f, -2.f));
}

void HeightMapDemo::Update()
{

	_camera->Update();



}

void HeightMapDemo::Render()
{

	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)& Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());


	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	/*
		enum ADDRESS_VALUE { // - samplerstate
		ADDRESS_WRAP=0,
		ADDRESS_MIRROR=1,
		ADDRESS_CLAMP=2,
		ADDRESS_BORDER=3,
	};
	*/


	//_shader->GetScalar("Address")->SetInt(ADDRESS_WRAP);

	DC->IASetVertexBuffers(0,1, _vertexBuffer->GetComPtr().GetAddressOf(),&stride,&offset);

	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);


	//_shader->Draw(0, 1, 3);
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);

}
