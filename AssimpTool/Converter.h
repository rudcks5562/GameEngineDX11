#pragma once
class Converter
{
public:

	Converter();
	~Converter();
public:
	void ReadAssetFile(wstring file);

private:
	wstring _assetPath = L"../Resources/Assets/";
	wstring _modelPath = L"../Resources/Models/";
	wstring _texturePath = L"../Resources/Textures/";




private:
	shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene;
};

