#include <stdio.h>

#include "cameraController.h"

int main() {
    Camera camera;

    // Define se é para escanear QRCodes
    camera.set_scanning_QR_code(true);

    // Define qual camera usar
    camera.set_camera_index(0);

    while (true) {
        camera.show_image();
        // Verifica se o usuário pressionou a tecla 'q' para sair do loop
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}