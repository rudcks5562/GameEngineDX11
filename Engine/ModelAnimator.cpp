#include "pch.h"
#include "ModelAnimator.h"
#include "Material.h"
#include "ModelMesh.h"
#include "Model.h"
#include "ModelAnimation.h"



ModelAnimator::ModelAnimator(shared_ptr<Shader> shader):
	Super(ComponentType::Animator),_shader(shader)
{


}

ModelAnimator::~ModelAnimator()
{

}

void ModelAnimator::Update()
{
	if (_model == nullptr)
		return;
	if (_texture == nullptr)
		CreateTexture();
	
	// anim update
	ImGui::InputInt("AnimIndex", &_keyframeDesc.animIndex);
	_keyframeDesc.animIndex %= _model->GetAnimationCount();
	ImGui::InputInt("CurFrame", (int*)&_keyframeDesc.currFrame);
	_keyframeDesc.currFrame %= _model->GetAnimationByIndex(_keyframeDesc.animIndex)->frameCount;

	RENDER->PushKeyFrameData(_keyframeDesc);

	//srv 로 정보전달
	_shader->GetSRV("TransformMap")->SetResource(_srv.Get());

	
	//bones
	BoneDesc boneDesc;
	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++) {

		shared_ptr<ModelBone>bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;

	}
	RENDER->PushBoneData(boneDesc);

	// transform
	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		// bone index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
}

void ModelAnimator::SetModel(shared_ptr<Model> model)
{

	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials) {
		material->SetShader(_shader);
	}
}

void ModelAnimator::CreateTexture()
{
	if (_model->GetAnimationCount() == 0) {
		return;
	}
	_animTransforms.resize(_model->GetAnimationCount());

	for (uint32 i = 0; i < _model->GetAnimationCount(); i++) {
		CreateAnimationTransform(i);
	}

	// Creature Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORM * 4;
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = _model->GetAnimationCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 16바이트
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		const uint32 dataSize = MAX_MODEL_TRANSFORM * sizeof(Matrix);// 가로층
		const uint32 pageSize = dataSize * MAX_MODEL_KEYFRAMES;//층수
		void* mallocPtr = ::malloc(pageSize * _model->GetAnimationCount());

		// 파편화된 데이터를 조립한다.
		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			uint32 startOffset = c * pageSize;

			BYTE* pageStartPtr = reinterpret_cast<BYTE*>(mallocPtr) + startOffset;

			for (uint32 f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* ptr = pageStartPtr + dataSize * f;
				::memcpy(ptr, _animTransforms[c].transforms[f].data(), dataSize);
			}
		}

		// 리소스 만들기
		vector<D3D11_SUBRESOURCE_DATA> subResources(_model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			void* ptr = (BYTE*)mallocPtr + c * pageSize;
			subResources[c].pSysMem = ptr;
			subResources[c].SysMemPitch = dataSize;
			subResources[c].SysMemSlicePitch = pageSize;
		}

		HRESULT hr = DEVICE->CreateTexture2D(&desc, subResources.data(), _texture.GetAddressOf());
		CHECK(hr);

		::free(mallocPtr);
	}

	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = _model->GetAnimationCount();

		HRESULT hr = DEVICE->CreateShaderResourceView(_texture.Get(), &desc, _srv.GetAddressOf());
		CHECK(hr);
	}


}

void ModelAnimator::CreateAnimationTransform(uint32 index)
{

	vector<Matrix> tempAnimBoneTransforms(MAX_MODEL_TRANSFORM,Matrix::Identity);

	shared_ptr<ModelAnimation> animation=_model->GetAnimationByIndex(index); // 작업할 애니메이션

	for (uint32 f = 0; f < animation->frameCount; f++) {

		for (uint32 b = 0; b < _model->GetBoneCount(); b++) {//2차배열

			shared_ptr<ModelBone> bone = _model->GetBoneByIndex(b);

			Matrix	matAnimation;

			shared_ptr<ModelKeyframe> frame= animation->GetKeyframe(bone->name);

			if (frame != nullptr) {
				ModelKeyframeData& data = frame->transforms[f];
				Matrix S, R, T;
				S = Matrix::CreateScale(data.scale.x, data.scale.y, data.scale.z);
				R = Matrix::CreateFromQuaternion(data.rotation);
				T = Matrix::CreateTranslation(data.translation.x, data.translation.y, data.translation.z);

				matAnimation = S * R * T;

			}
			else { 
				matAnimation = Matrix::Identity;
			}
			// 티포즈일때의 상황

			Matrix toRootMatrix = bone->transform;//글로벌
			Matrix invGlobal = toRootMatrix.Invert();// 역행렬

			int32 parentIndex = bone->parentIndex;

			Matrix matParent = Matrix::Identity;
			if (parentIndex >= 0) {// 부모존재
				matParent = tempAnimBoneTransforms[parentIndex];

			}
			tempAnimBoneTransforms[b] = matAnimation * matParent;// 애니메이션 적용하면서 글로벌화


			_animTransforms[index].transforms[f][b] = invGlobal * tempAnimBoneTransforms[b];//상대좌표로 재수정

		}
	}
}
