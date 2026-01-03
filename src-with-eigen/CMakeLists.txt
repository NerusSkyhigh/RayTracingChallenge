include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(eigen
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG "5.0.0"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(eigen)



add_library(eigen_raytracer
        Canvas.cpp
)

target_include_directories(eigen_raytracer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(eigen_raytracer
        PUBLIC
        cxx_std_20
)