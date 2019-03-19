#include <iostream>
#include <ctime>

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"

using namespace std;

void drawSquare(Scene *scene, Vec p1, Vec p2, Vec p3, Vec p4) {
  scene->add( dynamic_cast<Object*>(new Triangle(p1, p2, p3, Material(Vec(0.9, 0.9, 0.9), 1, 0, Vec(0,0,0)))));
  scene->add( dynamic_cast<Object*>(new Triangle(p1, p3, p4, Material(Vec(0.9, 0.9, 0.9), 1, 0, Vec(0,0,0)))));
}
void drawCube(Scene *scene, Vec origin, double size) {
  Vec p1 = origin + Vec(-size, size, size);
  Vec p2 = origin + Vec(size, size, size);
  Vec p3 = origin + Vec(size, size, -size);
  Vec p4 = origin + Vec(-size, size, -size);
  Vec p5 = origin + Vec(-size, -size, size);
  Vec p6 = origin + Vec(size, -size, size);
  Vec p7 = origin + Vec(size, -size, -size);
  Vec p8 = origin + Vec(-size, -size, -size);

  drawSquare(scene, p1, p2, p3, p4);
  // drawSquare(scene, p1, p2, p6, p5);
  drawSquare(scene, p2, p3, p7, p6);
  drawSquare(scene, p3, p4, p8, p7);
  drawSquare(scene, p4, p1, p5, p8);
  drawSquare(scene, p5, p6, p7, p8);

}
int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    time_t start, stop;
    time(&start);

    int samples = 30;
    if (argc == 2) samples = atoi(argv[1]);

    Vec origin(-250, 500, 1000);
    Vec dest(0, 100, 0);

    Camera camera = Camera(origin, dest, 500, 400, 1145, 60);
    Scene scene = Scene();

    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-300,350,350), 100, Material(Vec(0.1, 0.1, 0.9), 1, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(200,200,0), 100, Material(Vec(1, 0.71, 0.76), 0.5, 0.5, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(0,100,0), 100, Material(Vec(0, 1.0, 0.8), 0, 1, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(0,1500,0), 700, Material(Vec(0,0,0), 0, 0, Vec(1,1,1)))) );
    drawCube(&scene, Vec(0, 1200, 0), 1200);

    Renderer renderer = Renderer(&scene, &camera);
    renderer.render(samples);
    renderer.save_image("output.png");

    time(&stop);
    double diff = difftime(stop, start);
    int hrs = (int)diff/3600;
    int mins = ((int)diff/60)-(hrs*60);
    int secs = (int)diff-(hrs*3600)-(mins*60);
    printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);
    return 0;
}
