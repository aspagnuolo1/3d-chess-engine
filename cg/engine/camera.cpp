//////////////
// #INCLUDE //
//////////////


// Camera.h include
#include "camera.h"

/////////////
// CLASSES //
/////////////

ENG_API Camera::Camera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height, float near, float far)
	: Node(name,cords),
	m_width{width},
	m_height{height},
	m_near{near},
	m_far{far}
{
	//Empty Constructor
}

unsigned int ENG_API Camera::get_width() const
{
	return m_width;
}

unsigned int ENG_API Camera::get_height() const
{
	return m_height;
}

float ENG_API Camera::get_far() const
{
	return m_far;
}

float ENG_API Camera::get_near() const
{
	return m_near;
}

void ENG_API Camera::set_height(unsigned int height)
{
	m_height = height;
}

void ENG_API Camera::set_width(unsigned int width)
{
	m_width = width;
}

void ENG_API Camera::set_near(float new_near)
{
	m_near = new_near;
}

void ENG_API Camera::set_far(float new_far)
{
	m_far = new_far;
}

glm::mat4 ENG_API Camera::get_properties() const
{
	return m_properties;
}



