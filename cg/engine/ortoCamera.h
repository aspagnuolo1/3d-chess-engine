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
 * \class OrthographicCamera
 * \brief Class that derives from Camera.
 *
 * This class implements a camera with an orthographic projection. It is a specific type of camera 
 * suitable for rendering scenes without perspective distortion. It overrides methods to handle rendering 
 * and adjusting to changes in the window size.
 */
class ENG_API OrthographicCamera : public Camera
{
public:
    /**
     * \brief Constructor for the OrthographicCamera class.
     *
     * Initializes an orthographic camera with a name, initial transformation matrix, and viewport dimensions.
     * The near and far clipping planes are set to default values suitable for orthographic projection.
     *
     * \param name The name of the camera.
     * \param cords The initial transformation matrix in object coordinates.
     * \param width The viewport width of the camera.
     * \param height The viewport height of the camera.
     */

	OrthographicCamera(const std::string& name, glm::mat4 cords, unsigned int width, unsigned int height);

    /**
     * \brief Render the scene using the orthographic camera.
     *
     * This method applies the orthographic projection and combines it with the model-view matrix to render 
     * the scene from the camera's perspective.
     *
     * \param model_view The model-view transformation matrix.
     */
	void virtual render(glm::mat4 model_view) override;


    /**
     * \brief Update the camera's settings based on the new window size.
     *
     * Adjusts the orthographic projection to match the new viewport dimensions. This ensures that the 
     * rendered scene scales appropriately with window resizing.
     *
     * \param width The new width of the window.
     * \param height The new height of the window.
     */
	virtual void update_window_size(unsigned int width, unsigned int height) override;

};