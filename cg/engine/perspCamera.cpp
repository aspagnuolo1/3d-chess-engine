//////////////
// #INCLUDE //
//////////////


	// Header File include
	#include "perspCamera.h"

	//GLM
	#include <glm/gtc/type_ptr.hpp>

/////////////
// CLASSES //
/////////////

ENG_API PerspectiveCamera::PerspectiveCamera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height, float near, float far, float fov) :
	Camera(name,cords,width,height,near,far),
	m_fov{fov}
{
	/**
		glm::perspective signature --> glm::mat4 perspective(float fovy, float aspect, float zNear, float zFar);
	
	*/
	m_properties = glm::perspective(glm::radians(fov), (float)width/(float)height, near, far);
}
void ENG_API PerspectiveCamera::render(glm::mat4 model_view)
{
	// Empty method for now
}


void ENG_API PerspectiveCamera::update_window_size(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;


	m_properties = glm::perspective(glm::radians(m_fov), (float)width / (float)height, m_near, m_far);
}

void ENG_API PerspectiveCamera::set_properties(glm::mat4 properties)
{
	m_properties = properties;
}

glm::mat4 ENG_API PerspectiveCamera::get_inverse_camera()
{
	return glm::inverse(m_model_view);
}

float ENG_API PerspectiveCamera::get_fov() const{
	return m_fov;
}

void ENG_API PerspectiveCamera::set_fov(float fov){
	m_fov = fov;
}