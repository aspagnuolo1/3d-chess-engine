//////////////
// #INCLUDE //
//////////////


	// Object header file include
	#include "directionalLight.h"

	//FreeGLUT:
	#include <GL/freeglut.h>

	//GLM:
	#include <glm/gtc/type_ptr.hpp>

ENG_API DirectionalLight::DirectionalLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position) : Light(name,model_view,ambient,diffuse,specular), m_position{position}
{
	//Empty Constructor
}


void ENG_API DirectionalLight::render(glm::mat4 model_view)
{

	//Light position into worlds space
	glm::vec4 position = glm::vec4(m_position, 0.0f);

	glLoadMatrixf(glm::value_ptr(model_view));

	glLightfv(GL_LIGHT0 + m_light_id, GL_POSITION, glm::value_ptr(position));

	//Set Light Properties
	glLightfv(GL_LIGHT0 + m_light_id, GL_AMBIENT, glm::value_ptr(m_ambient));
	glLightfv(GL_LIGHT0 + m_light_id, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPECULAR, glm::value_ptr(m_specular));
}


glm::vec3 ENG_API DirectionalLight::get_position() const{
	return m_position;
}

void ENG_API DirectionalLight::set_position(glm::vec3 position)
{
	m_position = position;
}
