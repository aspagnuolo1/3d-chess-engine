#pragma once

#include "node.h"

/**
 * \class Light
 * \brief Abstract class representing a light object in the scene.
 *
 * Light is an abstract class that represents a light object in the scene. It is derived from the Node class and has additional member variables and functions specific to light objects. 
 * It has a light type, an ID, and color values for ambient, diffuse, and specular lighting.
 *
 * \note This class is meant to be subclassed and should not be instantiated directly.
 */
class ENG_API Light : public Node {

public:
    /**
     * \brief Pure virtual function to render the light.
     *
     * This function is a pure virtual function that must be implemented by subclasses to define how the light is rendered.
     * 
     * \param model_view The model-view matrix used for rendering the light.
     */
    virtual void render(glm::mat4 model_view) = 0;

    /**
     * \brief Constructor for the Light class.
     *
     * Initializes the light with a name, model-view matrix, and color values for ambient, diffuse, and specular components.
     *
     * \param name The name of the light.
     * \param model_view The model-view matrix.
     * \param ambient The ambient color of the light.
     * \param diffuse The diffuse color of the light.
     * \param specular The specular color of the light.
     */
    Light(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    /**
     * \brief Gets the unique ID of the light.
     *
     * \return The ID of the light.
     */
    const unsigned int& get_light_id();

    /**
     * \brief Gets the ambient color of the light.
     *
     * \return A 3D vector representing the ambient color.
     */
    glm::vec3 get_ambient() const;

    /**
     * \brief Sets the ambient color of the light.
     *
     * \param ambient The new ambient color as a 3D vector.
     */
    void set_ambient(const glm::vec3& ambient);

    /**
     * \brief Gets the diffuse color of the light.
     *
     * \return A 3D vector representing the diffuse color.
     */
    glm::vec3 get_diffuse() const;

    /**
     * \brief Sets the diffuse color of the light.
     *
     * \param diffuse The new diffuse color as a 3D vector.
     */
    void set_diffuse(const glm::vec3& diffuse);

    /**
     * \brief Gets the specular color of the light.
     *
     * \return A 3D vector representing the specular color.
     */
    glm::vec3 get_specular() const;

    /**
     * \brief Sets the specular color of the light.
     *
     * \param specular The new specular color as a 3D vector.
     */
    void set_specular(const glm::vec3& specular);

protected:
    /**
     * \var m_helper_light_id
     * \brief The incremental value for the light ID.
     *
     * m_helper_light_id is a static variable that holds the incremental value for the light ID. It is used to generate unique IDs for each light object by adding it to the base value.
     */
    static unsigned int m_helper_light_id;

    /**
     * \var m_max_lights
     * \brief The maximum number of lights that OpenGL can manage.
     *
     * m_max_lights is a static variable that holds the maximum number of lights that OpenGL can manage. It is used to ensure that the number of lights in the scene does not exceed this limit.
     */
    static int m_max_lights;

    /**
     * \var m_light_id
     * \brief The ID of the light.
     *
     * m_light_id is a member variable that holds the ID of the light. It is a unique identifier for the light object and is used to identify it in the scene.
     */
    unsigned int m_light_id;

    /**
     * \var m_ambient
     * \brief The ambient color of the light.
     *
     * m_ambient is a member variable that holds the ambient color of the light. It is a 3D vector with the red, green, and blue values.
     */
    glm::vec3 m_ambient;

    /**
     * \var m_diffuse
     * \brief The diffuse color of the light.
     *
     * m_diffuse is a member variable that holds the diffuse color of the light. It is a 3D vector with the red, green, and blue values.
     */
    glm::vec3 m_diffuse;

    /**
     * \var m_specular
     * \brief The specular color of the light.
     *
     * m_specular is a member variable that holds the specular color of the light. It is a 3D vector with the red, green, and blue values.
     */
    glm::vec3 m_specular;
};
