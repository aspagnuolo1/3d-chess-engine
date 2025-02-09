#include <iostream>
#include <cassert>

#include "materialTest.h"

void MaterialTest::test() {
        Material material(
            "TestMaterial", 
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  // emission
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),  // ambient
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),  // diffuse
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),  // specular
            1.0f  // shininess
        );

        // Test emission
        std::cout << "\tTesting Emission..." << std::endl;
        assert(material.get_emission() == glm::vec3(0.0f, 0.0f, 0.0f));
        material.set_emission(glm::vec3(1.0f, 1.0f, 1.0f));
        assert(material.get_emission() == glm::vec3(1.0f, 1.0f, 1.0f));

        // Test ambient
        std::cout << "\tTesting Ambient..." << std::endl;
        assert(material.get_ambient() == glm::vec3(1.0f, 0.0f, 0.0f));
        material.set_ambient(glm::vec3(0.5f, 0.5f, 0.5f));
        assert(material.get_ambient() == glm::vec3(0.5f, 0.5f, 0.5f));

        // Test diffuse
        std::cout << "\tTesting Diffuse..." << std::endl;
        assert(material.get_diffuse() == glm::vec3(0.0f, 1.0f, 0.0f));
        material.set_diffuse(glm::vec3(0.2f, 0.3f, 0.4f));
        assert(material.get_diffuse() == glm::vec3(0.2f, 0.3f, 0.4f));

        // Test specular
        std::cout << "\tTesting Specular..." << std::endl;
        assert(material.get_specular() == glm::vec3(0.0f, 0.0f, 1.0f));
        material.set_specular(glm::vec3(0.7f, 0.7f, 0.7f));
        assert(material.get_specular() == glm::vec3(0.7f, 0.7f, 0.7f));

        // Test shininess
        std::cout << "\tTesting Shininess..." << std::endl;
        assert(material.get_shininess() == 1.0f);
        material.set_shininess(64.0f);
        assert(material.get_shininess() == 64.0f);

 }
