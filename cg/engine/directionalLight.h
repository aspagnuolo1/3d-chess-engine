#pragma once

//////////////
// #INCLUDE //
//////////////


// Base class include
#include "light.h"

/**
 * \class DirectionalLight
 * \brief Represents a directional light source in the scene.
 *
 * DirectionalLight is a subclass of Light that represents a light source with a fixed direction. Unlike point or spotlights, a directional light illuminates objects uniformly, simulating light coming from an infinitely distant source like the sun.
 */
class ENG_API DirectionalLight : public Light {
public:
    /**
     * \brief Renders the directional light.
     *
     * This function overrides the render method from the Light class to define the behavior of rendering a directional light.
     * 
     * \param model_view The model-view matrix used for rendering the light.
     */
    void virtual render(glm::mat4 model_view) override;

    /**
     * \brief Constructor for the DirectionalLight class.
     *
     * Initializes the directional light with a name, model-view matrix, color values, and position.
     *
     * \param name The name of the light.
     * \param model_view The model-view matrix.
     * \param ambient The ambient color of the light.
     * \param diffuse The diffuse color of the light.
     * \param specular The specular color of the light.
     * \param position The position vector, which represents the direction of the light.
     */
    DirectionalLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);

    /**
     * \brief Gets the position (direction) of the directional light.
     *
     * \return A 3D vector representing the direction of the light.
     */
    glm::vec3 get_position() const;

    /**
     * \brief Sets the position (direction) of the directional light.
     *
     * \param position A 3D vector representing the new direction of the light.
     */
    void set_position(glm::vec3 position);

protected:
    /**
     * \var m_position
     * \brief The position vector of the light, representing its direction.
     *
     * m_position represents the direction of the directional light. Unlike point lights, this vector determines the light's direction rather than a specific position in space.
     */
    glm::vec3 m_position;
};
