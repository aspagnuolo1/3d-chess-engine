#include <iostream>
#include <cassert>

#include "lightTest.h"

void SpotLightTest::test() {
    // Crea una matrice di vista modello fittizia per il test
    glm::mat4 model_view = glm::mat4(1.0f); // Identità per esempio
    glm::vec3 ambient(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse(1.0f, 1.0f, 1.0f);
    glm::vec3 specular(1.0f, 1.0f, 1.0f);
    glm::vec3 direction(1.0f, 0.0f, 0.0f);
    float constant_att = 1.0f, linear_att = 0.0f, quadratic_att = 0.0f, cutoff = 15.0f;

    // Crea un oggetto SpotLight
    SpotLight light(
        "SpotLightTest",
        model_view,
        ambient,
        diffuse,
        specular,
        direction,
        constant_att,
        linear_att,
        quadratic_att,
        cutoff
    );

    // Test Direction
    std::cout << "\tTesting Direction..." << std::endl;
    assert(light.get_direction() == direction);
    glm::vec3 new_direction(0.0f, 1.0f, 0.0f);
    light.set_direction(new_direction);
    assert(light.get_direction() == new_direction);

    // Test Cutoff
    std::cout << "\tTesting Cutoff..." << std::endl;
    assert(light.get_cutoff() == cutoff);
    float new_cutoff = 30.0f;
    light.set_cutoff(new_cutoff);
    assert(light.get_cutoff() == new_cutoff);

    // Test for Constant Attenuation
    std::cout << "\tTesting Constant Attenuation..." << std::endl;
    assert(light.get_constant_attenuation() == constant_att);
    light.set_constant_attenuation(2.0f);
    assert(light.get_constant_attenuation() == 2.0f);

    // Test for Linear Attenuation
    std::cout << "\tTesting Linear Attenuation..." << std::endl;
    assert(light.get_linear_attenuation() == linear_att);
    light.set_linear_attenuation(1.0f);
    assert(light.get_linear_attenuation() == 1.0f);

    // Test for Quadratic Attenuation
    std::cout << "\tTesting Quadratic Attenuation..." << std::endl;
    assert(light.get_quadratic_attenuation() == quadratic_att);
    light.set_quadratic_attenuation(0.5f);
    assert(light.get_quadratic_attenuation() == 0.5f);


};


void OmnidirectionalLightTest::test() {
    // Crea una matrice di vista modello fittizia per il test
    glm::mat4 model_view = glm::mat4(1.0f); // Identità per esempio
    glm::vec3 ambient(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse(1.0f, 1.0f, 1.0f);
    glm::vec3 specular(1.0f, 1.0f, 1.0f);
    float constant_att = 1.0f, linear_att = 0.0f, quadratic_att = 0.0f;

    // Crea un oggetto OmniDirectionalLight
    OmniDirectionalLight light(
        "OmniDirectionalLightTest",
        model_view,
        ambient,
        diffuse,
        specular,
        constant_att,
        linear_att,
        quadratic_att
    );

    // Test for Constant Attenuation
    std::cout << "\tTesting Constant Attenuation..." << std::endl;
    assert(light.get_constant_attenuation() == constant_att);
    light.set_constant_attenuation(2.0f);
    assert(light.get_constant_attenuation() == 2.0f);

    // Test for Linear Attenuation
    std::cout << "\tTesting Linear Attenuation..." << std::endl;
    assert(light.get_linear_attenuation() == linear_att);
    light.set_linear_attenuation(1.0f);
    assert(light.get_linear_attenuation() == 1.0f);

    // Test for Quadratic Attenuation
    std::cout << "\tTesting Quadratic Attenuation..." << std::endl;
    assert(light.get_quadratic_attenuation() == quadratic_att);
    light.set_quadratic_attenuation(0.5f);
    assert(light.get_quadratic_attenuation() == 0.5f);

};


void DirectionalLightTest::test() {
    // Crea una matrice di vista modello fittizia per il test
    glm::mat4 model_view = glm::mat4(1.0f); // Identità per esempio
    glm::vec3 ambient(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse(1.0f, 1.0f, 1.0f);
    glm::vec3 specular(1.0f, 1.0f, 1.0f);
    glm::vec3 position(10.0f, 5.0f, 3.0f);

    // Crea un oggetto DirectionalLight
    DirectionalLight light(
        "DirectionalLightTest",
        model_view,
        ambient,
        diffuse,
        specular,
        position
    );

    // Test per la posizione
    std::cout << "\tTesting Position..." << std::endl;
    assert(light.get_position() == position);
    glm::vec3 new_position(20.0f, 10.0f, 6.0f);
    light.set_position(new_position);
    assert(light.get_position() == new_position);

    // Test per Ambient
    std::cout << "\tTesting Ambient..." << std::endl;
    assert(light.get_ambient() == ambient);
    glm::vec3 new_ambient(0.2f, 0.2f, 0.2f);
    light.set_ambient(new_ambient);
    assert(light.get_ambient() == new_ambient);

    // Test per Diffuse
    std::cout << "\tTesting Diffuse..." << std::endl;
    assert(light.get_diffuse() == diffuse);
    glm::vec3 new_diffuse(0.5f, 0.5f, 0.5f);
    light.set_diffuse(new_diffuse);
    assert(light.get_diffuse() == new_diffuse);

    // Test per Specular
    std::cout << "\tTesting Specular..." << std::endl;
    assert(light.get_specular() == specular);
    glm::vec3 new_specular(1.0f, 1.0f, 1.0f);
    light.set_specular(new_specular);
    assert(light.get_specular() == new_specular);

};
