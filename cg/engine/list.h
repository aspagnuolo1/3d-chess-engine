#pragma once

#include "object.h"
#include "node.h"
#include "light.h"
#include "mesh.h"
#include "camera.h"
#include <list>

/**
 * \struct RenderNode
 * \brief Structure that holds a node and its transformation matrix.
 *
 *
 * The RenderNode structure has two member variables:
 *  - m_node: a pointer to an Object. It represents the node to be rendered.
 *  - m_mat: a 4x4 matrix that represents the transformation of the node in world coordinates
 */
struct RenderNode
{
	Object* m_object;
	glm::mat4 m_mat;
};

/**
 * \class RenderList
 * \brief A class for storing and rendering a list of nodes.
 *
 * RenderList is a container for `RenderNode` structures, each representing an object (such as a mesh or light) and its transformation matrix.
 * It provides functionality to manage and render a list of objects (nodes) with their respective transformations in the world space.
 */
class ENG_API  RenderList : public Object
{
public:

    /**
     * \brief Constructor
     * \param name The name for the render list (default is "render_list").
     */
	RenderList(const std::string& name = "render_list");

    /**
     * \brief Destructor
     */
	~RenderList();

	/**
	 * \brief Copy constructor
	 *
	 * Deleted to prevent copying of RenderList instances.
	 */
	RenderList(const RenderList& o) = delete;

	/**
	 * \brief Move constructor
	 *
	 * Deleted to prevent moving of RenderList instances.
	 */
	RenderList(RenderList&& o) = delete;


	/**
	 * \brief Copy assignment operator
	 *
	 * Deleted to prevent assignment of RenderList instances.
	 */
	RenderList& operator=(const RenderList& o) = delete;

	/**
	 * \brief Move assignment operator
	 *
	 * Deleted to prevent move assignment of RenderList instances.
	 */
	RenderList& operator=(RenderList&& o) = delete;

    /**
     * \brief Adds nodes and their transformation matrices to the list.
     * 
     * This function recursively traverses the node hierarchy, calling the `pass()` method of child nodes. 
     * It multiplies the child's matrix by the parent’s matrix and adds the result to the render list.
     * 
     * \param node The root node in the hierarchy.
     * \param parent_matrix The parent node's final matrix in world coordinates.
     */
	void pass(Node* node, glm::mat4 parent_matrix);

	/**
     * \brief Renders all nodes in the current render list.
     * 
     * Iterates through all nodes in the list and calls their `render()` method, passing the camera view matrix.
     * 
     * \param view The inverse of the camera matrix.
     */
	void render(glm::mat4 view);

    /**
     * \brief Clears the render list.
     * 
     * This function removes all nodes from the render list and frees their memory.
     */
	void clear();

    /**
     * \brief Gets the current render list.
     * 
     * \return The list of nodes to be rendered.
     */
	std::list<RenderNode*> get_render_list();



protected:
    /**
     * \var m_list
     * \brief Contains the list of RenderNode objects.
     * 
     * This is the container for the render nodes (objects and their transformation matrices).
     */
	std::list<RenderNode*> m_list;

    /**
     * \brief Helper function to add RenderNode to the list.
     * 
     * If the node is a Light, it is added to the front of the list; otherwise, it's added to the back.
     * 
     * \param node The RenderNode to add to the list.
     */
	void load_render_node(RenderNode* node);

};
