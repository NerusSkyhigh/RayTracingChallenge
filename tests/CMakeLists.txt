include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_TAG "v3.12.0"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(catch2)


add_executable(raytracer_tests
        Tuple.test.cpp
        Color.test.cpp
        Canvas.test.cpp
        Matrix.test.cpp
        Ray.test.cpp
        Intersections.test.cpp
        Sphere.test.cpp
        Hit.test.cpp
)

target_link_libraries(raytracer_tests
        PRIVATE
        Catch2::Catch2WithMain
        raytracer
)