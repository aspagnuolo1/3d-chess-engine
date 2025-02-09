#define FREEIMAGE_LIB // Static lib only, put it in the project props
#include "texture2D.h"
#include <FreeImage.h>

#include <GL/glew.h>
#include <fstream>
#include <iostream>

//TODO: include freeimage --> install with: brew install freeimage

unsigned int Texture2D::m_default_texture_id = 0;

ENG_API Texture2D::Texture2D(const std::string& name, const std::string& file_path) : Texture(name), m_file_path{file_path}
{
    if(!m_default_texture_id)
        generate_default_texture();

    m_loaded = false;

    m_textures.push_back(this);
}

ENG_API Texture2D::~Texture2D(){
	glDeleteTextures(1, &m_texture_id);
}

void ENG_API Texture2D::render(glm::mat4 model_view) {
    if (!m_loaded) {
        load_texture(m_texture_id);
    }

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // Applica le impostazioni configurate
    apply_filter_and_mipmap();
    apply_texture_wrap();
	apply_anisotropic_filter();

}

void ENG_API Texture2D::generate_default_texture()
{
	    unsigned char default_texture_data[4 * 4] = {
        255, 255, 255, 255, // White pixel
        0,   0,   0,   255, // Black pixel
        0,   0,   0,   255, // Black pixel
        255, 255, 255, 255  // White pixel
    };

	glGenTextures(1, &m_default_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, default_texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	m_loaded = true;
}

void ENG_API Texture2D::load_texture(unsigned int texture_id){
	
	if (m_file_path == "[none]") {
		m_texture_id = m_default_texture_id;
		return;
	}

    glGenTextures(1, &m_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

    std::ifstream fileStream(m_file_path);

	if (!fileStream.good()) {
		throw std::invalid_argument("Texture file does not exist. Check the path.");
	}

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(m_file_path.c_str(), 0);
	if (format == FIF_UNKNOWN) {
		throw std::invalid_argument("Texture format not suppoted.");
	}

	FIBITMAP* bitmap = FreeImage_Load(format, m_file_path.c_str());
	if (bitmap == nullptr) {
		throw std::invalid_argument("Error while loading file.");
	}

	
	if (format == FIF_DDS) {
		FreeImage_FlipVertical(bitmap);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(bitmap),  FreeImage_GetHeight(bitmap), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void *) FreeImage_GetBits(bitmap));

	FreeImage_Unload(bitmap);

	m_loaded = true;

}