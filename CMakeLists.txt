cmake_minimum_required(VERSION 3.10)

project(CiankyRenderbolek)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(tgaimage src/TGAImage/tgaimage.cpp)
add_library(model src/Model/model.cpp)

add_executable(renderbolek src/main.cpp)

target_link_libraries(renderbolek tgaimage)
target_link_libraries(renderbolek model)
