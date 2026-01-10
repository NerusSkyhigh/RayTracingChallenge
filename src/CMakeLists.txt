add_library(linalg
        linalg/macros.h
        linalg/Tuple.cpp
        linalg/Matrix.cpp
        linalg/ViewTransform.h
)

# ------------ Renderer Library -------------
add_library(renderer
        renderer/Color.cpp
        renderer/Canvas.cpp
        renderer/Material.cpp
        renderer/PointLight.cpp
        renderer/Ray.cpp
        renderer/World.cpp
        renderer/World.h
        renderer/Camera.cpp
        renderer/Camera.h
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
        shapes/Sphere.cpp
        shapes/Intersections.cpp
        shapes/Plane.cpp
        shapes/Plane.h
)
target_link_libraries(shapes
    linalg
)
target_include_directories(shapes
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


#---------------- END ----------------
add_library(raytracer
        INTERFACE
)

target_link_libraries(raytracer
        INTERFACE
        linalg
        renderer
        shapes
)

target_include_directories(raytracer
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(raytracer
        INTERFACE
        cxx_std_20
)