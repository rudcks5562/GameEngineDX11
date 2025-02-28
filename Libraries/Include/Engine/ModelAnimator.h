#pragma once
#include "Component.h"

class Model;

struct AnimTransform {

	using TransformArrayType = array<Matrix, MAX_MODEL_TRANSFORM>; 

	array<TransformArrayType, MAX_MODEL_KEYFRAMES> transforms;


};

class ModelAnimator : public Component
{
	using Super = Component;

public:
	ModelAnimator(shared_ptr<Shader> shader);
	~ModelAnimator();

	virtual void Update() override;

	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }

private:
	void CreateTexture();
	void CreateAnimationTransform(uint32 index);

private:
	vector<AnimTransform> _animTransforms;
	ComPtr<ID3D11Texture2D> _texture;// 텍스쳐에 담아서
	ComPtr<ID3D11ShaderResourceView> _srv;// 텍스쳐 넘기기용

private:
	shared_ptr<Shader> _shader;
	uint8 _pass = 0;
	shared_ptr<Model> _model;

private:
	KeyFrameDesc _keyframeDesc;


};

