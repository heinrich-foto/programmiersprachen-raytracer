#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer app(width, height, filename);

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));
  std::cout << width << " " << height << std::endl;
  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }
    // win.drawLine(0.1f,0.1f, 0.8f,0.1f, 255,0,0);
    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
