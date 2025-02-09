/**
 * @file		engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Alessandro Spagnuolo, Dominik Panzarella, Mattia Mancino
 */
#pragma once

#define GLUT_KEY_UP          101
#define GLUT_KEY_DOWN        103
#define GLUT_KEY_LEFT        100
#define GLUT_KEY_RIGHT       102
#define GLUT_CTRL_L          114
#define TAB                  9


 
//////////////
// #INCLUDE //
//////////////

   // C/C++:         
   #include <memory>
   #include <chrono>
   #include <queue>

	// Main library include
	#include "lib.h"
   #include "camera.h"
   #include "mesh.h"
   #include "node.h"
   #include "ortoCamera.h"
   #include "perspCamera.h"
   #include "object.h"
   #include "attenuationLight.h"
   #include "directionalLight.h"
   #include "light.h"
   #include "list.h"
   #include "material.h"
   #include "omnidirectionalLight.h"
   #include "spotLight.h"
   #include "texture.h"
   #include "ovoreader.h"





///////////////
// NAMESPACE //
///////////////

namespace Eng {



//////////////
// #INCLUDE //
//////////////   

   // You can subinclude here other headers of your engine...



///////////////////////
// MAIN ENGINE CLASS //
///////////////////////

/**
 * \class Base
 * \brief The main graphics engine class implemented as a singleton.
 *
 * The Base class initializes the engine, manages the rendering process, handles user input, and manages the scene graph.
 * It provides utilities for FPS calculation, text rendering, camera management, and scene rendering.
 */
class ENG_API Base final
{
//////////
public: //
//////////	  

   /**
    * \brief Deleted copy constructor to ensure only one instance of the singleton.
    */
   Base(Base const &) = delete;

   /**
    * \brief Destructor to clean up resources used by the engine.
    */
   ~Base();

   /**
    * \brief Deleted assignment operator to prevent assignment of the singleton.
    */
   void operator=(Base const &) = delete;

   /**
    * \brief Retrieves the singleton instance of the engine.
    * 
    * \return A reference to the singleton instance.
    */
   static Base &getInstance();

   /**
    * \brief Initializes the engine.
    *
    * Sets up the graphics context, initializes FreeGLUT, configures OpenGL settings, and prepares the engine for rendering.
    *
    * \param title The title of the window.
    * \param width The width of the window.
    * \param height The height of the window.
    * \param argc Number of command-line arguments.
    * \param argv Array of command-line arguments.
    * \return True if initialization was successful, false otherwise.
    */
   bool init(const char* title, unsigned int width, unsigned int height,int argc, char* argv[]);

   /**
    * \brief Frees all engine resources.
    * 
    * Properly disposes of allocated memory and shuts down dependencies like FreeImage.
    * \return True if resources were freed successfully, false otherwise.
    */
   bool free();   

   /**
    * \brief Updates the engine state, including handling input and managing animations.
    */
   void update();


   /**
    * \brief Renders the current scene graph.
    *
    * Clears the screen, processes the scene graph into the render list, and renders each object.
    */
   void renderScene();

   /**
    * \brief Loads a scene into the engine using the provided root node.
    *
    * \param root The root node of the scene graph.
    */
   void loadScene(Node* root);

   /**
    * \brief Loads a scene from a file.
    *
    * Parses the scene file and initializes the scene graph with the loaded data.
    * \param file_path The path to the scene file.
    * \param texture_dir Directory containing textures for the scene.
    */
   void loadScene(const char* file_path, const char* texture_dir);
   
   /**
    * \brief Calculates the current FPS.
    *
    * Updates the FPS value approximately once per second.
    */
   void calculateFPS();

   /**
    * \brief Registers a display callback.
    * \param function Pointer to the display callback function.
    */
   void registerDisplayCallback(void (*function)(void));

   /**
    * \brief Registers a reshape callback.
    * \param function Pointer to the reshape callback function.
    */
   void registerReshapeCallback(void (*function)(int, int));

   /**
    * \brief Registers a keyboard callback.
    * \param function Pointer to the keyboard callback function.
    */
   void registerKeyboardCallback(void (*function)(unsigned char, int, int));

   /**
    * \brief Registers a special key callback.
    * \param function Pointer to the special key callback function.
    */
   void registerSpecialCallback(void (*function)(int, int, int));

   /**
    * \brief Sets the engine's active camera.
    * \param camera Pointer to the PerspectiveCamera object.
    */
   void setCamera(PerspectiveCamera* camera);

   /**
    * \brief Enables FPS display.
    */
   void enableFPS();

