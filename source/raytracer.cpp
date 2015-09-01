#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <sdfloader.hpp>

int main(int argc, char* argv[])
{
  std::string sdfFileName = "../";
  if (argc >= 2) {
    sdfFileName += argv[1];
  } else {
    sdfFileName += "sdf_scene_test.sdf";
  }
  std::cout << "Starting Raytracer with this SDF File: " << sdfFileName << std::endl << std::endl;
  auto SDF = SDFLoader::instance();
  Scene scene = SDF->load(sdfFileName);

  if (argc >= 3) {
    scene.SSAA_=std::stof(argv[2]);
  } else {
    scene.SSAA_=1;
  }
  unsigned width = scene.resX;
  unsigned height = scene.resY;
  std::string const filename = scene.filename;
  
  Renderer app(width, height, filename);
  std::thread thr([&app,&scene]() { app.render(scene); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
