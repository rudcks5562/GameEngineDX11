#pragma once

#include "IExecute.h"
#include "Geometry.h"
class ConstBufferDemo : public IExecute
{

public:

	// IExecute을(를) 통해 상속됨
	void Init() override; 

	void Update() override;

	void Render() override;

	shared_ptr<Shader> _shader;
	//vector<VertexData> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<Geometry<VertexColorData>> _geometry;

	Vec3 _translation = Vec3(0.f, 0.f, 0.f);


	Matrix _world= Matrix::Identity;
	Matrix _view= Matrix::Identity;
	Matrix _projection= Matrix::Identity;

};

