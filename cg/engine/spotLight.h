#pragma once

//////////////
// #INCLUDE //
//////////////


// Base class include
#include "attenuationLight.h"

/**
 * \class SpotLight
 * \brief Represents a spotlight in the scene.
 *
 * SpotLight is a subclass of AttenuationLight that represents a light source emitting a cone-shaped beam of light.
 * It includes parameters for direction, attenuation, and cutoff angle, allowing fine control over the spotlight's behavior.
 */
class ENG_API SpotLight : public AttenuationLight {
public:
    /**
     * \brief Constructor for the SpotLight class.
     *
     * Initializes the spotlight with a name, model-view matrix, color values, direction, attenuation parameters, and a cutoff angle.
     *
     * \param name The name of the light.
     * \param model_view The model-view matrix.
     * \param ambient The ambient color of the light.
     * \param diffuse The diffuse color of the light.
     * \param specular The specular color of the light.
     * \param direction The direction vector of the spotlight.
     * \param constant_att The constant attenuation factor (default is 1.0f).
     * \param linear_att The linear attenuation factor (default is 0.0f).
     * \param quadratic_att The quadratic attenuation factor (default is 0.0f).
     * \param cutoff The cutoff angle of the spotlight in degrees (default is 15.0f).
     */
    SpotLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction, float constant_att = 1.0f, float linear_att = 0.0f, float quadratic_att = 0.0f, float cutoff = 15.0f);

    /**
     * \brief Renders the spotlight.
     *
     * This function overrides the render method from the AttenuationLight class to define the behavior of rendering a spotlight.
     *
     * \param model_view The model-view matrix used for rendering the light.
     */
    void virtual render(glm::mat4 model_view) override;

    /**
     * \brief Gets the direction of the spotlight.
     *
     * \return A 3D vector representing the direction of the spotlight.
     */
    glm::vec3 get_direction() const;

    /**
     * \brief Sets the direction of the spotlight.
     *
     * \param direction A 3D vector representing the new direction of the spotlight.
     */
    void set_direction(const glm::vec3& direction);

    /**
     * \brief Gets the cutoff angle of the spotlight.
     *
     * \return The cutoff angle of the spotlight in degrees.
     */
    float get_cutoff() const;

    /**
     * \brief Sets the cutoff angle of the spotlight.
     *
     * \param cutoff The new cutoff angle of the spotlight in degrees.
     */
    void set_cutoff(float cutoff);

protected:
    /**
     * \var m_direction
     * \brief The direction vector of the spotlight.
     *
     * m_direction defines the direction in which the spotlight is pointing. It is used to calculate the spotlight's effect on objects in the scene.
     */
    glm::vec3 m_direction;

    /**
     * \var m_cutoff
     * \brief The cutoff angle of the spotlight.
     *
     * m_cutoff defines the angle of the cone of light emitted by the spotlight. It is measured in degrees and determines the area illuminated by the spotlight.
     */
    float m_cutoff;
};
