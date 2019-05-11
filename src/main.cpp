#include "camera.h"
#include "scene.h"
#include "renderer.h"

#include <iostream>
#include <ctime>
#include <memory>
#include <glm/glm.hpp>
using namespace glm;

void drawSquare(Scene *scene, vec3 p1, vec3 p2, vec3 p3, vec3 p4, Material m, Texture* texture=NULL) {
    scene->add(new Quadrangle(p1, p2, p3, p4, m, texture));
}

void drawRoom(Scene *scene, vec3 origin, float size, Texture* brick, Texture* floor) {
    vec3 p1 = origin + vec3(-size, size, size+1000);
    vec3 p2 = origin + vec3(size, size, size+1000);
    vec3 p3 = origin + vec3(size, size, -size);
    vec3 p4 = origin + vec3(-size, size, -size);
    vec3 p5 = origin + vec3(-size, -size, size+1000);
    vec3 p6 = origin + vec3(size, -size, size+1000);
    vec3 p7 = origin + vec3(size, -size, -size);
    vec3 p8 = origin + vec3(-size, -size, -size);

    vec3 f1 = origin + vec3(-size, -size, size);
    vec3 f2 = origin + vec3(size, -size, size);
    vec3 f3 = origin + vec3(size, -size, -size);
    vec3 f4 = origin + vec3(-size, -size, -size);
    vec3 f5 = origin + vec3(-size, -size, size+1000);
    vec3 f6 = origin + vec3(size, -size, size+1000);
    vec3 f7 = origin + vec3(size, -size, size);
    vec3 f8 = origin + vec3(-size, -size, size);

    Material white = Material(vec3(0.8, 0.8, 0.8), 0, 0, 0);
    Material red = Material(vec3(0.8, 0, 0), 0, 0, 0);
    Material blue = Material(vec3(0, 0, 0.8), 0, 0, 0);

    drawSquare(scene, p1, p2, p3, p4, white);
    drawSquare(scene, p1, p2, p6, p5, white);
    drawSquare(scene, p2, p3, p7, p6, white);
    drawSquare(scene, p3, p4, p8, p7, white, brick);
    drawSquare(scene, p4, p1, p5, p8, red);
    drawSquare(scene, f1, f2, f3, f4, white, floor);
    drawSquare(scene, f5, f6, f7, f8, white, floor);
}

void drawMirror(Scene *scene) {
    vec3 p1 = vec3(-400, 300, -150);
    vec3 p2 = vec3(300, 300, -300);
    vec3 p3 = vec3(300, 0, -300);
    vec3 p4 = vec3(-400, 0, -150);
    Material mirror = Material(vec3(1, 1, 1), 1, 0, 0);
    drawSquare(scene, p1, p2, p3, p4, mirror);
}

void drawLight(Scene *scene, vec3 origin, float size) {
    Material light = Material(vec3(0,0,0), 0, 0, 0, 1, vec3(4,4,4));

    vec3 p1 = origin + vec3(-size, 0, size);
    vec3 p2 = origin + vec3(size, 0, size);
    vec3 p3 = origin + vec3(size, 0, -size);
    vec3 p4 = origin + vec3(-size, 0, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

void drawLeftLight(Scene *scene, vec3 origin, float size) {
    Material light = Material(vec3(0,0,0), 0, 0, 0, 1, vec3(4,4,4));

    vec3 p1 = origin + vec3(0, -size, size);
    vec3 p2 = origin + vec3(0, size, size);
    vec3 p3 = origin + vec3(0, size, -size);
    vec3 p4 = origin + vec3(0, -size, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

void drawScene(int samples) {
    vec3 origin(-300, 500, 700);
    vec3 dest(0, 200, 0);

    Camera camera = Camera(origin, dest, 400, 300, 700, 60);
    Scene scene = Scene();

    std::unique_ptr<Texture> earth(new Texture("../texture/earth.png"));
    std::unique_ptr<Texture> brick(new Texture("../texture/brick.png"));
    std::unique_ptr<Texture> floor(new Texture("../texture/floor.png"));

    // texture ball
    Object* obj1 = new Sphere(vec3(0,100,0), 100, Material(vec3(1, 1, 1), 0.5, 0, 0.2), earth.get());
    Object* obj2 = new Sphere(vec3(0,100,200), 80, Material(vec3(1, 1, 1), 0, 0, 0), brick.get());

    // refraction ball
    Object* obj3 = new Sphere(vec3(250,100,0), 100, Material(vec3(1, 1, 1), 0, 1, 0, 1.6));

    // mirror ball
    Object* obj4 = new Sphere(vec3(-250,100,0), 100, Material(vec3(1, 1, 1), 1, 0, 0));

    scene.add(obj1);
    scene.add(obj2);
    scene.add(obj3);
    scene.add(obj4);

    drawMirror(&scene);
    drawRoom(&scene, vec3(0, 500, 0), 500, brick.get(), floor.get());
    drawLeftLight(&scene, vec3(-499, 700, 0), 300);
    ////////////

    Renderer renderer = Renderer(&scene, &camera);
    renderer.render(samples);
    renderer.save_image("output.png");

    scene.free();
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    time_t start, stop;
    time(&start);

    int samples = 100;
    if (argc == 2) samples = atoi(argv[1]);
    drawScene(samples);

    time(&stop);
    float diff = difftime(stop, start);
    int hrs = (int)diff/3600;
    int mins = ((int)diff/60)-(hrs*60);
    int secs = (int)diff-(hrs*3600)-(mins*60);
    printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);

    return 0;
}
