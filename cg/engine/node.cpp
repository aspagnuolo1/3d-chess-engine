//////////////
// #INCLUDE //
//////////////
	   #include <iostream>
// Object header file include
#include "node.h"


ENG_API Node::Node(const std::string& name, glm::mat4 model_view) :
	Object(name), m_model_view{ model_view }, m_parent{ nullptr }
{
	// Empty Constructor
}

ENG_API Node::~Node() {
	
	for (Node* child : m_children)
		delete child;
	m_children.clear();

}

void ENG_API Node::set_parent(Node* parent) {
	this->m_parent = parent;
	parent->add_child(this);
}

void ENG_API Node::add_child(Node* child) {
	child->m_parent = this;
	this->m_children.push_back(child);

}

void ENG_API Node::remove_child(Node* child) {

    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (child->m_id == (*it)->get_object_id()) {
            m_children.erase(it); // Erase the child using the iterator
            return;
        }
    }
	
}


const unsigned int ENG_API Node::get_number_of_chilren() {
	return this->m_children.size();
}


std::vector<Node*> ENG_API Node::get_children()
{
	return m_children;
}

const glm::mat4 ENG_API Node::get_matrix() {
	return this->m_model_view;
}

void ENG_API Node::set_matrix(glm::mat4 model_view) {
	this->m_model_view = model_view;
}

void Node::render(glm::mat4 model_view)
{
	// Empty method for now
}

// ?
const glm::mat4 ENG_API Node::get_final_matrix(){
	if (this->m_parent == nullptr) {
		// We are in the root, we have to return the final computation
		return this->m_model_view;
	}
	else {
		return this->m_model_view * this->m_parent->get_final_matrix();
	}
}
Node ENG_API *Node::find_by_id(const unsigned int& id)
{
	for (Node* child : this->m_children) {
		if (child && child->m_id == id) {
			return child;
		}
	}
	return nullptr;
}

std::vector<Node*> ENG_API Node::find_by_name(const std::string& name) {
	std::vector<Node*> matching_nodes;  
	for (Node* child : this->m_children) {
		if (child && child->m_name == name) { 
			matching_nodes.push_back(child);
		}
	}
	for (Node* child : this->m_children) {
		if (child) {
			for (Node* r : child->find_by_name(name)) {
				matching_nodes.push_back(r);
			}
		}
	}
	return matching_nodes;
}
