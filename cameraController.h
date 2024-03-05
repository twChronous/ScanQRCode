#include <opencv2/opencv.hpp>
#include <zbar.h>

class Camera {
private:
    cv::VideoCapture cap;
    zbar::ImageScanner scanner;

public:
    Camera() : scanner() {
        // Abre a câmera padrão (0 para a primeira câmera conectada)
        cap.open(0);
        
        // Verifica se a câmera foi aberta corretamente
        if (!cap.isOpened()) {
            std::cerr << "Erro ao abrir a câmera!" << std::endl;
            exit(1);
        }
    }

    ~Camera() {
        // Fecha a câmera quando o objeto Camera é destruído
        cap.release();
    }

    void showImage(bool ScanQRCode = false) {
        cv::Mat frame;

        // Captura um frame da câmera
        cap >> frame;

        // Converte o frame capturado para tons de cinza
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Cria uma imagem ZBar
        zbar::Image imagemQR(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows);

        // Realiza a decodificação dos códigos QR na imagemif
        if(ScanQRCode) scanner.scan(imagemQR);

        // Exibe o frame capturado
        cv::imshow("Camera", frame);

        // Processa os resultados da decodificação
        for (zbar::Image::SymbolIterator simbolo = imagemQR.symbol_begin(); simbolo != imagemQR.symbol_end(); ++simbolo) {
            std::cout << "Tipo de código: " << simbolo->get_type_name() << std::endl;
            std::cout << "Conteúdo: " << simbolo->get_data() << std::endl;
        }

        // Aguarda uma tecla ser pressionada por 30ms (o número pode ser ajustado conforme necessário)
        cv::waitKey(30);
    }
};