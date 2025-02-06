#pragma once

#include "IExecute.h"

class triangleDemo : public IExecute
{

public:





	// IExecute을(를) 통해 상속됨
	void Init() override;

	void Update() override;

	void Render() override;

};

