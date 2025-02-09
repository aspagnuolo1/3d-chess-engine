//////////////
// #INCLUDE //
//////////////


	// Camera.h include
	#include "ortoCamera.h"

	//GLM
	#include <glm/gtc/type_ptr.hpp>


/////////////
// CLASSES //
/////////////

ENG_API OrthographicCamera::OrthographicCamera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height) :
	Camera(name,cords,width,height,-1.0f, -1.0f)
{
	/*
	glm::ortho signature -->
		glm::mat4 glm::ortho(
			float left, float right,
			float bottom, float top,
			float zNear, float zFar);
	*/ 
	m_properties = glm::ortho(0.0f, (float) width, 0.0f, (float)height, -1.0f, 1.0f );
}

void ENG_API OrthographicCamera::render(glm::mat4 model_view)
{
	// Empty method for now
}

void ENG_API OrthographicCamera::update_window_size(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_properties = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}