#pragma once

#include "Resource/World/Component/TComponentManagerActionListener.h"

namespace ve
{

class CTransform;

class TransformManagerActionListener : public TComponentManagerActionListener<CTransform>
{
public:
	TransformManagerActionListener();

	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CTransform>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CTransform>>& targetComponent) override;
};

}