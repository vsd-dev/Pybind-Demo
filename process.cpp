// This file contains some pybind11 testing code that could be as reference for future development
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <pybind11/functional.h>
namespace py = pybind11;
using PyArrayFloat = py::array_t<double>;
using PyListInt = std::vector<int>;
using Pyuint8 = py::array_t<uint8_t>;

class CVutils
{
private:
    std::string filename;

public:
    Pyuint8 process_image(std::string &filename, int width, int height)
    {
        cv::Mat input_image = cv::imread(filename, cv::IMREAD_COLOR);
        // Perform image processing, such as resizing
        cv::Mat resized_image;
        cv::resize(input_image, resized_image, cv::Size(width, height));
        return py::array({height, width, static_cast<int>(resized_image.channels())}, resized_image.data);
    }

    Pyuint8 read_image(std::string &filename)
    {
        cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
        // Perform image processing, such as resizing
        int width = image.cols;
        int height = image.rows;
        return py::array({height, width, static_cast<int>(image.channels())}, image.data);
    }

    Pyuint8 resizeImage(const Pyuint8& pixels, size_t w, size_t h) 
    {
        py::buffer_info bufInfo = pixels.request();
        cv::Mat input_image(bufInfo.shape[0], bufInfo.shape[1], CV_8UC3, bufInfo.ptr);

        cv::Mat resized_image;
        cv::resize(input_image, resized_image, cv::Size(w, h));

        return Pyuint8(
            {static_cast<int>(resized_image.rows), static_cast<int>(resized_image.cols), 3},
            resized_image.data);
    }

    PyArrayFloat add_arrays(PyArrayFloat input1, PyArrayFloat input2)
    // py::array_t<double> add_arrays(py::array_t<double, py::array::c_style | py::array::forcecast> input1, py::array_t<double, py::array::c_style | py::array::forcecast> input2)
    {
        py::buffer_info buf1 = input1.request();
        py::buffer_info buf2 = input2.request();
        if (buf1.ndim != 1 || buf2.ndim != 1)
            throw std::runtime_error("Number of dimensions must be one");

        if (buf1.size != buf2.size)
            throw std::runtime_error("Input shapes must match");

        // /* No pointer is passed, so NumPy will allocate the buffer */
        PyArrayFloat result = PyArrayFloat(buf1.size);
        py::buffer_info buf3 = result.request();

        double *ptr1 = static_cast<double *>(buf1.ptr);
        double *ptr2 = static_cast<double *>(buf2.ptr);
        double *ptr3 = static_cast<double *>(buf3.ptr);
        for (size_t idx = 0; idx < buf1.shape[0]; idx++)
            ptr3[idx] = ptr1[idx] + ptr2[idx];

        return result;
    }
};

PYBIND11_MODULE(myLib, m)
{
    m.doc() = "Pybind Demo Class";
    py::class_<CVutils>(m, "CVutils")
        .def(py::init<>())
        .def("process_image", &CVutils::process_image, "preprocess an image")
        .def("read_image", &CVutils::read_image, "read an image")
        .def("resize_image", &CVutils::resizeImage, "Resize an image")
        .def("add_arrays", &CVutils::add_arrays, "Add two NumPy arrays")
        // .def("process_image_with_cb", &CVutils::process_image_cb, "Add two NumPy arrays")
        ;

    py::class_<PyListInt>(m, "MyList")
        .def(py::init<>())
        .def("append", (void(PyListInt::*)(const int &)) & PyListInt::push_back)
        .def("clear", (void(PyListInt::*)()) & PyListInt::clear)
        .def("pop", (void(PyListInt::*)()) & PyListInt::pop_back)
        .def("__len__", [](const PyListInt &v)
             { return v.size(); })
        .def("__get__", [](const PyListInt &v, int idx)
             { return v[idx]; })

        .def("print", [](const PyListInt &l)
             {
                fprintf(stderr, "[");
                auto it = l.begin();

                if (it != l.end()) {
                    fprintf(stderr, "%d", *it++);
                }

                for (; it != l.end(); ++it) {
                    fprintf(stderr, ", %d", *it);
                }

                fprintf(stderr, "]\n"); })

        .def(
            "__iter__", [](PyListInt &v)
            { return py::make_iterator(v.begin(), v.end()); },
            py::keep_alive<0, 1>());
}
