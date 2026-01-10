cmake_minimum_required(VERSION 4.1)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

option(BUILD_TESTING "Build tests" ON)

add_subdirectory(src)

find_package(OpenMP REQUIRED)

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
    OpenMP::OpenMP_CXX
)

add_executable(cp6_LightingSphere
    img/cp6_LightingSphere.cpp
    #img/cp6_LightingSphereCameraVersion.cpp
)
target_link_libraries(cp6_LightingSphere
    PRIVATE
    raytracer
)

add_executable(cp7_Scene
    img/cp7_Scene.cpp
)
target_link_libraries(cp7_Scene
    PRIVATE
    raytracer
)

add_executable(cp9_SpheresOnAPlane
    img/cp9_SpheresOnAPlane.cpp
)
target_link_libraries(cp9_SpheresOnAPlane
        PRIVATE
        raytracer
)
