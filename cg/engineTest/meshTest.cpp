#include <iostream>
#include <cassert>

#include "meshTest.h"

void MeshTest::test() {
        // Create a Mesh instance with a name and initial transformation matrix (identity matrix)
        Mesh mesh("Mesh1", glm::mat4(1.0f), 6, 8); // Example with 6 faces and 8 vertices

        // Test the object name
        std::cout << "\tTesting Object Name..." << std::endl;
        assert(mesh.get_object_name() == "Mesh1");
        mesh.set_object_name("UpdatedMesh");
        assert(mesh.get_object_name() == "UpdatedMesh");

        // Test the object ID
        std::cout << "\tTesting Object ID..." << std::endl;
        unsigned int mesh_id = mesh.get_object_id();
        assert(mesh_id == 5); // Assuming the first object gets ID 2, so Mesh will get ID 3.

        // Test material assignment
        std::cout << "\tTesting Material..." << std::endl;
        Material* new_material = new Material("new_material", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
        mesh.set_material(new_material);
        // Optionally, test for the material, but ensure you have proper getters in the Material class

        // Test setting vertices, normals, and texture coordinates
        std::cout << "\tTesting Vertices, Normals, and Texture Coordinates..." << std::endl;
        std::vector<glm::vec3> vertices = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) };
        mesh.set_all_vertices(vertices);
        assert(mesh.get_all_vertices() == vertices);

        std::vector<glm::vec3> normals = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
        mesh.set_all_normals(normals);
        assert(mesh.get_all_normals() == normals);

        std::vector<glm::vec2> texture_coords = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
        mesh.set_all_texture_coords(texture_coords);
        assert(mesh.get_all_texture_coords() == texture_coords);

        // Test face vertices
        std::cout << "\tTesting Face Vertices..." << std::endl;
        std::vector<std::vector<unsigned int>> face_vertices = { {0, 1, 2}, {2, 3, 0} };
        mesh.set_face_vertices(face_vertices);
        assert(mesh.get_face_vertices() == face_vertices);
    }
