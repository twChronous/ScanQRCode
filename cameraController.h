#include <zbar.h>
#include <math.h>
#include <opencv2/opencv.hpp>

class Camera {
public:
    int camera_index = 0;
    float focal_length = 500.0; 
    bool is_show_distance = false;
    float known_qr_code_size = 10;
    bool is_scanning_QR_code = false;
    bool is_takeoff_base = false;
    bool is_landing_base = false;

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
                    if (is_show_distance) {
                        float qr_area = cv::contourArea(qr_points);
                        float distance = (known_qr_code_size * focal_length) / sqrt(qr_area);

                        std::cout << "Distância: " << distance << " cm" << std::endl;
                        cv::polylines(frame, qr_points, true, cv::Scalar(0, 255, 0), 2);
                    }
                }
            }
            if (is_landing_base) {
                //Código de identificação da base de pouso
                
            }
            if (is_takeoff_base) {
                //Código de identificação da base de decolagem
            }
        }

            cv::imshow("Camera", frame);
            cv::waitKey(30);
        }

    void set_scanning_QR_code(bool is_scanning) {
        this->is_scanning_QR_code = is_scanning;
    }
    void set_show_distance(bool is_distance) {
        this->is_show_distance = is_distance;
    }
    void set_identify_landing_base(bool is_base) {
        this->is_landing_base = is_base;
    }
    void set_identify_takeoff_base(bool is_base) {
        this->is_takeoff_base = is_base;
    }
    void set_camera_index(int index) {
        this->camera_index = index;
        capture.release();
        capture.open(camera_index);
    }
    void set_focal_length(int size) {
        this->focal_length = size;
    }
    void set_qr_code_size(int size) {
        this->known_qr_code_size = size;
    }
};
