//////////////
// #INCLUDE //
//////////////

// Object header file include
#include "attenuationLight.h"

ENG_API AttenuationLight::AttenuationLight(const std::string& name, glm::mat4 model_view, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, 
                                           float constant_att, float linear_att, float quadratic_att) 
    : Light(name, model_view, ambient, diffuse, specular), 
      m_constant_attenuation{constant_att}, m_linear_attenuation{linear_att}, m_quadratic_attenuation{quadratic_att}
{
    // Costruttore vuoto che inizializza l'oggetto con i parametri passati
}

float ENG_API AttenuationLight::get_constant_attenuation() const {
    return m_constant_attenuation;
}

void ENG_API AttenuationLight::set_constant_attenuation(float constant_att) {
    // Aggiungi un controllo per evitare valori negativi
    if (constant_att >= 0.0f) {
        m_constant_attenuation = constant_att;
    }
}

float ENG_API AttenuationLight::get_linear_attenuation() const {
    return m_linear_attenuation;
}

void ENG_API AttenuationLight::set_linear_attenuation(float linear_att) {
    // Aggiungi un controllo per evitare valori negativi
    if (linear_att >= 0.0f) {
        m_linear_attenuation = linear_att;
    }
}

float ENG_API AttenuationLight::get_quadratic_attenuation() const {
    return m_quadratic_attenuation;
}

void ENG_API AttenuationLight::set_quadratic_attenuation(float quadratic_att) {
    // Aggiungi un controllo per evitare valori negativi
    if (quadratic_att >= 0.0f) {
        m_quadratic_attenuation = quadratic_att;
    }
}
