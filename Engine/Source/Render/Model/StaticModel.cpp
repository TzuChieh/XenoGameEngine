#include "StaticModel.h"

using namespace ve;

StaticModel::StaticModel() : 
	m_position(0, 0, 0), 
	m_orientation(0, 0, 0, 1)
{

}

StaticModel::StaticModel(const std::string& fullFilename) :
	m_fullFilename(fullFilename)
{

}

const std::string& StaticModel::getFullFilename() const
{
	return m_fullFilename;
}

const Vector3f& StaticModel::getPosition() const
{
	return m_position;
}

void StaticModel::setPosition(const Vector3f& position)
{
	setPosition(position.x, position.y, position.z);
}

void StaticModel::setPosition(const float32 x, const float32 y, const float32 z)
{
	m_position.set(x, y, z);
}

const Quaternion& StaticModel::getOrientation() const
{
	return m_orientation;
}

void StaticModel::setOrientation(const Vector3f& normalizedAxis, const float32 degree)
{
	m_orientation.setRot(normalizedAxis, degree / 180.0f * 3.14159365f);
}