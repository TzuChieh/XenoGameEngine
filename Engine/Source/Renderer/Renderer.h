#pragma once

namespace xe
{

class Renderer
{
	
	friend class Engine;

public:
	virtual void render() = 0;

private:
	virtual bool init() = 0;
	virtual void decompose() = 0;
};

}