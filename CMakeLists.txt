cmake_minimum_required(VERSION 4.1)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

option(BUILD_TESTING "Build tests" ON)

add_subdirectory(src)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

#add_subdirectory(src-with-eigen)


add_executable(cp4_clock
        img/cp4_clock.cpp
)
target_link_libraries(cp4_clock
        PRIVATE
        raytracer
)

add_executable(cp5_sphere
    img/cp5_sphere.cpp
)
target_link_libraries(cp5_sphere
    PRIVATE
    raytracer
)