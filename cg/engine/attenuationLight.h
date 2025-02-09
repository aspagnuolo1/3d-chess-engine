#pragma once

//////////////
// #INCLUDE //
//////////////


// Base class include
#include "light.h"

/**
 * \class AttenuationLight
 * \brief Represents a light with attenuation properties.
 *
 * AttenuationLight is a subclass of Light that includes additional properties for controlling the attenuation of light intensity over distance.
 * It introduces parameters for constant, linear, and quadratic attenuation, making it suitable for simulating real-world light falloff.
 */
class ENG_API AttenuationLight : public Light {
public:
    /**
     * \brief Pure virtual function to render the attenuation light.
     *
     * This function must be implemented by subclasses to define how the light with attenuation is rendered.
     * 
     * \param model_view The model-view matrix used for rendering the light.
     */
    void virtual render(glm::mat4 model_view) override = 0;

    /**
     * \brief Constructor for the AttenuationLight class.
     *
     * Initializes the attenuation light with a name, model-view matrix, color values, and attenuation parameters.
     *
     * \param name The name of the light.
     * \param model_view The model-view matrix.
     * \param ambient The ambient color of the light.
     * \param diffuse The diffuse color of the light.
     * \param specular The specular color of the light.
     * \param constant_att The constant attenuation factor.
     * \param linear_att The linear attenuation factor.
     * \param quadratic_att The quadratic attenuation factor.
     */
    AttenuationLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant_att, float linear_att, float quadratic_att);

    /**
     * \brief Gets the constant attenuation factor.
     *
     * \return The constant attenuation factor.
     */
    float get_constant_attenuation() const;

    /**
     * \brief Sets the constant attenuation factor.
     *
     * \param constant_att The new constant attenuation factor.
     */
    void set_constant_attenuation(float constant_att);

    /**
     * \brief Gets the linear attenuation factor.
     *
     * \return The linear attenuation factor.
     */
    float get_linear_attenuation() const;

    /**
     * \brief Sets the linear attenuation factor.
     *
     * \param linear_att The new linear attenuation factor.
     */
    void set_linear_attenuation(float linear_att);

    /**
     * \brief Gets the quadratic attenuation factor.
     *
     * \return The quadratic attenuation factor.
     */
    float get_quadratic_attenuation() const;

    /**
     * \brief Sets the quadratic attenuation factor.
     *
     * \param quadratic_att The new quadratic attenuation factor.
     */
    void set_quadratic_attenuation(float quadratic_att);

protected:
    /**
     * \var m_constant_attenuation
     * \brief The constant attenuation factor.
     *
     * m_constant_attenuation represents the constant component of the light's attenuation. It defines a base intensity unaffected by distance.
     */
    float m_constant_attenuation;

    /**
     * \var m_linear_attenuation
     * \brief The linear attenuation factor.
     *
     * m_linear_attenuation defines the linear component of the light's attenuation, reducing intensity proportionally to the distance from the light source.
     */
    float m_linear_attenuation;

    /**
     * \var m_quadratic_attenuation
     * \brief The quadratic attenuation factor.
     *
     * m_quadratic_attenuation defines the quadratic component of the light's attenuation, reducing intensity with the square of the distance from the light source.
     */
    float m_quadratic_attenuation;
};
