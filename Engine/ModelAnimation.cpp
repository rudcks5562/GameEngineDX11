#include "pch.h"
#include "ModelAnimation.h"

shared_ptr<ModelKeyframe> ModelAnimation::GetKeyframe(const wstring& name)
{
	auto findIt = keyframes.find(name);
	if (findIt == keyframes.find(name)) {
		return nullptr ;
	}

	return findIt->second;



}
