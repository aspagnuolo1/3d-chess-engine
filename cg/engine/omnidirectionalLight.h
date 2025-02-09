#pragma once

//////////////
// #INCLUDE //
//////////////

// Base class include
#include "attenuationLight.h"

/**
 * \class OmniDirectionalLight
 * \brief Represents an omnidirectional light source in the scene.
 *
 * OmniDirectionalLight is a subclass of AttenuationLight that represents a point light source emitting light in all directions.
 * It includes attenuation factors to simulate realistic light falloff over distance.
 */
class ENG_API OmniDirectionalLight : public AttenuationLight {
public:
    /**
     * \brief Constructor for the OmniDirectionalLight class.
     *
     * Initializes the omnidirectional light with a name, model-view matrix, color values, and optional attenuation parameters.
     *
     * \param name The name of the light.
     * \param model_view The model-view matrix.
     * \param ambient The ambient color of the light.
     * \param diffuse The diffuse color of the light.
     * \param specular The specular color of the light.
     * \param constant_att The constant attenuation factor (default is 1.0f).
     * \param linear_att The linear attenuation factor (default is 0.0f).
     * \param quadratic_att The quadratic attenuation factor (default is 0.0f).
     */
    OmniDirectionalLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant_att = 1.0f, float linear_att = 0.0f, float quadratic_att = 0.0f);

    /**
     * \brief Renders the omnidirectional light.
     *
     * This function overrides the render method from the AttenuationLight class to define the behavior of rendering an omnidirectional light.
     *
     * \param model_view The model-view matrix used for rendering the light.
     */
    void virtual render(glm::mat4 model_view) override;
};
