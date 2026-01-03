add_library(raytracer
        Tuple.cpp
        Color.cpp
        Canvas.cpp
        Matrix.cpp
        Ray.cpp
        Ray.h
        Sphere.cpp
        Sphere.h
        Intersection.h
        Shape.h
)

target_include_directories(raytracer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(raytracer
        PUBLIC
        cxx_std_20
)