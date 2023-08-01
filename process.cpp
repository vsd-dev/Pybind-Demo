// This file contains some pybind11 testing code that could be as reference for future development
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include <iostream>

namespace py = pybind11;

class CVutils
{
private:
    std::string filename;

public:
    CVutils(const std::string &name)
        : filename(name) {}

    py::array_t<uint8_t> resize(int width, int height)
    {
        cv::Mat input_image = cv::imread(filename, cv::IMREAD_COLOR);
        // Perform image processing, such as resizing
        cv::Mat resized_image;
        cv::resize(input_image, resized_image, cv::Size(width, height));
        return py::array({height, width, static_cast<int>(resized_image.channels())}, resized_image.data);
    }
};

namespace py = pybind11;

PYBIND11_MODULE(myLib, m)
{
    m.doc() = "OpenCV Demo Class";
    py::class_<CVutils>(m, "CVutils")
        .def(py::init<std::string>())
        .def("resize", &CVutils::resize, "resize an image");
}
