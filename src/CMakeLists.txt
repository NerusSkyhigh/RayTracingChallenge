# ---------------- linalg ----------------
add_library(linalg
        linalg/macros.h
        linalg/Tuple.cpp
        linalg/Matrix.cpp
        linalg/ViewTransform.h
)

target_include_directories(linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# ---------------- Geometry ----------------
add_library(geometry
        geometry/Ray.cpp
        geometry/Intersections.cpp
        geometry/Shape.h
        geometry/Sphere.cpp
        geometry/Plane.h
)

target_link_libraries(geometry PUBLIC linalg)
target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# ---------------- Scene ----------------
add_library(scene
        scene/World.cpp
        scene/PointLight.cpp
        scene/material/Material.cpp
        scene/pattern/Pattern.cpp
        scene/pattern/StripePattern.cpp
        scene/pattern/Monocromatic.cpp
        scene/pattern/Monocromatic.h
)

target_link_libraries(scene PUBLIC geometry linalg)
target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# ---------------- Render ----------------
add_library(render
        render/Color.cpp
        render/Canvas.cpp
        render/Camera.cpp
)

target_link_libraries(render PUBLIC scene geometry linalg)
target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# ---------------- Facade target ----------------
add_library(raytracer INTERFACE)

target_link_libraries(raytracer INTERFACE
        linalg
        geometry
        scene
        render
)

target_compile_features(raytracer INTERFACE cxx_std_20)
