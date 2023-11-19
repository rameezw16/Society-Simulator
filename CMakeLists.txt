# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(interpersonal_visualiser)

# Set the source file
set(SOURCE_FILES *.cpp)
# set(SOURCE_FILES *.cpp)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE -w)

# Link against SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_ttf)

# Copy the font file to the build directory
configure_file(fonts/times.ttf ${CMAKE_CURRENT_BINARY_DIR}/times.ttf COPYONLY)
