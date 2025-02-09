#pragma once

#include "object.h"
#include <vector>

/**
 * \enum Filter
 * \brief Enumeration for texture filtering options.
 *
 * Specifies the filtering mode to be applied when scaling a texture.
 */
enum ENG_API Filter{
	NEAREST,			///< Nearest neighbor filtering for pixelated scaling.
	LINEAR				///< Linear filtering for smooth scaling.
};

/**
 * \enum TextureMipmap
 * \brief Enumeration for mipmap filtering options.
 *
 * Specifies whether and how mipmaps are used for texture filtering.
 */
enum ENG_API TextureMipmap{
	DISABLE,			 ///< Mipmapping is disabled.
	MIPMAP_NEAREST,		///< Use nearest neighbor interpolation for mipmaps.
	MIPMAP_LINEAR		///< Use linear interpolation for mipmaps.
};

/**
 * \enum TextureWrap
 * \brief Enumeration for texture wrapping options.
 *
 * Specifies how textures are wrapped around coordinates exceeding the range [0, 1].
 */
enum ENG_API TextureWrap{
	REPEAT,					///< Repeats the texture image.
	CLAMP_TO_EDGE			///< Clamps the texture to the edge pixels.
};

/**
 * \class Texture
 * \brief Abstract class for texture management.
 *
 * Provides the base functionality for loading, configuring, and applying textures. 
 * Derived classes must implement specific behavior for loading texture data.
 */
class ENG_API Texture : public Object {
public:
	/**
	* \brief Constructor
	*
	* Initializes the texture with a name
	*
	* \param name The name of the texture.
	*/
	Texture(const std::string& name);


	/**
	* \brief Deconstructor
	*
	* \param Texture class decostructor
	*/
	virtual ~Texture();

	/**
	 * \brief Copy constructor
	 *
	 * Deleted to prevent copying of Texture instances.
	 */
	Texture(const Texture& o) = delete;

	/**
	 * \brief Move constructor
	 *
	 * Deleted to prevent moving of Texture instances.
	 */
	Texture(Texture&& o) = delete;

	/**
	 * \brief Copy assignment operator
	 *
	 * Deleted to prevent assignment of Texture instances.
	 */
	Texture& operator=(const Texture& o) = delete;

	/**
	 * \brief Move assignment operator
	 *
	 * Deleted to prevent move assignment of Texture instances.
	 */
	Texture& operator=(Texture&& o) = delete;

    /**
     * \brief Render the texture.
     *
     * A pure virtual function that must be implemented by derived classes.
     * Currently, the parameters are placeholders and not used.
     *
     * \param model_view NOT USED.
     */
	void virtual render(glm::mat4 model_view) override =0;

    /**
     * \brief Set texture filtering and mipmap options.
     *
     * Configures the filtering and mipmap settings for the texture.
     *
     * \param f The filtering mode.
     * \param m The mipmap option. Defaults to \ref TextureMipmap::DISABLE.
     */
	void set_filter(Filter f, TextureMipmap m = TextureMipmap::DISABLE);

    /**
     * \brief Set texture wrapping mode.
     *
     * Configures how the texture is wrapped for coordinates outside [0, 1].
     *
     * \param wrap The wrapping mode.
     */
	void set_texture_wrap(TextureWrap wrap);

    /**
     * \brief Set the anisotropic filtering level.
     *
     * Configures the level of anisotropic filtering applied to the texture.
     *
     * \param level The desired anisotropic filtering level.
     */

	void set_anisotropic_level(unsigned int level);

protected:

    /**
     * \brief Apply filtering and mipmap settings to the texture.
     *
     * Updates the OpenGL texture parameters for filtering and mipmaps.
     */
    void apply_filter_and_mipmap() const;

    /**
     * \brief Apply texture wrapping mode to the texture.
     *
     * Updates the OpenGL texture parameters for wrapping.
     */

    void apply_texture_wrap() const;

    /**
     * \brief Apply anisotropic filtering to the texture.
     *
     * Configures anisotropic filtering based on hardware support and the specified level.
     */

	void apply_anisotropic_filter() const;

    /**
     * \brief Pure virtual function to load the texture.
     *
     * Derived classes must implement this function to load texture data.
     *
     * \param texture_id The OpenGL texture ID.
     */
	void virtual load_texture(unsigned int texture_id) = 0;

    /**
     * \var m_texture_id
     * \brief OpenGL texture ID.
     *
     * Stores the unique identifier for the texture in OpenGL.
     */
	unsigned int m_texture_id;

    /**
     * \var m_textures
     * \brief List of all loaded texture objects.
     *
     * A static vector that holds pointers to all created Texture instances.
     */

	static std::vector<Texture*> m_textures;

    /**
     * \var m_loaded
     * \brief Flag indicating if the texture is loaded.
     */
	bool m_loaded;

    /**
     * \var m_filter
     * \brief Current filtering mode.
     */
	Filter m_filter;

    /**
     * \var m_mipmap
     * \brief Current mipmap setting.
     */
	TextureMipmap m_mipmap;

    /**
     * \var m_wrap
     * \brief Current texture wrapping mode.
     */
	TextureWrap m_wrap;

    /**
     * \var m_anisotropic_level
     * \brief Level of anisotropic filtering.
     */
	unsigned int m_anisotropic_level;

};