   /**
    * \brief Disables FPS display.
    */

   void disableFPS();

   /**
    * \brief Enables wireframe rendering mode.
    */
   void enableWireFrame();

   /**
    * \brief Disables wireframe rendering mode.
    */
   void disableWireFrame();

   /**
    * \brief Gets the current window height.
    * \return The height of the window in pixels.
    */
   float getWindowHeight();

   /**
    * \brief Gets the current window width.
    * \return The width of the window in pixels.
    */
   float getWindowWidth();

  /**
    * \brief Queues a string to be rendered as on-screen text.
    * \param text The string to render.
    */
   void printText(const std::string& text);

   /**
    * \brief Adds a node to the current scene graph.
    * \param toAdd Pointer to the node to be added.
    */
   void addToScene(Node* toAdd);

   /**
    * \brief Gets the root node of the current scene graph.
    * \return Pointer to the root node.
    */
   Node* getRoot();

   /**
    * \brief Friend function to handle reshape events.
    * \param width The new width of the window.
    * \param height The new height of the window.
    */
   friend void reshapeCallback(int width, int height);

   /**
    * \brief Friend function to handle display events.
    */
   friend void displayCallback();

   /**
    * \brief Friend function to handle special key events.
    * \param key The special key pressed.
    * \param mouseX The x-coordinate of the mouse cursor.
    * \param mouseY The y-coordinate of the mouse cursor.
    */
   friend void specialCallback(int key, int mouseX, int mouseY);

///////////
private: //
///////////	

   /**
    * \struct Reserved
    * \brief Internal structure to manage reserved resources or data.
    *
    * This struct acts as a placeholder for implementation details
    * that should remain hidden from the public API.
    */
   struct Reserved;

   /**
    * \brief Unique pointer to manage the reserved structure.
    *
    * Allows the engine to encapsulate internal data and resources,
    * ensuring proper cleanup and efficient memory usage.
    */
   std::unique_ptr<Reserved> reserved;

   /**
    * \brief Pointer to the user-defined reshape callback function.
    *
    * This function is invoked when the window is resized.
    * It takes the new width and height as arguments.
    */
   void (*reshape_function)(int, int) { nullptr };

   /**
    * \brief Pointer to the user-defined display callback function.
    *
    * This function is called to render the window content.
   */
   void (*display_function)(void) { nullptr };

   /**
    * \brief Pointer to the user-defined special key callback function.
    *
    * This function is invoked when a special key (e.g., arrow keys) is pressed.
    * It takes the key code, mouse x-coordinate, and mouse y-coordinate as arguments.
    */
   void (*special_function)(int, int, int) { nullptr };

   /**
    * \brief A list of strings to be rendered as on-screen text.
    *
    * Each string in this list is displayed using the 2D camera.
    */
   std::vector<std::string> textToRender;

   /**
    * \brief Pointer to the current 3D camera used for rendering the scene.
    *
    * This camera defines the perspective view for rendering.
    */
   PerspectiveCamera* camera;

   /**
    * \brief Pointer to the current 2D camera used for rendering text.
    *
    * Primarily used for on-screen text and UI elements.
    */
   OrthographicCamera* m_2d_camera;

   /**
    * \brief Pointer to the root node of the scene graph.
    *
    * The scene graph organizes the 3D objects to be rendered in a hierarchical structure.
    */
   Node* m_scene_graph;

   /**
    * \brief The list of objects to be rendered in the current frame.
    *
    * This list is populated based on the scene graph and used during rendering.
    */
   RenderList m_render_list;

    /**
    * \brief Identifier for the GLUT window.
    *
    * Used to manage the window in the FreeGLUT/OpenGL context.
    */
   int windowId;

   /**
    * \brief The width of the engine's rendering window in pixels.
    */
   float m_window_width;

   /**
    * \brief The height of the engine's rendering window in pixels.
    */
   float m_window_height;

   /**
    * \brief Flag indicating whether FPS display is enabled.
    */

   bool m_show_fps;

   /**
    * \brief Timestamp of the last frame update.
    *
    * Used to calculate the elapsed time between frames for FPS computation.
    */
   std::chrono::time_point<std::chrono::steady_clock> lastTime;

   /**
    * \brief Counter for the number of frames rendered since the last FPS calculation.
    */
   int frameCount = 0;

   /**
    * \brief The current frames-per-second (FPS) value.
    */
   float fps = 0.0f;

   /**
    * \brief Private constructor for the singleton pattern.
    *
    * Ensures that the class cannot be instantiated directly outside of the getInstance() method.
    */
   Base();
};

}; // end of namespace Eng::

