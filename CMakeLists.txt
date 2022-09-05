cmake_minimum_required(VERSION 3.20)
project(TimeOptimalTrajectory)

set(CMAKE_CXX_STANDARD 14)

set(EIGEN3_INCLUDE_DIR libs/eigen-3.4-rc1)
INCLUDE_DIRECTORIES ( ${EIGEN3_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(./include/TimeOptimalTrajectory)
INCLUDE_DIRECTORIES(D:/ProgramData/Anaconda3/include)
link_directories(D:/ProgramData/Anaconda3/libs)


aux_source_directory(./src SRC_MAIN)

add_executable(Example ./tests/Example.cpp ${SRC_MAIN})
add_executable(ExamplePlot ./tests/ExamplePlot.cpp ${SRC_MAIN})

target_link_libraries(ExamplePlot python39.lib)
