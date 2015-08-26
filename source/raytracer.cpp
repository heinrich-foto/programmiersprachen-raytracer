#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <sdfloader.hpp>

int main(int argc, char* argv[])
{
  unsigned width = 600;
  unsigned height = 600;
  std::string const filename = "./sinnlos_wird_ueberschrieben.ppm";

  Renderer app(width, height, filename);
    
  std::string sdfFileName = "../";
  if (argc == 2) {
    sdfFileName += argv[1];
  } else {
    sdfFileName += "sdf_scene_test.sdf";
  }
  std::cout << "Starting Raytracer with this SDF File: " << sdfFileName << std::endl << std::endl;
  auto SDF = SDFLoader::instance();
  Scene scene = SDF->load(sdfFileName);

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
