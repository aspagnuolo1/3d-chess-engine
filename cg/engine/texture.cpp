//////////////
// #INCLUDE //
//////////////

// Object header file include
#include "texture.h"

#include <cstring>
#include <GL/glew.h>



std::vector<Texture*> ENG_API Texture::m_textures{};


ENG_API Texture::Texture(const std::string& name)
 : Object(name),
  m_loaded{false},
  m_filter{Filter::NEAREST},
  m_mipmap{TextureMipmap::DISABLE},
  m_wrap{TextureWrap::REPEAT},
  m_anisotropic_level{1}
{
	// Empty Constructor For now
	m_textures.push_back(this);
}

ENG_API Texture::~Texture()
{
	for(int i=0; i<m_textures.size(); i++){
		if(this->m_id == m_textures.at(i)->m_id)
			m_textures.erase(m_textures.begin() + i);
	}

	glDeleteTextures(1, &m_texture_id);
}

void ENG_API Texture::set_filter(Filter f, TextureMipmap m) {
    m_filter = f;
    m_mipmap = m;
}

void ENG_API Texture::set_texture_wrap(TextureWrap wrap) {
    m_wrap = wrap;
}

void ENG_API Texture::set_anisotropic_level(unsigned int level) {
    m_anisotropic_level = level;
}

void ENG_API Texture::apply_filter_and_mipmap() const {
    if (m_filter == LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (m_mipmap == MIPMAP_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else if (m_mipmap == MIPMAP_NEAREST) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        if (m_mipmap == MIPMAP_NEAREST) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        }
    }
}

void ENG_API Texture::apply_texture_wrap() const {
    if (m_wrap == REPEAT) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else if (m_wrap == CLAMP_TO_EDGE) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}



void ENG_API Texture::apply_anisotropic_filter() const {
	
    if (strstr((const char *)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic")) {
        float max_anisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);

        // Limita il livello al massimo supportato
        float anisotropy = std::min(static_cast<float>(m_anisotropic_level), max_anisotropy);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
    }else
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_anisotropic_level);
}



