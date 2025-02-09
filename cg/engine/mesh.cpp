
#define GLM_ENABLE_EXPERIMENTAL

//////////////
// #INCLUDE //
//////////////


// Header file include
#include "mesh.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
/////////////
// CLASSES //
/////////////

ENG_API Mesh::Mesh(const std::string& name, glm::mat4 cords, unsigned int faces, unsigned int vertices,Material* material) :
		Node(name,cords) ,
		m_faces{ faces },
      m_vertices{ vertices },
      m_material{ material }
{
	//Empty Constructor
}

ENG_API Mesh::~Mesh()
{
	//Empty for now
}

void ENG_API Mesh::render(glm::mat4 model_view)
{
    glLoadMatrixf(glm::value_ptr(model_view));

    if (m_material != nullptr)
        m_material->render(model_view);

    glBegin(GL_TRIANGLES);

    // Rendering the mesh faces
    for (unsigned int i = 0; i < m_face_vertices.size(); i++) {
        const auto& face = m_face_vertices.at(i);  // Get the current face (an array of 3 vertex indices)

        // Iterate through each vertex in the face
        for (unsigned int j = 0; j < face.size(); j++) {
            // Retrieve and render vertex normal
            unsigned int vertexIndex = face[j];  // Get the vertex index
            const auto& vertex_normal_coords = m_all_normals.at(vertexIndex);

            // Retrieve and render texture coordinates
            const auto& vertex_texture_coords = m_all_texture_coords.at(vertexIndex);

            // Retrieve and render vertex position
            const auto& vertex_coords = m_all_vertices.at(vertexIndex);

            // Set normal
            glNormal3f(vertex_normal_coords.x, vertex_normal_coords.y, vertex_normal_coords.z);

            // Set texture coordinates
            glTexCoord2f(vertex_texture_coords.x, vertex_texture_coords.y);

            // Set vertex position
            glVertex3f(vertex_coords.x, vertex_coords.y, vertex_coords.z);
        }
    }
    glEnd();

}


void ENG_API Mesh::set_material(Material* material)
{
   this->m_material = material;
}

void ENG_API Mesh::set_all_vertices(std::vector<glm::vec3> all_vertices){
   m_all_vertices = std::move(all_vertices);
}

void ENG_API Mesh::set_all_normals(std::vector<glm::vec3> all_normals){
   m_all_normals = std::move(all_normals);
}

void ENG_API Mesh::set_all_texture_coords(std::vector<glm::vec2> all_texture_coords){
  m_all_texture_coords = std::move(all_texture_coords);
}

void ENG_API Mesh::set_face_vertices(std::vector<std::vector<unsigned int>> face_vertices){
   m_face_vertices = std::move(face_vertices);
}

void ENG_API Mesh::generate_cube(float edge) {
   float size = edge / 2.0f;
   unsigned char faceColor[6][3];
   for (int c = 0; c < 6; c++)
      for (int d = 0; d < 3; d++)
         faceColor[c][d] = rand() % 255;

   // Back:   
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[0][0], faceColor[0][1], faceColor[0][2]);
   glVertex3f(size, 0, -size);
   glVertex3f(-size, 0, -size);
   glVertex3f(size, edge, -size);
   glVertex3f(-size, edge, -size);
   glEnd();

   // Front:	      
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[1][0], faceColor[1][1], faceColor[1][2]);
   glVertex3f(-size, 0, size);
   glVertex3f(size, 0, size);
   glVertex3f(-size, edge, size);
   glVertex3f(size, edge, size);
   glEnd();

   // Left:	      
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[2][0], faceColor[2][1], faceColor[2][2]);
   glVertex3f(-size, edge, -size);
   glVertex3f(-size, 0, -size);
   glVertex3f(-size, edge, size);
   glVertex3f(-size, 0, size);
   glEnd();

   // Right:	      
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[3][0], faceColor[3][1], faceColor[3][2]);
   glVertex3f(size, 0, -size);
   glVertex3f(size, edge, -size);
   glVertex3f(size, 0, size);
   glVertex3f(size, edge, size);
   glEnd();

   // Bottom:	      
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[4][0], faceColor[4][1], faceColor[4][2]);
   glVertex3f(-size, 0, -size);
   glVertex3f(size, 0, -size);
   glVertex3f(-size, 0, size);
   glVertex3f(size, 0, size);
   glEnd();

   // Top:	      
   glBegin(GL_TRIANGLE_STRIP);
   glColor3ub(faceColor[4][0], faceColor[4][1], faceColor[4][2]);
   glVertex3f(size, edge, -size);
   glVertex3f(-size, edge, -size);
   glVertex3f(size, edge, size);
   glVertex3f(-size, edge, size);
   glEnd();
}

// Getter for all vertices
const std::vector<glm::vec3> ENG_API& Mesh::get_all_vertices() const {
    return m_all_vertices;
}

// Getter for all normals
const std::vector<glm::vec3> ENG_API& Mesh::get_all_normals() const {
    return m_all_normals;
}

// Getter for all texture coordinates
const std::vector<glm::vec2> ENG_API& Mesh::get_all_texture_coords() const {
    return m_all_texture_coords;
}

// Getter for face vertices
const std::vector<std::vector<unsigned int>> ENG_API& Mesh::get_face_vertices() const {
    return m_face_vertices;
}

Material ENG_API* Mesh::get_material()
{
    return m_material;
}