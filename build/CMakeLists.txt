set (CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(pathtracer
    ../src/main.cpp
    ../src/camera.cpp
    ../src/ray.cpp
    ../src/scene.cpp
    ../src/renderer.cpp
    ../src/material.cpp
    ../src/objects.cpp
    ../src/texture.cpp
    ../lib/lodepng/lodepng.cpp
    )
