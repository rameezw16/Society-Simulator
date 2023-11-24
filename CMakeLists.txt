cmake_minimum_required(VERSION 3.5)
project(simulator)

set(CMAKE_BUILD_TYPE Debug)


file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
file(GLOB INCLUDE include)

add_library(implementation ${SRC_FILES} ${HEADERS})


#target_include_directories(main PUBLIC ${INCLUDE})
#target_link_libraries(main -lSDL2 -lSDL2_image)

add_executable(main ${SRC_FILES} ${HEADERS})
target_link_libraries(main PUBLIC implementation -lSDL2 -lSDL2_image)


