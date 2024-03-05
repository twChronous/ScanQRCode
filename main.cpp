#include <ostream>
#include <stdio.h>

#include "cameraController.h"

using namespace std;

int main() {
    // Cria um objeto Camera
    Camera camera;

    // Loop principal para capturar imagens até que o usuário pressione a tecla 'q'
    while (true) {
        // Captura um frame da câmera
        camera.showImage(true);

        // Verifica se o usuário pressionou a tecla 'q' para sair do loop
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}
