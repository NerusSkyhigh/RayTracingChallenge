cmake_minimum_required(VERSION 4.1)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

option(BUILD_TESTING "Build tests" ON)

add_subdirectory(src)

add_executable(RayTracer
        main.cpp
)

target_link_libraries(RayTracer
        PRIVATE
        raytracer
)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()