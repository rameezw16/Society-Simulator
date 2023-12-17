cmake_minimum_required(VERSION 3.5)
project(simulator)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/gnuplot-iostream")

# include(ExternalProject)
# set(GNUPLOT_VERSION "5.4.8")

# ExternalProject_Add(
#     gnuplot
#     GIT_REPOSITORY https://github.com/gnuplot/gnuplot.git
#     GIT_TAG "${GNUPLOT_VERSION}"
#     UPDATE_COMMAND ""
#     CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Skipping Gnuplot configure step."
#     BUILD_COMMAND ${CMAKE_COMMAND} -E echo "Skipping Gnuplot build step."
#     INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "Skipping Gnuplot install step."
# )


file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
file(GLOB INCLUDE include)

add_library(implementation ${SRC_FILES} ${HEADERS})


#target_include_directories(main PUBLIC ${INCLUDE})
#target_link_libraries(main -lSDL2 -lSDL2_image)

add_executable(main ${SRC_FILES} ${HEADERS})
# add_dependencies(main gnuplot)

# ExternalProject_Get_Property(gnuplot source_dir)
# target_include_directories(main PRIVATE ${source_dir}/src)
target_link_libraries(main PUBLIC implementation -lSDL2 -lSDL2_image ${Boost_LIBRARIES})

# Specify Gnuplot library directory
# ExternalProject_Get_Property(gnuplot binary_dir)
# set(GNUPLOT_EXECUTABLE "${binary_dir}/src/gnuplot")
# target_link_directories(main PRIVATE ${binary_dir}/src)

# Specify the path to the Gnuplot executable
# target_compile_definitions(main PRIVATE GNUPLOT_EXECUTABLE="${GNUPLOT_EXECUTABLE}")


