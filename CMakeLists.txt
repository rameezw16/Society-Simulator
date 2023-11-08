cmake_minimum_required(VERSION 3.0)
project(peopleSim)

file(GLOB SRC_FILES src/*.cpp include/*.h)

find_package(SDL2)
add_executable(main ${SRC_FILES})
target_link_libraries(main -lSDL2)



