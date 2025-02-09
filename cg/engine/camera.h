#pragma once


//////////////
// #INCLUDE //
//////////////

// C/C++

// GLM
#include <glm/glm.hpp>

// Base class include
#include "node.h"

/**
* \class Camera
* \brief Class that derives from Node.
*
* This class is responsible for defining a generic camera. It provides methods for managing viewport dimensions,
* near and far planes, and updating properties when the window size changes. The class is intended to be a
* base class for specific camera types that implement the \ref update_window_size function.
*/
class ENG_API Camera : public Node
{
public:
    /**
    * \brief Constructor for the Camera class.
    *
    * Initializes the camera with a name, initial position matrix, viewport dimensions, and clipping planes.
    *
    * \param name The name of the camera.
    * \param cords The initial transformation matrix in object coordinates.
    * \param width The viewport width of the camera.
    * \param height The viewport height of the camera.
    * \param near The near clipping plane distance.
    * \param far The far clipping plane distance.
    */
    Camera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height, float near, float far);

    /**
    * \brief Get the current width of the camera viewport.
    * \return The width of the viewport.
    */
    unsigned int get_width() const;

    /**
    * \brief Get the current height of the camera viewport.
    * \return The height of the viewport.
    */
    unsigned int get_height() const;

    /**
    * \brief Get the far clipping plane distance.
    * \return The far clipping plane distance.
    */
    float get_far() const;

    /**
    * \brief Get the near clipping plane distance.
    * \return The near clipping plane distance.
    */
    float get_near() const;

    /**
    * \brief Set a new height for the camera viewport.
    * \param height The new height of the viewport.
    */
    void set_height(unsigned int height);

    /**
    * \brief Set a new width for the camera viewport.
    * \param width The new width of the viewport.
    */
    void set_width(unsigned int width);

    /**
    * \brief Set a new near clipping plane distance.
    * \param new_near The new near clipping plane distance.
    */
    void set_near(float new_near);

    /**
    * \brief Set a new far clipping plane distance.
    * \param new_far The new far clipping plane distance.
    */
    void set_far(float new_far);

    /**
    * \brief Get the camera properties matrix.
    *
    * This matrix includes the camera's transformation and projection properties.
    * \return A 4x4 matrix representing the camera properties.
    */
    glm::mat4 get_properties() const;

    /**
    * \brief Pure virtual function to update the viewport size.
    *
    * This function should be implemented by derived classes to adjust the camera's settings
    * when the window size changes.
    *
    * \param width The new width of the window.
    * \param height The new height of the window.
    */
    virtual void update_window_size(unsigned int width, unsigned int height) = 0;

protected:
    /**
    * \var m_properties
    * \brief Matrix holding camera properties.
    *
    * Stores the camera's combined transformation and projection matrix.
    */
    glm::mat4 m_properties;

    /**
    * \var m_width
    * \brief Current camera viewport width.
    *
    * Stores the width of the camera's viewport.
    */
    unsigned int m_width;

    /**
    * \var m_height
    * \brief Current camera viewport height.
    *
    * Stores the height of the camera's viewport.
    */
    unsigned int m_height;

    /**
    * \var m_near
    * \brief Near clipping plane distance.
    *
    * Specifies the distance to the near clipping plane.
    */
    float m_near;

    /**
    * \var m_far
    * \brief Far clipping plane distance.
    *
    * Specifies the distance to the far clipping plane.
    */
    float m_far;
};
