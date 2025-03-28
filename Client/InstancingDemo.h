#pragma once
class InstancingDemo : public IExecute
{

public:
	void Init() override;
	void Update() override;
	void Render() override;



private:
	shared_ptr<Shader> _shader;
	shared_ptr<GameObject> _camera;
	vector<shared_ptr<GameObject>> _objs;



private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
	vector<Matrix> _worlds;
	shared_ptr<VertexBuffer> _instanceBuffer;
};

