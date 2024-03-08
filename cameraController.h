#include <opencv2/opencv.hpp>
#include <zbar.h>

class Camera {
public:
    bool is_scanning_QR_code = false;
    int camera_index = 0;

private:
    cv::VideoCapture capture;
    zbar::ImageScanner scanner;

public:
    Camera() : scanner() {       
        capture.open(camera_index);
        if (!capture.isOpened()) {
            throw std::runtime_error("Erro ao abrir a câmera!");
        }
    }

    ~Camera() {
        capture.release();
    }

    void show_image() {
        cv::Mat frame;
        capture >> frame;

        if (!frame.empty()) {
            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

            zbar::Image zbar_image(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows);

            if (is_scanning_QR_code) {
                scanner.scan(zbar_image);

                for (zbar::Image::SymbolIterator symbol = zbar_image.symbol_begin(); symbol != zbar_image.symbol_end(); ++symbol) {
                    std::cout << "QR Code content: " << symbol->get_data() << std::endl;

                    std::vector<cv::Point> qr_points;
                    for (int i = 0; i < symbol->get_location_size(); ++i) {
                        qr_points.emplace_back(symbol->get_location_x(i), symbol->get_location_y(i));
                    }

                    cv::polylines(frame, qr_points, true, cv::Scalar(0, 255, 0), 2);
                }
            }

            cv::imshow("Camera", frame);
            cv::waitKey(30);
        }
    }

    void set_scanning_QR_code(bool is_scanning) {
        this->is_scanning_QR_code = is_scanning;
    }

    void set_camera_index(int index) {
        this->camera_index = index;
        capture.release();
        capture.open(camera_index);
    }
};
