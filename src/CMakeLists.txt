add_library(linalg
        linalg/macros.h
        linalg/Tuple.cpp
        linalg/Matrix.cpp
)

# ------------ Renderer Library -------------
add_library(renderer
    renderer/Color.cpp
    renderer/Canvas.cpp
)
target_link_libraries(renderer
    linalg
)
target_include_directories(renderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
# ---------------- END ----------------

#------------- Shapes Library -------------
add_library(shapes
    shapes/Shape.h
    shapes/Sphere.cpp
        shapes/Hit.cpp
        shapes/Hit.h
)
target_link_libraries(shapes
    linalg
)
target_include_directories(shapes
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(raytracer
        renderer/Ray.cpp
        renderer/Ray.h
        shapes/Intersections.h
)
#---------------- END ----------------

target_link_libraries(raytracer
        linalg
        renderer
        shapes
)

target_include_directories(raytracer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(raytracer
        PUBLIC
        cxx_std_20
)