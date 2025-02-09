//////////////
// #INCLUDE //
//////////////

// Object header file include
#include "light.h"

#include <stdexcept>
#include <GL/freeglut.h>

// It is always the case that --> GL_LIGHTi=GL_LIGHT0+i
//TODO: need to be specified the GL_LIGHT0 as static member field?


unsigned int ENG_API Light::m_helper_light_id = 0;

//GL_LIGHT0 defined as --> 0x4000

int ENG_API Light::m_max_lights = 0;

Light::Light(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Node(name, model_view), m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_light_id{ m_helper_light_id }
{
	if(m_helper_light_id==0)
	{
		glGetIntegerv(GL_MAX_LIGHTS, &m_max_lights);
	}
	else if(m_helper_light_id > size_t(m_max_lights - 1))
		throw std::runtime_error("Maximum number of possible lights reached!");

	m_helper_light_id++;

}

const unsigned int ENG_API& Light::get_light_id()
{
	return m_light_id;
}

glm::vec3 ENG_API Light::get_ambient() const {
    return m_ambient;
}

void ENG_API Light::set_ambient(const glm::vec3& ambient) {
    m_ambient = ambient;
}

glm::vec3 ENG_API Light::get_diffuse() const {
    return m_diffuse;
}

void ENG_API Light::set_diffuse(const glm::vec3& diffuse) {
    m_diffuse = diffuse;
}

glm::vec3 ENG_API Light::get_specular() const {
    return m_specular;
}

void ENG_API Light::set_specular(const glm::vec3& specular) {
    m_specular = specular;
}