//////////////
// #INCLUDE //
//////////////


	// Base class include
	#include "material.h"

	//GLM
	#include <glm/glm.hpp>

	#include <GL/freeglut.h>
	#include <glm/gtc/type_ptr.hpp>
	#include <iostream>

ENG_API Material::Material(const std::string& name, glm::vec4 emission, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess, 	float transparency) : Object(name), m_emission{emission}, m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess}, m_transparency{transparency},m_texture{nullptr}
{
	//Emtpy Cosntructor
}

ENG_API Material::~Material()
{
	if (m_texture != nullptr)
		delete m_texture;
}

void ENG_API Material::render(glm::mat4 model_view)
{
	if (m_texture != nullptr)
		m_texture->render(model_view);
		
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(m_emission, m_transparency)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(m_ambient, m_transparency)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(m_diffuse, m_transparency)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(m_specular, m_transparency)));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);


}

void ENG_API Material::set_texture(Texture* texture)
{
	m_texture = texture;
}

Texture ENG_API* Material::get_texture()
{
	return m_texture;
}

glm::vec3 ENG_API Material::get_emission()
{
	return m_emission;
}

glm::vec3 ENG_API Material::get_ambient()
{
	return m_ambient;
}

glm::vec3 ENG_API Material::get_diffuse()
{
	return m_diffuse;
}

glm::vec3 ENG_API Material::get_specular()
{
	return m_specular;
}

float ENG_API Material::get_shininess()
{
	return m_shininess;
}

void ENG_API Material::set_emission(const glm::vec3& emission) {
    m_emission = emission;
}

void ENG_API Material::set_ambient(const glm::vec3& ambient) {
    m_ambient = ambient;
}

void ENG_API Material::set_diffuse(const glm::vec3& diffuse) {
    m_diffuse = diffuse;
}

void ENG_API Material::set_specular(const glm::vec3& specular) {
    m_specular = specular;
}

void ENG_API Material::set_shininess(float shininess) {
    m_shininess = shininess;
}

float ENG_API Material::get_transparency(){
	return m_transparency;
}

void ENG_API Material::set_transparency(float transparency){
	m_transparency = transparency;
}