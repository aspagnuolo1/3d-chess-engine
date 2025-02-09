#include <iostream>
#include <cassert>

#include "cameraTest.h"

    void OrtocameraTest::test() {
        // Crea una telecamera ortografica con valori iniziali
        OrthographicCamera ortho_camera(
            "OrthographicCameraTest",
            glm::mat4(1.0f),  // Matrice di trasformazione iniziale (identità)
            800,              // Larghezza della finestra
            600               // Altezza della finestra
        );

        // Test per la larghezza della finestra
        std::cout << "\tTesting Get Width..." << std::endl;
        assert(ortho_camera.get_width() == 800);
        ortho_camera.set_width(1024);
        assert(ortho_camera.get_width() == 1024);

        // Test per l'altezza della finestra
        std::cout << "\tTesting Get Height..." << std::endl;
        assert(ortho_camera.get_height() == 600);
        ortho_camera.set_height(768);
        assert(ortho_camera.get_height() == 768);

        // Test per la distanza del piano di taglio vicino
        std::cout << "\tTesting Get Near Clipping..." << std::endl;
        ortho_camera.set_near(0.1f);
        assert(ortho_camera.get_near() == 0.1f);

        // Test per la distanza del piano di taglio lontano
        std::cout << "\tTesting Get Far Clipping..." << std::endl;
        ortho_camera.set_far(1000.0f);
        assert(ortho_camera.get_far() == 1000.0f);

        // Testa l'aggiornamento della dimensione della finestra
        std::cout << "\tTesting Update Window Size..." << std::endl;
        ortho_camera.update_window_size(1280, 720);
        assert(ortho_camera.get_width() == 1280);
        assert(ortho_camera.get_height() == 720);
    }




    void PerspcameraTest::test() {
        // Crea una telecamera prospettica con valori iniziali
        PerspectiveCamera perspec_camera(
            "PerspectiveCameraTest",
            glm::mat4(1.0f),  // Matrice di trasformazione iniziale (identità)
            800,              // Larghezza della finestra
            600,              // Altezza della finestra
            0.1f,             // Distanza del piano di taglio vicino
            1000.0f,          // Distanza del piano di taglio lontano
            45.0f             // Campo visivo (fov)
        );

        // Test per la larghezza della finestra
        std::cout << "\tTesting Get Width..." << std::endl;
        assert(perspec_camera.get_width() == 800);
        perspec_camera.set_width(1024);
        assert(perspec_camera.get_width() == 1024);

        // Test per l'altezza della finestra
        std::cout << "\tTesting Get Height..." << std::endl;
        assert(perspec_camera.get_height() == 600);
        perspec_camera.set_height(768);
        assert(perspec_camera.get_height() == 768);

        // Test per il piano di taglio vicino
        std::cout << "\tTesting Get Near Clipping..." << std::endl;
        perspec_camera.set_near(0.2f);
        assert(perspec_camera.get_near() == 0.2f);

        // Test per il piano di taglio lontano
        std::cout << "\tTesting Get Far Clipping..." << std::endl;
        perspec_camera.set_far(1200.0f);
        assert(perspec_camera.get_far() == 1200.0f);

        // Test per il campo visivo (fov)
        std::cout << "\tTesting Get FOV..." << std::endl;
        assert(perspec_camera.get_fov() == 45.0f);
        perspec_camera.set_fov(60.0f);
        assert(perspec_camera.get_fov() == 60.0f);

        // Testa l'aggiornamento della dimensione della finestra
        std::cout << "\tTesting Update Window Size..." << std::endl;
        perspec_camera.update_window_size(1280, 720);
        assert(perspec_camera.get_width() == 1280);
        assert(perspec_camera.get_height() == 720);

        // Verifica la matrice inversa della telecamera
        std::cout << "\tTesting Get Inverse Camera Matrix..." << std::endl;
        glm::mat4 inverse_camera = perspec_camera.get_inverse_camera();
        assert(inverse_camera == glm::inverse(glm::mat4(1.0f)));  // Supponendo che la matrice iniziale sia l'identità
    }

