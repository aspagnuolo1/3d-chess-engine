#pragma once

#include "texture.h"

/**
 * \class Texture2D
 * \brief Derived class for managing 2D textures.
 *
 * This class represents a 2D texture, which can be loaded from a file and rendered. It inherits from the base `Texture` class,
 * implementing the necessary methods for handling the loading and rendering of 2D textures.
 */
class ENG_API Texture2D : public Texture{
public:

    /**
     * \brief Constructor
     *
     * Initializes a 2D texture from a specified file path.
     *
     * \param name The name of the texture.
     * \param file_path The path to the texture file.
     */
    Texture2D(const std::string& name, const std::string& file_path);

    /**
     * \brief Destructor
     *
     * Cleans up the 2D texture, freeing any resources associated with it.
     */

    ~Texture2D();

    /**
     * \brief Copy constructor
     *
     * Deleted to prevent copying of Texture2D instances.
     */
    Texture2D(const Texture2D& t) = delete;

    /**
     * \brief Copy assignment operator
     *
     * Deleted to prevent assignment of Texture2D instances.
     */
    Texture2D& operator=(const Texture2D& o) = delete;

    /**
     * \brief Move constructor
     *
     * Deleted to prevent moving of Texture2D instances.
     */
    Texture2D(Texture2D&& o) = delete;

    /**
     * \brief Move assignment operator
     *
     * Deleted to prevent move assignment of Texture2D instances.
     */

    Texture2D& operator=(Texture2D&& t) = delete;

    /**
     * \brief Render the 2D texture.
     *
     * Overrides the base class's render function to handle the specific behavior for rendering a 2D texture.
     * This function must be implemented by derived classes to define how to render the texture.
     *
     * \param model_view The transformation matrix to apply during rendering.
     */
    void virtual render(glm::mat4 model_view) override;

    /**
     * \brief Load the 2D texture from the specified file.
     *
     * This function implements the texture loading behavior for 2D textures. It loads the texture image from
     * the provided file path into OpenGL.
     *
     * \param texture_id The OpenGL texture ID to associate with the loaded texture.
     */
    void virtual load_texture(unsigned int texture_id) override;

protected:

    /**
     * \var m_file_path
     * \brief Path to the texture file.
     *
     * Stores the file path where the texture image is located. Used for loading the texture into OpenGL.
     */
    std::string m_file_path;

    /**
     * \brief Generate a default texture.
     *
     * This method creates a default texture when a valid texture file cannot be loaded. This texture could be a
     * simple placeholder (e.g., a solid color or checkerboard).
     */

    void generate_default_texture();

    /**
     * \var m_default_texture_id
     * \brief OpenGL ID for the default texture.
     *
     * Stores the OpenGL texture ID for the default texture. This texture is used when no valid texture can be loaded.
     */
    static unsigned int m_default_texture_id;

};