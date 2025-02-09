#pragma once

//////////////
// #INCLUDE //
//////////////

	// C/C++
	#include <string>

	// Main library include
	#include "lib.h"

	//GLM
	#include <glm/glm.hpp>


/**
 * \class Object
 * \brief Base class used by all the derived classes.
 *
 * This class provides basic functionality such as setting an object's name, enforcing required API methods (e.g., `render()`), 
 * and assigning a unique identifier to each object instance. It serves as the base for all derived classes.
 */
class ENG_API Object {
public:
    /**
     * \brief Constructor
     *
     * Initializes an object with the specified name and assigns a unique identifier.
     *
     * \param name The name of the object. It's a string value.
     */
    Object(const std::string& name);

    /**
     * \brief Destructor
     *
     * A pure virtual destructor, making Object an abstract class. Derived classes must implement their own destructors.
     */
    virtual ~Object() = 0;

    /**
     * \brief Sets the object's name.
     *
     * Updates the name of the object to the specified value.
     *
     * \param name The new name of the object. It's a string value.
     */
    void set_object_name(const std::string& name);

    /**
     * \brief Gets the object's name.
     *
     * Retrieves the current name of the object.
     *
     * \return The name of the object as a string.
     */
    const std::string get_object_name();

    /**
     * \brief Gets the object's unique identifier.
     *
     * Retrieves the unique identifier assigned to the object.
     *
     * \return The object's unique identifier as an unsigned integer.
     */
    const unsigned int get_object_id();

    /**
     * \brief Renders the object.
     *
     * A pure virtual function that must be overridden by derived classes to define the rendering behavior.
     *
     * \param model_view A matrix expressing the Model-View transformation.
     */
    void virtual render(glm::mat4 model_view) = 0;

protected:
    /**
     * \var m_id
     * \brief Unique object identifier.
     *
     * A member variable that stores the unique identifier assigned to the object. Identifiers start from 1 (0 is not a valid identifier).
     */
    unsigned int m_id;

    /**
     * \var m_name
     * \brief The name of the object.
     *
     * A member variable that stores the name of the object.
     */
    std::string m_name;

    /**
     * \var m_helper_id
     * \brief Static helper for generating unique object identifiers.
     *
     * A static member variable used to maintain a counter that ensures each object instance is assigned a unique identifier.
     */
    static unsigned int m_helper_id;
};

