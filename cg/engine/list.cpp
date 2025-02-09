//////////////
// #INCLUDE //
//////////////

// C/C++
#include <vector>
#include <iostream>

// Base class include
#include "list.h"

#include <GL/freeglut.h>

//GLM

ENG_API RenderList::RenderList(const std::string& name) : Object(name)
{
	//Empty Constructor
}

ENG_API RenderList::~RenderList()
{
	//Empty Deconstructor
}

void ENG_API RenderList::load_render_node(RenderNode* node)
{
	if (dynamic_cast<const Light*>(node->m_object) != nullptr)
		m_list.push_front(node);
	else
		m_list.push_back(node);
}

std::list<RenderNode*> ENG_API RenderList::get_render_list()
{
	return m_list;
}

void ENG_API RenderList::clear()
{
	m_list.clear();
}

void ENG_API RenderList::pass(Node* node, glm::mat4 parent_matrix)
{
	if (node == nullptr)			return;

	glm::mat4 matrix_world_coordinates = parent_matrix * node->get_matrix();

	//We accept only light or mesh (no camera) concrete type
	if (dynamic_cast<const Camera*>(node) == nullptr && (dynamic_cast<const Light*>(node) != nullptr || dynamic_cast<const Node*>(node) != nullptr))
		load_render_node(new RenderNode{node, matrix_world_coordinates});

	if(node->get_number_of_chilren() > 0)
	{
		for (auto* child : node->get_children())
			pass(child, matrix_world_coordinates);
	}
}

void ENG_API RenderList::render(glm::mat4 view)
{
	std::vector<RenderNode*> lights;
	unsigned int activated_lights = 0;

	for(auto i = m_list.begin(); i != m_list.end(); i++ )
	{
		if(dynamic_cast<Light*>((*i)->m_object) != nullptr) 
		{
			lights.push_back(*i);
		}
		else
		{
			break;
		}
	}

	int number_of_lights = lights.size();

	//remove the lights from the m_list
	for (auto i = lights.begin(); i != lights.end(); i++)
		m_list.remove(*i);


	std::vector<RenderNode*> solid_meshes;

	for(auto i = m_list.begin(); i != m_list.end(); i++ )
	{
		if(dynamic_cast<Mesh*>((*i)->m_object) != nullptr && dynamic_cast<Mesh*>((*i)->m_object)->get_material()->get_transparency() == 1.0f) 
		{
			solid_meshes.push_back(*i);
		}
	}

	int number_of_solid_meshes = solid_meshes.size();

	//remove the lights from the m_list
	for (auto i = solid_meshes.begin(); i != solid_meshes.end(); i++)
		m_list.remove(*i);


	for (auto &l : lights) {
		if (activated_lights < 8) {
			glEnable(GL_LIGHT0 + dynamic_cast<Light*>(l->m_object)->get_light_id());
			l->m_object->render(view * l->m_mat);
			activated_lights++;
		}
	}

	for (auto &l : solid_meshes) {
		l->m_object->render(view * l->m_mat);
	}




	for (auto& m : m_list) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		m->m_object->render(view * m->m_mat);
		glDisable(GL_BLEND);
	}



}