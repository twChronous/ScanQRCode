#include <stdio.h>

#include "cameraController.h"

int main() {
    Camera camera;

    // Define se é para escanear QRCodes
    camera.set_scanning_QR_code(true);
    // Define qual camera usar
    camera.set_camera_index(0);
    //Distância focal da câmera em pixels 
    camera.set_focal_length(500.0);
    //Tamanho do QR Code em cm
    camera.set_qr_code_size(10.0);

    std::cout << "Code ON!" << std::endl;
    while (true) {
        camera.show_image();
        // Verifica se o usuário pressionou a tecla 'q' para sair do loop
        if (cv::waitKey(1) == 'q') {
            std::cout << "Code OFF!" << std::endl;
            break;
        }
    }

    return 0;
}