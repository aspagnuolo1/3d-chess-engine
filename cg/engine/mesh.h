#pragma once

//////////////
// #INCLUDE //
//////////////

	// C/C++
	#include <string>

	// Main library include
	#include "lib.h"
	#include "node.h"
	#include "material.h"	

	//GLM
	#include <glm/glm.hpp>

/////////////
// CLASSES //
/////////////

/**
 * \class Mesh
 * \brief Class for representing a 3D mesh.
 *
 * The Mesh class derives from the Node class and adds functionality for handling 3D mesh data, including vertices, 
 * normals, texture coordinates, and faces. It can be rendered with its material properties and transformation matrices.
 */
class ENG_API Mesh : public Node {
public:
    /**
     * \brief Constructor
     *
     * Initializes the mesh with a name, transformation matrix, number of faces and vertices, and an optional material.
     *
     * \param name The name of the mesh.
     * \param cords The initial transformation matrix in object coordinates.
     * \param faces The number of faces in the mesh.
     * \param vertices The number of vertices in the mesh.
     * \param material The material to be applied to the mesh. Defaults to a simple material.
     */
	Mesh(const std::string& name, glm::mat4 cords, unsigned int faces, unsigned int vertices, Material* material = new Material("default_material", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 5.0f));

	/**
	* \brief Deconstructor
	*
	* \param Mesh class decostructor
	*/
	virtual ~Mesh();

	/**
	 * \brief Copy constructor
	 *
	 * Deleted to prevent copying of Mesh instances.
	 */
	Mesh(const Mesh& o) = delete;

	/**
	 * \brief Move constructor
	 *
	 * Deleted to prevent moving of Mesh instances.
	 */
	Mesh(Mesh&& o) = delete;


	/**
	 * \brief Copy assignment operator
	 *
	 * Deleted to prevent assignment of Mesh instances.
	 */
	Mesh& operator=(const Mesh& o) = delete;

	/**
	 * \brief Move assignment operator
	 *
	 * Deleted to prevent move assignment of Mesh instances.
	 */
	Mesh& operator=(Mesh&& o) = delete;

    /**
     * \brief Render the mesh.
     *
     * This function renders the mesh using OpenGL, applying the material and the associated transformation.
     * It iterates through the faces of the mesh, rendering each vertex along with its normal and texture coordinates.
     *
     * \param model_view The transformation matrix to apply to the mesh.
     */
	void virtual render(glm::mat4 model_view);

	    
	/**
     * \brief Set the material for the mesh.
     *
     * This method allows for assigning a new material to the mesh.
     *
     * \param material The new material to assign to the mesh.
     */
	void set_material(Material* material);

	/**
     * \brief Set the mesh's vertices.
     *
     * This method allows for setting the vertices of the mesh. The vertices are stored in a vector of glm::vec3.
     *
     * \param all_vertices The list of all vertex positions in the mesh.
     */
	void set_all_vertices(std::vector<glm::vec3> all_vertices);

	/**
     * \brief Set the mesh's normals.
     *
     * This method allows for setting the normals of the mesh. The normals are stored in a vector of glm::vec3.
     *
     * \param all_normals The list of all vertex normals in the mesh.
     */
	void set_all_normals(std::vector<glm::vec3> all_normals);

    /**
     * \brief Set the mesh's texture coordinates.
     *
     * This method allows for setting the texture coordinates of the mesh. The texture coordinates are stored in a vector of glm::vec2.
     *
     * \param all_texture_coords The list of all texture coordinates in the mesh.
     */
	void set_all_texture_coords(std::vector<glm::vec2> all_texture_coords);

    /**
     * \brief Set the mesh's face vertices.
     *
     * This method allows for setting the vertices that make up each face of the mesh. Each face consists of a set of vertex indices.
     *
     * \param face_vertices The list of faces, where each face is represented by a set of vertex indices.
     */
	void set_face_vertices(std::vector<std::vector<unsigned int>> face_vertices);

    /**
     * \brief Get the mesh's vertices.
     *
     * This method retrieves all the vertices of the mesh.
     *
     * \return A reference to the vector of all vertices.
     */
    const std::vector<glm::vec3>& get_all_vertices() const;

    /**
     * \brief Get the mesh's normals.
     *
     * This method retrieves all the normals of the mesh.
     *
     * \return A reference to the vector of all normals.
     */
    const std::vector<glm::vec3>& get_all_normals() const;

    /**
     * \brief Get the mesh's texture coordinates.
     *
     * This method retrieves all the texture coordinates of the mesh.
     *
     * \return A reference to the vector of all texture coordinates.
     */
    const std::vector<glm::vec2>& get_all_texture_coords() const;

    /**
     * \brief Get the mesh's face vertices.
     *
     * This method retrieves the vertices for each face of the mesh.
     *
     * \return A reference to the vector of face vertices.
     */
    const std::vector<std::vector<unsigned int>>& get_face_vertices() const;

    /**
     * \brief Get the material of the mesh.
     *
     * This method retrieves the material that is applied to the mesh.
     *
     * \return A pointer to the mesh's material.
     */
	Material* get_material();

private:
    /**
     * \brief Generate a cube mesh.
     *
     * This method generates a cube mesh with a specified edge length. Each face of the cube is randomly colored.
     *
     * \param edge The length of the cube's edge.
     */
	void generate_cube(float edge);

protected:
    /**
     * \var m_faces
     * \brief The number of faces in the mesh.
     *
     * This member variable stores the number of faces in the mesh, used for rendering.
     */
	unsigned int m_faces;

    /**
     * \var m_vertices
     * \brief The number of vertices in the mesh.
     *
     * This member variable stores the number of vertices in the mesh, used for rendering.
     */
	unsigned int m_vertices;

    /**
     * \var m_material
     * \brief The material applied to the mesh.
     *
     * This member variable stores the material that defines the visual appearance of the mesh.
     */
	Material* m_material;

    /**
     * \var m_all_vertices
     * \brief The vertices of the mesh.
     *
     * This member variable stores the positions of all vertices in the mesh.
     */
	std::vector<glm::vec3> m_all_vertices;

    /**
     * \var m_all_normals
     * \brief The normals of the mesh.
     *
     * This member variable stores the normals associated with each vertex in the mesh.
     */
    std::vector<glm::vec3> m_all_normals;

    /**
     * \var m_all_texture_coords
     * \brief The texture coordinates of the mesh.
     *
     * This member variable stores the texture coordinates associated with each vertex in the mesh.
     */
    std::vector<glm::vec2> m_all_texture_coords;

    /**
     * \var m_face_vertices
     * \brief The vertices for each face in the mesh.
     *
     * This member variable stores the indices of vertices that form each face of the mesh.
     */
	std::vector<std::vector<unsigned int>> m_face_vertices;

};