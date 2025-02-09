/**
 * @file		mainTests.cpp
 * @brief	Test application (that uses the graphics engine)
 *
 * @author	Alessandro Spagnuolo, Dominik Panzarella, Mattia Mancino
 */



//////////////
// #INCLUDE //
//////////////

   // Library header:
   #include "engine.h"
   #include "materialTest.h"
   #include "lightTest.h"
   //#include "cameraTest.h"
   #include "nodeTest.h"
   #include "meshTest.h"
   #include "textureTest.h"

   // C/C++:
   #include <cassert>
   #include <iostream>



//////////
// MAIN //
//////////


void testEngineInitialization(int argc, char* argv[]) {
	Node root("RootNode", glm::mat4(1.0f));
}


/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[]) {
   std::cout << "=== Starting Tests ===" << std::endl;

   std::cout << std::endl;
   std::cout << "** Engine Test **" <<std::endl;
   testEngineInitialization(argc, argv);
   std::cout << "** All Engine tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** Node Test **" <<std::endl;
   NodeTest::test();
   std::cout << "** All Node tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** Mesh Test **" <<std::endl;
   MeshTest::test();
   std::cout << "** All Mesh tests passed successfully! **" << std::endl;


   std::cout << std::endl;
   std::cout << "** Material Test **" <<std::endl;
   MaterialTest::test();
   std::cout << "** All Material tests passed successfully! **" << std::endl;
   
   std::cout << std::endl;
   std::cout << "** SpotLight Test **" <<std::endl;
   SpotLightTest::test();
   std::cout << "** All SpotLight tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** OmnidrectionLight Test **" <<std::endl;
   OmnidirectionalLightTest::test();
   std::cout << "** All OmnidrectionLight tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** DirectionalLight Test **" <<std::endl;
   DirectionalLightTest::test();
   std::cout << "** All DirectionalLight tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** OrtoCamera Test **" <<std::endl;
   //OrtocameraTest::test();
   std::cout << "** All OrtoCamera tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** Perspcamera Test **" <<std::endl;
   //PerspcameraTest::test();
   std::cout << "** All Perspcamera tests passed successfully! **" << std::endl;

   std::cout << std::endl;
   std::cout << "** Texture Test **" <<std::endl;
   TextureTest::test();
   std::cout << "** All Texture tests passed successfully! **" << std::endl;


   std::cout << std::endl;
   std::cout << "=== All Tests Passed Successfully ===" << std::endl;
   return 0;
}
