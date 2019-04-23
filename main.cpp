#include <iostream>
#include <ctime>

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"
#include "lib/tinyobjloader/tiny_obj_loader.h"

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

  Material white = Material(Vec(0.8, 0.8, 0.8), 0, 0, 0, Vec(0,0,0));
  Material red = Material(Vec(0.8, 0, 0), 0, 0, 0, Vec(0,0,0));
  Material blue = Material(Vec(0, 0, 0.8), 0, 0, 0, Vec(0,0,0));
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

void drawLeftLight(Scene *scene, Vec origin, double size) {
    Material light = Material(Vec(0,0,0), 0, 0, 0, Vec(4,4,4));

    Vec p1 = origin + Vec(0, -size, size);
    Vec p2 = origin + Vec(0, size, size);
    Vec p3 = origin + Vec(0, size, -size);
    Vec p4 = origin + Vec(0, -size, -size);
    drawSquare(scene, p1, p2, p3, p4, light);
}

void importOBJ(Scene *scene, Vec pos, double scale) {
    std::string inputfile = "../obj/teapot.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!err.empty()) { // `err` may contain warning message.
      std::cerr << err << std::endl;
    }

    if (!ret) {
      exit(1);
    }

    Material m = Material(Vec(1, 1, 1), 0, 1, 0, Vec(0,0,0));

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
        int fv = shapes[s].mesh.num_face_vertices[f];
        vector<Vec> p_list = vector<Vec>();
        Vec n = Vec();

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {
          // access to vertex
          tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
          tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
          tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
          tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
          tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
          tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
          tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
          p_list.push_back((Vec(vx,vy,vz) + pos) * scale);
          n = n + Vec(nx, ny, nz);
          // Optional: texture coordinate
          // tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
          // tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
          // Optional: vertex colors
          // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
          // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
          // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
        }
        n = n / fv;

        scene->add( dynamic_cast<Object*>(new Triangle(p_list.at(0), p_list.at(1), p_list.at(2), m)));
        index_offset += fv;

        // per-face material
        shapes[s].mesh.material_ids[f];
      }
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    time_t start, stop;
    time(&start);

    int samples = 1000;
    if (argc == 2) samples = atoi(argv[1]);

    // First //
    // Vec origin(0, 500, 1400);
    // Vec dest(0, 500, 0);
    //
    // Camera camera = Camera(origin, dest, 500, 500, 1400, 60);
    // Scene scene = Scene();
    //
    // scene.add( dynamic_cast<Object*>(new Sphere(Vec(100,160,-300), 160, Material(Vec(1, 1, 1), 0, 0, 0, Vec(0,0,0)))) );
    // scene.add( dynamic_cast<Object*>(new Sphere(Vec(200,600,0), 120, Material(Vec(1, 1, 1), 0, 1, 0, Vec(0,0,0)))) );
    // scene.add( dynamic_cast<Object*>(new Sphere(Vec(-200,120,-200), 120, Material(Vec(1.0, 1.0, 1.0), 1, 0, 0, Vec(0,0,0)))) );
    // scene.add( dynamic_cast<Object*>(new Sphere(Vec(-200,400,1000), 120, Material(Vec(0.1, 0.75, 1.0), 1, 0, 0, Vec(0,0,0)))) );
    // drawRoom(&scene, Vec(0, 500, 0), 500);
    // drawLight(&scene, Vec(0, 999, 0), 500);
    ///////////

    // Second //
    Vec origin(0, 200, 700);
    Vec dest(0, 200, 0);

    Camera camera = Camera(origin, dest, 500, 500, 700, 60);
    Scene scene = Scene();

    // scene.add( dynamic_cast<Object*>(new Sphere(Vec(0,100,0), 100, Material(Vec(1, 0.75, 1), 0, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(250,100,0), 100, Material(Vec(1, 1, 1), 0, 1, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-250,100,0), 100, Material(Vec(1, 1, 1), 1, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(150,300,-400), 100, Material(Vec(0.2, 0.8, 0), 0.5, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-150,200,-400), 100, Material(Vec(0, 0.2, 1), 0.5, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(150,100,1000), 100, Material(Vec(0.8, 0, 0.3), 0, 0, 0, Vec(0,0,0)))) );
    scene.add( dynamic_cast<Object*>(new Sphere(Vec(-150,100,1000), 100, Material(Vec(0.2, 0.75, 0.6), 0, 0, 0, Vec(0,0,0)))) );

    drawRoom(&scene, Vec(0, 500, 0), 500);
    drawLeftLight(&scene, Vec(-499, 700, 0), 300);
    importOBJ(&scene, Vec(0, 40, 200), 1);
    //////////

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
