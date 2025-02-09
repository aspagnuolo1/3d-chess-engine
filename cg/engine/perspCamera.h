#pragma once

//////////////
// #INCLUDE //
//////////////

	// Header file include
#include "camera.h"

/////////////
// CLASSES //
/////////////

/**
 * \class PerspectiveCamera
 * \brief Class that derives from Camera.
 *
 * This class implements a camera with a perspective projection. It is used to render scenes with perspective, 
 * where objects farther from the camera appear smaller. The class provides methods to manage field of view (FoV), 
 * render scenes, and adjust to changes in window size.
 */
class ENG_API PerspectiveCamera : public Camera
{
public:
    /**
     * \brief Constructor for the PerspectiveCamera class.
     *
     * Initializes a perspective camera with a name, initial transformation matrix, viewport dimensions, 
     * near and far clipping planes, and a field of view (FoV).
     *
     * \param name The name of the camera.
     * \param cords The initial transformation matrix in object coordinates.
     * \param width The viewport width of the camera.
     * \param height The viewport height of the camera.
     * \param near The near clipping plane distance.
     * \param far The far clipping plane distance.
     * \param fov The field of view (in degrees). Defaults to 45.0f.
     */
	PerspectiveCamera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height, float near, float far, float fov = 45.0f);

    /**
     * \brief Render the scene using the perspective camera.
     *
     * This method applies the perspective projection and combines it with the model-view matrix 
     * to render the scene from the camera's perspective.
     *
     * \param model_view The model-view transformation matrix.
     */
	void virtual render(glm::mat4 model_view) override;

    /**
     * \brief Update the camera's settings based on the new window size.
     *
     * Adjusts the perspective projection to match the new viewport dimensions while preserving the 
     * field of view and aspect ratio.
     *
     * \param width The new width of the window.
     * \param height The new height of the window.
     */
	virtual void update_window_size(unsigned int width, unsigned int height) override;

    /**
     * \brief Set a custom properties matrix for the camera.
     *
     * Allows manual setting of the camera's combined transformation and projection matrix.
     *
     * \param properties The new camera properties matrix.
     */
	void set_properties(glm::mat4 properties);

    /**
     * \brief Get the inverse of the camera's transformation matrix.
     *
     * Returns a matrix representing the inverse of the camera's current transformation, 
     * useful for view transformations.
     *
     * \return A 4x4 matrix representing the inverse transformation.
     */
	glm::mat4 get_inverse_camera();

    /**
     * \brief Get the field of view (FoV) of the perspective camera.
     * \return The current FoV value in degrees.
     */
	float get_fov() const;

    /**
     * \brief Set a new field of view (FoV) for the perspective camera.
     *
     * Adjusts the camera's perspective projection based on the new FoV.
     *
     * \param fov The new field of view in degrees.
     */
	void set_fov(float fov);


private:
    /**
     * \var m_fov
     * \brief Field of view for the perspective camera.
     *
     * Defines the vertical field of view (in degrees) for the perspective projection.
     */

	float m_fov;
};