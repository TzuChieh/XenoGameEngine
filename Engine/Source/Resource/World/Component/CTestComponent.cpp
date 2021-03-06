#include "CTestComponent.h"
#include "Core/Engine.h"
#include "Game/GameProgram.h"

#include <iostream>

using namespace ve;

CTestComponent::CTestComponent() : 
	m_message("Hi, I'm CTestComponent with default message")
{
	std::cout << "CTestComponent default ctor called" << std::endl;
}

CTestComponent::CTestComponent(const std::string& message) :
	m_message(message)
{
	std::cout << "CTestComponent set message ctor called" << std::endl;
}

CTestComponent::CTestComponent(const CTestComponent& other)
{
	m_message = other.m_message;

	std::cout << "CTestComponent copy ctor called" << std::endl;
}

CTestComponent::CTestComponent(CTestComponent&& other)
{
	m_message = std::move(other.m_message);

	std::cout << "CTestComponent move ctor called" << std::endl;
}

CTestComponent::~CTestComponent()
{
	std::cout << "CTestComponent dtor called" << std::endl;
}

ComponentTypeId CTestComponent::getTypeId()
{
	std::cout << "CTestComponent type ID: " << Component::getTypeId<CTestComponent>() << std::endl;
	return Component::getTypeId<CTestComponent>();
}

//CTestComponent& CTestComponent::operator = (CTestComponent left)
//{
//	std::swap(*this, left);
//	return *this;
//}

std::string CTestComponent::getMessage() const
{
	return m_message;
}

void CTestComponent::setMessage(const std::string& message)
{
	m_message = message;
}