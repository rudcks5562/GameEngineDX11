#pragma once

class VertexBuffer;

struct InstancingData {
	Matrix world;

};
#define MAX_MESH_INSTANCE 500

class InstancingBuffer
{
public:
	InstancingBuffer();
	~InstancingBuffer();

public:
	void ClearData();
	void AddData(InstancingData& data);
	void PushData();

	//ID

public:
	uint32 GetCount() { return static_cast<uint32>(_data.size()); }
	shared_ptr<VertexBuffer> GetBuffer() { return _instanceBuffer; }
 private:
	//uint 64 _instanceId = 0;
	shared_ptr<VertexBuffer> _instanceBuffer;
	uint32 _maxCount = 0;
	vector<InstancingData> _data;

private:
		void CreateBuffer(uint32 maxCount = MAX_MESH_INSTANCE);





};

