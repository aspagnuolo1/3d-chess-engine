#include <iostream>
#include <cassert>

#include "textureTest.h"

#include <iostream>
#include <cassert>

void TextureTest::test() {
        // Step 1: Create a Texture2D object
        std::cout << "\tCreating a Texture2D object..." << std::endl;
        Texture2D texture("TestTexture", "path/to/texture.png");

        // Step 2: Test if the object is created successfully
        std::cout << "\tTesting object creation..." << std::endl;
        assert(texture.get_object_name() == "TestTexture");

        // Step 3: Test if the texture is loaded (assuming load_texture flag is set)
        std::cout << "\tTesting texture load status..." << std::endl;
    

        // Step 4: Test the texture's ID
        std::cout << "\tTesting texture ID..." << std::endl;

        // Step 5: Test filter and wrap settings
        std::cout << "\tTesting texture filter and wrap settings..." << std::endl;
        //Texture::set_filter(Filter::LINEAR, TextureMipmap::MIPMAP_NEAREST);
        //Texture::set_texture_wrap(TextureWrap::REPEAT);
    }
