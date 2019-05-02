#include <iostream>
#include <ctime>

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"

#include <glm/glm.hpp>

using namespace std;

void drawSquare(Scene *scene, Vec p1, Vec p2, Vec p3, Vec p4, Material m, Texture* texture=NULL) {
    scene->add(dynamic_cast<Object*> (new Quadrangle(p1, p2, p3, p4, m, texture)));
}

void drawRoom(Scene *scene, Vec origin, double size, Texture* brick, Texture* floor) {
    Vec p1 = origin + Vec(-size, size, size+1000);
    Vec p2 = origin + Vec(size, size, size+1000);
    Vec p3 = origin + Vec(size, size, -size);
    Vec p4 = origin + Vec(-size, size, -size);
    Vec p5 = origin + Vec(-size, -size, size+1000);
    Vec p6 = origin + Vec(size, -size, size+1000);
    Vec p7 = origin + Vec(size, -size, -size);
    Vec p8 = origin + Vec(-size, -size, -size);

    Vec f1 = origin + Vec(-size, -size, size);
    Vec f2 = origin + Vec(size, -size, size);
    Vec f3 = origin + Vec(size, -size, -size);
    Vec f4 = origin + Vec(-size, -size, -size);
    Vec f5 = origin + Vec(-size, -size, size+1000);
    Vec f6 = origin + Vec(size, -size, size+1000);
    Vec f7 = origin + Vec(size, -size, size);
    Vec f8 = origin + Vec(-size, -size, size);

    Material white = Material(Vec(0.8, 0.8, 0.8), 0, 0, 0);
    Material red = Material(Vec(0.8, 0, 0), 0, 0, 0);
    Material blue = Material(Vec(0, 0, 0.8), 0, 0, 0);

    drawSquare(scene, p1, p2, p3, p4, white);
    drawSquare(scene, p1, p2, p6, p5, white);
    drawSquare(scene, p2, p3, p7, p6, white);
    drawSquare(scene, p3, p4, p8, p7, white, brick);
    drawSquare(scene, p4, p1, p5, p8, red);
    drawSquare(scene, f1, f2, f3, f4, white, floor);
    drawSquare(scene, f5, f6, f7, f8, white, floor);
}

void drawArtwork(Scene *scene, Vec origin, double width, double height, double depth, double f, Texture* t) {
    double w = width/2+f;
    double h = height/2+f;
    double d = depth/2;

    Vec p1 = origin + Vec(-w, h, d);
    Vec p2 = origin + Vec(w, h, d);
    Vec p3 = origin + Vec(w, h, -d);
    Vec p4 = origin + Vec(-w, h, -d);
    Vec p5 = origin + Vec(-w, -h, d);
    Vec p6 = origin + Vec(w, -h, d);
    Vec p7 = origin + Vec(w, -h, -d);
    Vec p8 = origin + Vec(-w, -h, -d);

    Vec a1 = origin + Vec(-width/2, height/2, depth/2+1);
    Vec a2 = origin + Vec(width/2, height/2, depth/2+1);
    Vec a5 = origin + Vec(-width/2, -height/2, depth/2+1);
    Vec a6 = origin + Vec(width/2, -height/2, depth/2+1);

    Material frame = Material(Vec(0.5, 0.4, 0.2), 0.8, 0, 0.3);

    drawSquare(scene, p1, p2, p3, p4, frame);
    drawSquare(scene, p1, p2, p6, p5, frame);
    drawSquare(scene, p2, p3, p7, p6, frame);
    drawSquare(scene, p3, p4, p8, p7, frame);
    drawSquare(scene, p4, p1, p5, p8, frame);
    drawSquare(scene, p5, p6, p7, p8, frame);
    drawSquare(scene, a1, a2, a6, a5, frame, t);
}

void drawMirror(Scene *scene) {
    Vec p1 = Vec(-400, 300, -150);
    Vec p2 = Vec(300, 300, -300);
    Vec p3 = Vec(300, 0, -300);
    Vec p4 = Vec(-400, 0, -150);
    Material mirror = Material(Vec(1, 1, 1), 1, 0, 0);
    drawSquare(scene, p1, p2, p3, p4, mirror);
}

void drawLight(Scene *scene, Vec origin, double size) {
    Material light = Material(Vec(0,0,0), 0, 0, 0, 1, Vec(4,4,4));

    Vec p1 = origin + Vec(-size, 0, size);
    Vec p2 = origin + Vec(size, 0, size);
    Vec p3 = origin + Vec(size, 0, -size);
    Vec p4 = origin + Vec(-size, 0, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

void drawLeftLight(Scene *scene, Vec origin, double size) {
    Material light = Material(Vec(0,0,0), 0, 0, 0, 1, Vec(4,4,4));

    Vec p1 = origin + Vec(0, -size, size);
    Vec p2 = origin + Vec(0, size, size);
    Vec p3 = origin + Vec(0, size, -size);
    Vec p4 = origin + Vec(0, -size, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

void drawScene(int samples) {
    Vec origin(-300, 500, 700);
    Vec dest(0, 450, 0);

    Camera camera = Camera(origin, dest, 1600, 1200, 700, 60);
    Scene scene = Scene();

    // Texture* wood_wicker = new Texture("../texture/wood_wicker.png");
    // Texture* wood_wicker_bump = new Texture("../texture/wood_wicker_bump.png");
    Texture* brick = new Texture("../texture/brick.png");
    Texture* floor = new Texture("../texture/floor.png");
    Texture* artwork = new Texture("../texture/artwork.png");
    Texture* artwork2 = new Texture("../texture/artwork2.png");

    drawArtwork(&scene, Vec(0, 500, 10), 173, 200, 20, 10, artwork);
    drawArtwork(&scene, Vec(-230, 500, 10), 123, 300, 20, 10, artwork2);
    drawRoom(&scene, Vec(0, 500, 0), 500, brick, floor);
    drawLeftLight(&scene, Vec(-499, 700, 0), 300);
    ////////////

    Renderer renderer = Renderer(&scene, &camera);
    renderer.render(samples);
    renderer.save_image("output.png");
}

int main(int argc, char *argv[]) {
    glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
    srand((unsigned int)time(NULL));
    time_t start, stop;
    time(&start);

    int samples = 100;
    if (argc == 2) samples = atoi(argv[1]);
    drawScene(samples);

    time(&stop);
    double diff = difftime(stop, start);
    int hrs = (int)diff/3600;
    int mins = ((int)diff/60)-(hrs*60);
    int secs = (int)diff-(hrs*3600)-(mins*60);
    printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);

    return 0;
}