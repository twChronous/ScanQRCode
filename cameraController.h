#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

class Camera {
private:
    cv::VideoCapture cap;

public:
    Camera() {
        // Abre a câmera padrão (0 para a primeira câmera conectada)
        cap.open(0);
        
        // Verifica se a câmera foi aberta corretamente
        if (!cap.isOpened()) {
            std::cerr << "Erro ao abrir a câmera!" << std::endl;
        } 

    }

    ~Camera() {
        // Fecha a câmera quando o objeto Camera é destruído
        cap.release();
    }

    void showImage() {
        cv::Mat frame;

        // Captura um frame da câmera
        cap >> frame;

        // Detecta códigos QR na imagem
        detectarQR(frame);

        // Exibe o frame capturado
        cv::imshow("Camera", frame);

        // Aguarda uma tecla ser pressionada por 30ms (o número pode ser ajustado conforme necessário)
        cv::waitKey(30);
    }

private:
    void detectarQR(cv::Mat& frame) {
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();

        // Cria um objeto de dicionário (pode ser DICT_6X6_250, DICT_6X6_100, etc.)
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

        // Detecta marcadores na imagem
        cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters);

        // Desenha os contornos e IDs dos marcadores detectados
        if (!markerIds.empty()) {
            cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
        }
    }
};