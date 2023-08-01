cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "myLib")
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(PYBIND11_PYTHON_VERSION 3.10)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")
add_subdirectory(pybind11)

find_package(OpenCV REQUIRED)


pybind11_add_module(${PROJECT_NAME} process.cpp)

# target_include_directories(${PROJECT_NAME} PUBLIC ${PYBIND11_INCLUDE_DIRS} "${CMAKE_SYSROOT}/usr/include/python3.10" ${OpenCV_INCLUDE_DIRS} 
# ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${OpenCV_INCLUDE_DIRS})

# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})


target_link_libraries(${PROJECT_NAME} PUBLIC
  ${OpenCV_LIBS})
  target_compile_definitions(${PROJECT_NAME}
  PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

#
# Print out the value of PYBIND11_INCLUDE_DIRS
message(STATUS "PYBIND11_INCLUDE_DIRS: ${PYBIND11_INCLUDE_DIRS}")
message(STATUS ":OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
