#include <iostream>
#include <ctime>

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"

using namespace std;

void drawSquare(Scene *scene, Vec p1, Vec p2, Vec p3, Vec p4, Material m) {
  scene->add( dynamic_cast<Object*>(new Triangle(p1, p2, p3, m)));
  scene->add( dynamic_cast<Object*>(new Triangle(p1, p3, p4, m)));
}
void drawRoom(Scene *scene, Vec origin, double size) {
  Vec p1 = origin + Vec(-size, size, size+1000);
  Vec p2 = origin + Vec(size, size, size+1000);
  Vec p3 = origin + Vec(size, size, -size);
  Vec p4 = origin + Vec(-size, size, -size);
  Vec p5 = origin + Vec(-size, -size, size+1000);
  Vec p6 = origin + Vec(size, -size, size+1000);
  Vec p7 = origin + Vec(size, -size, -size);
  Vec p8 = origin + Vec(-size, -size, -size);

  Material white = Material(Vec(0.8, 0.8, 0.8), 1, 0, 0, Vec(0,0,0));
  Material red = Material(Vec(0.8, 0, 0), 1, 0, 0, Vec(0,0,0));
  Material blue = Material(Vec(0, 0, 0.8), 1, 0, 0, Vec(0,0,0));
  drawSquare(scene, p1, p2, p3, p4, white);
  drawSquare(scene, p1, p2, p6, p5, white);
  drawSquare(scene, p2, p3, p7, p6, blue);
  drawSquare(scene, p3, p4, p8, p7, white);
  drawSquare(scene, p4, p1, p5, p8, red);
  drawSquare(scene, p5, p6, p7, p8, white);
}

void drawLight(Scene *scene, Vec origin, double size) {
    Material light = Material(Vec(0,0,0), 0, 0, 0, Vec(4,4,4));

    Vec p1 = origin + Vec(-size, 0, size);
    Vec p2 = origin + Vec(size, 0, size);
    Vec p3 = origin + Vec(size, 0, -size);
    Vec p4 = origin + Vec(-size, 0, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    time_t start, stop;
    time(&start);

    int samples = 500;
    if (argc == 2) samples = atoi(argv[1]);

    Vec origin(0, 500, 1400);
    Vec dest(0, 500, 0);

    Camera camera = Camera(origin, dest, 500, 500, 1400, 60);
    Scene scene = Scene();

    scene.add( dynamic_cast<Object*>(new Sphere(Vec(100,160,-300), 160, Material(Vec(1, 1, 1), 1, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(200,120,200), 120, Material(Vec(0.5, 0.5, 0.5), 0, 1, 1, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-200,120,-200), 120, Material(Vec(1.0, 1.0, 1.0), 0, 1, 0, Vec(0,0,0)))) );
    drawRoom(&scene, Vec(0, 500, 0), 500);
    drawLight(&scene, Vec(0, 999, 0), 300);

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
