cmake_minimum_required(VERSION 3.5)
project(peopleSim)

set(CMAKE_BUILD_TYPE Debug)
file(GLOB SRC_FILES src/*.cpp include/*.h include/*.hpp)
file(GLOB INCLUDE include)

add_executable(main ${SRC_FILES})
target_link_libraries(main -lSDL2 -lSDL2_image)
target_include_directories(main PRIVATE ${INCLUDE})



