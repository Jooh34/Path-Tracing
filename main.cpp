#include <iostream>

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"

using namespace std;

int main(int argc, char *argv[]) {
    int samples = 4;
    if (argc == 2) samples = atoi(argv[1]);

    Vec origin(0, 0, 500);
    Vec dest(0, 0, 0);

    Camera camera = Camera(origin, dest, 100, 80, 500, 90);
    Scene scene = Scene();

    scene.add( dynamic_cast<Object*>(new Sphere(Vec(0,0,0), 100, Material())) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-300,300,0), 50, Material(EMIT, Vec(1,1,1), ))) );

    Renderer renderer = Renderer(&scene, &camera);
    renderer.render(samples);
    renderer.save_image("output.png");
}
