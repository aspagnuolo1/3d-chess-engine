#pragma once

#include "object.h"

#include "texture.h"

/**
 * \class Material
 * \brief Class representing the material properties of an object.
 * 
 * The Material class encapsulates the properties of a material such as emission, ambient, diffuse, specular colors, shininess, and transparency.
 * It also supports the assignment of a texture, which can be applied to the surface of an object using this material.
 * 
 * The class derives from the `Object` class and implements the `render()` method to handle material-specific rendering behavior.
 */
class ENG_API Material : public Object {
public:

    /**
     * \brief Constructor
     * 
     * Initializes the material with various properties like emission, ambient, diffuse, specular, shininess, and transparency.
     * 
     * \param name The name of the material.
     * \param emission The emission color of the material.
     * \param ambient The ambient color of the material.
     * \param diffuse The diffuse color of the material.
     * \param specular The specular color of the material.
     * \param shininess The shininess factor of the material (default is 0.0f).
     * \param transparency The transparency factor of the material (default is 1.0f).
     */
	Material(const std::string& name, glm::vec4 emission, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess = 0.0f, float transparency= 1.0f);

    /**
     * \brief Destructor
     * 
     * Cleans up resources used by the Material instance.
     */

	~Material();


	/**
	 * \brief Copy constructor
	 *
	 * Deleted to prevent copying of Material instances.
	 */
	Material(const Material& o) = delete;

	/**
	 * \brief Move constructor
	 *
	 * Deleted to prevent moving of Material instances.
	 */
	Material(Material&& o) = delete;


	/**
	 * \brief Copy assignment operator
	 *
	 * Deleted to prevent assignment of Material instances.
	 */
	Material& operator=(const Material& o) = delete;

	/**
	 * \brief Move assignment operator
	 *
	 * Deleted to prevent move assignment of Material instances.
	 */
	Material& operator=(Material&& o) = delete;

    /**
     * \brief Inherited function used to render the material properties in the context of the given model-view matrix.
     * 
     * The function sets up the OpenGL state for the material rendering, applying its properties such as colors, shininess, and texture.
     * 
     * \param model_view The Model-View matrix used for the rendering context.
     */
	void virtual render(glm::mat4 model_view) override;

    /**
     * \brief Sets the texture for the material.
     * 
     * This function allows you to set a texture to be applied to objects using this material.
     * 
     * \param texture Pointer to the Texture object to be applied.
     */
	void set_texture(Texture* texture);

    /**
     * \brief Gets the texture of the material.
     * 
     * \return The texture pointer applied to this material.
     */
	Texture* get_texture();

    /**
     * \brief Gets the emission color of the material.
     * 
     * \return The emission color of the material.
     */

	glm::vec3 get_emission();


    /**
     * \brief Gets the ambient color of the material.
     * 
     * \return The ambient color of the material.
     */
	glm::vec3 get_ambient();

    /**
     * \brief Gets the diffuse color of the material.
     * 
     * \return The diffuse color of the material.
     */
	glm::vec3 get_diffuse();

    /**
     * \brief Gets the specular color of the material.
     * 
     * \return The specular color of the material.
     */
	glm::vec3 get_specular();

    /**
     * \brief Sets the emission color for the material.
     * 
     * \param emission The emission color to be set for the material.
     */
	void set_emission(const glm::vec3& emission);

    /**
     * \brief Sets the ambient color for the material.
     * 
     * \param ambient The ambient color to be set for the material.
     */
	void set_ambient(const glm::vec3& ambient);

    /**
     * \brief Sets the diffuse color for the material.
     * 
     * \param diffuse The diffuse color to be set for the material.
     */
	void set_diffuse(const glm::vec3& diffuse);

    /**
     * \brief Sets the specular color for the material.
     * 
     * \param specular The specular color to be set for the material.
     */
	void set_specular(const glm::vec3& specular);

    /**
     * \brief Sets the shininess factor of the material.
     * 
     * \param shininess The shininess factor to be set (default is 0.0f).
     */
	void set_shininess(float shininess);

    /**
     * \brief Gets the shininess factor of the material.
     * 
     * \return The shininess factor.
     */
	float get_shininess();

    /**
     * \brief Gets the transparency factor of the material.
     * 
     * \return The transparency factor of the material.
     */
	float get_transparency();

    /**
     * \brief Sets the transparency factor for the material.
     * 
     * \param transparency The transparency factor to be set (default is 1.0f).
     */
	void set_transparency(float transparency);

protected:
    /**
     * \var m_emission
     * \brief Emission color of the material.
     * 
     * The emission color represents the material's ability to emit light, often used to simulate glowing or self-illuminating objects.
     */

	glm::vec3 m_emission;

    /**
     * \var m_ambient
     * \brief Ambient color of the material.
     * 
     * The ambient color is the color of light that is scattered and diffused across the surface of the object.
     */
	glm::vec3 m_ambient;

    /**
     * \var m_diffuse
     * \brief Diffuse color of the material.
     * 
     * The diffuse color represents how much light is scattered across the surface, providing the base color of the object.
     */
	glm::vec3 m_diffuse;

    /**
     * \var m_specular
     * \brief Specular color of the material.
     * 
     * The specular color represents the reflection of light on the surface, simulating highlights and shiny spots.
     */
	glm::vec3 m_specular;

    /**
     * \var m_shininess
     * \brief Shininess factor of the material.
     * 
     * The shininess factor controls the size and sharpness of the specular highlights on the material's surface.
     */
	float m_shininess;

    /**
     * \var m_transparency
     * \brief Transparency factor of the material.
     * 
     * The transparency factor defines how transparent the material is. A value of 1.0 means fully opaque, and 0.0 means fully transparent.
     */
	float m_transparency;

    /**
     * \var m_texture
     * \brief Texture applied to the material.
     * 
     * The texture is a 2D image or map that is applied to the material to enhance its visual appearance.
     */
	Texture* m_texture;
};