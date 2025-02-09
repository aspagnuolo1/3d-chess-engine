//////////////
// #INCLUDE //
//////////////


	// Object header file include
	#include "omnidirectionalLight.h"

	//FreeGLUT:
	#include <GL/freeglut.h>

	//GLM:
	#include <glm/glm.hpp>
	#include <glm/gtc/type_ptr.hpp>


ENG_API OmniDirectionalLight::OmniDirectionalLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant_att, float linear_att, float quadratic_att) : AttenuationLight(name, model_view, ambient, diffuse, specular, constant_att, linear_att, quadratic_att)
{
}

void ENG_API OmniDirectionalLight::render(glm::mat4 model_view)
{
	glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	float cutoff = 180.0f;		//Special Value

	glLoadMatrixf(glm::value_ptr(model_view));

	//Set the OpenGL light position (direction)
	glLightfv(GL_LIGHT0 + m_light_id, GL_POSITION, glm::value_ptr(position));
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPOT_CUTOFF, &cutoff);

	//Set Attenuation Properties
	glLightf(GL_LIGHT0 + m_light_id, GL_CONSTANT_ATTENUATION, m_constant_attenuation);			// default 1
	glLightf(GL_LIGHT0 + m_light_id, GL_LINEAR_ATTENUATION, m_linear_attenuation);				// default 0
	glLightf(GL_LIGHT0 + m_light_id, GL_QUADRATIC_ATTENUATION, m_quadratic_attenuation);		// default 0

	//Set Light Properties
	glLightfv(GL_LIGHT0 + m_light_id, GL_AMBIENT, glm::value_ptr(m_ambient));
	glLightfv(GL_LIGHT0 + m_light_id, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPECULAR, glm::value_ptr(m_specular));

	
}