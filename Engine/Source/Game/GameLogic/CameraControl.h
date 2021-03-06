#pragma once

#include "GameLogic.h"

namespace ve
{

class Input;
class CTransform;

class CameraControl : public GameLogic
{
public:
	virtual ~CameraControl() override;

	virtual void execute(float32 deltaS, World* world, const EngineProxy& engineProxy) override;

private:
	void processCameraTranslation(const Input* input, CTransform* transform, const float32 deltaS) const;
	void processCameraRotation(const Input* input, CTransform* transform, const float32 deltaS) const;
};

}