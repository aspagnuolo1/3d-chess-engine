//////////////
// #INCLUDE //
//////////////

	// Base class include
	#include "spotLight.h"

	//FreeGLUT:
	#include <GL/freeglut.h>

	//GLM:
	#include <glm/glm.hpp>
	#include <glm/gtc/type_ptr.hpp>
	#include <iostream>



ENG_API SpotLight::SpotLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction, float constant_att, float linear_att, float quadratic_att, float cutoff) : AttenuationLight(name, model_view, ambient, diffuse, specular, constant_att, linear_att, quadratic_att), m_direction{ direction },m_cutoff{cutoff}
{
	//empty constructor

}

void ENG_API SpotLight::render(glm::mat4 model_view)
{
	//Light position into worlds space
	glm::vec4 position = glm::vec4(0.0f,0.0f,0.0f, 1.0f);

	glLoadMatrixf(glm::value_ptr(model_view));

	//Set the OpenGL light position and direction
	glLightfv(GL_LIGHT0 + m_light_id, GL_POSITION, glm::value_ptr(position));
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPOT_CUTOFF, &m_cutoff);
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPOT_DIRECTION, glm::value_ptr(m_direction));

	//Set Attenuation Properties
	glLightf(GL_LIGHT0 + m_light_id, GL_CONSTANT_ATTENUATION, m_constant_attenuation);			// default 1
	glLightf(GL_LIGHT0 + m_light_id, GL_LINEAR_ATTENUATION, m_linear_attenuation);				// default 0
	glLightf(GL_LIGHT0 + m_light_id, GL_QUADRATIC_ATTENUATION, m_quadratic_attenuation);		// default 0

	//Set Light Properties
	glLightfv(GL_LIGHT0 + m_light_id, GL_AMBIENT, glm::value_ptr(m_ambient));
	glLightfv(GL_LIGHT0 + m_light_id, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glLightfv(GL_LIGHT0 + m_light_id, GL_SPECULAR, glm::value_ptr(m_specular));
	
}

glm::vec3 ENG_API SpotLight::get_direction() const
{
    return m_direction;
}

void ENG_API SpotLight::set_direction(const glm::vec3& direction)
{
    m_direction = direction;
}

float ENG_API SpotLight::get_cutoff() const
{
    return m_cutoff;
}

void ENG_API SpotLight::set_cutoff(float cutoff)
{
    m_cutoff = cutoff;
}