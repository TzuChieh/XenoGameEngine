#pragma once

#include "Core/Timer.h"

namespace ve
{

class GlfwTimer : public Timer
{
public:
	virtual float64 getCurrentTimeS() const override;
	virtual float64 getCurrentTimeMs() const override;
};

}