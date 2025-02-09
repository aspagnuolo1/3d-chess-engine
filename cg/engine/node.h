#pragma once


//////////////
// #INCLUDE //
//////////////

// C/C++
#include <vector>

// Base class include
#include "object.h"



/**
 * \class Node
 * \brief Class that derives from Object.
 *
 * The Node class represents a hierarchical structure in a scene graph, allowing for the management of transformations, 
 * parent-child relationships, and final world coordinate computations. It extends the functionality of the Object class 
 * by providing features specific to nodes in a scene graph.
 */
class ENG_API Node : public Object{

public:

	/**
     * \brief Constructor
     *
     * Initializes the node with a name and an initial position relative to the parent node.
     *
     * \param name The name of the node.
     * \param model_view The initial transformation matrix in object coordinates.
     */

	Node(const std::string& name, glm::mat4 model_view);

	/**
	* \brief Deconstructor
	*
	* \param Node class decostructor
	*/
	virtual ~Node();

	/**
	 * \brief Copy constructor
	 *
	 * Deleted to prevent copying of Node instances.
	 */
	Node(const Node& o) = delete;

	/**
	 * \brief Move constructor
	 *
	 * Deleted to prevent moving of Node instances.
	 */
	Node(Node&& o) = delete;


	/**
	 * \brief Copy assignment operator
	 *
	 * Deleted to prevent assignment of Node instances.
	 */
	Node& operator=(const Node& o) = delete;

	/**
	 * \brief Move assignment operator
	 *
	 * Deleted to prevent move assignment of Node instances.
	 */
	Node& operator=(Node&& o) = delete;

	/**
	* \brief Inherited function used to render the object. It's a virtual method, must be override by its derived classes.
	*
	* \param model_view Matrix expressing the Model-View matrix.
	* \return No value returned.
	*/
	void virtual render(glm::mat4 model_view);

	/**
	* \brief Method for retrieving the node's final matrix in World Coordinates.
	*
	* \return The node matrix in World Coordinates.
	* \param No parameters.
	*/
	const glm::mat4 get_final_matrix();

	/**
	* \brief Method for finding a child with its id.
	*
	* \return The child of type Node* or NULL if not found.
	* \param name The id of the child to be found.
	*/
	Node* find_by_id(const unsigned int& id);

	/**
	* \brief Method for finding children with their name.
	*
	* \return An std::vector of children of type Node*.
	* \param name The name of the children to be found.
	*/
	std::vector<Node*> find_by_name(const std::string& name);

	/**
	* \brief Method for setting the node's parent.
	*
	* \return No value returned.
	* \param parent The Node* parent to be set.
	*/
	void set_parent(Node* parent);

	/**
	* \brief Method for adding a child.
	*
	* \return No value returned.
	* \param child The Node* child to be added.
	*/
	void add_child(Node* child);

	/**
	* \brief Method for removing a child.
	*
	* \return No value returned.
	* \param child The Node* child to be removed.
	*/
	void remove_child(Node* child);

	/**
	* \brief Method for retrieveing the number of children of the node.
	*
	* \return The number of the node's children.
	* \param No parameters.
	*/
	const unsigned int get_number_of_chilren();

	std::vector<Node*> get_children();

	/**
	* \brief Setter method for the node's model view matrix.
	*
	* \return No value returned.
	* \param obj_mat The model view matrix to be set.
	*/
	void set_matrix(glm::mat4 model_view);
	
	void remove_all_children() {

    	m_children.clear();
	}

	/**
	* \brief Getter method for the node's model view matrix.
	*
	* \return The node's model view matrix.
	* \param No parameters.
	*/
	const glm::mat4 get_matrix();

protected:
	/**
	* \var m_parent
	* \brief Current parent node.
	*
	* Member variable that stores the node's parent.
	*/
	Node* m_parent;

	/**
	* \var m_children
	* \brief Current children nodes.
	*
	* Member variable that stores the node's children.
	*/
	std::vector<Node*> m_children;

	/**
	* \var m_obj_cords
	* \brief The node's matrix in Object Coordinates.
	*
	* Member variable that stores the node's children.
	*/
	glm::mat4 m_model_view;
};

