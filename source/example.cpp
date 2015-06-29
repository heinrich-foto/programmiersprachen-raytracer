#include "fensterchen.hpp"
#include "sphere.hpp"
#include "box.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  Window win(glm::ivec2(800,800));

  Box box1 {glm::vec3{0,1,2},glm::vec3{2,3,2}};
  std::cout << box1 << std::endl;

  Sphere sphere1 {0.2};
  std::cout << sphere1 << std::endl;


  /* 
  Static vs dynamic
  =================
  Static type checking means that type checking occurs at compile time.
   No type information is used at runtime in that case.
  Dynamic type checking occurs when type information is used at runtime. 
  C++ uses a mechanism called RTTI (runtime type information) to implement 
  this. The most common example where RTTI is used is the dynamic_cast operator 
  which allows downcasting of polymorphic types. Furthermore, you can use the typeid 
  operator to find out about the runtime type of objects. For example, 
  you can use it to check whether the shape in the example is a circle or a rectangle.
  */

  // Color red(255, 0, 0); 
  // glm::vec3 position(0,0);
  // std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>(position, 1.2, red, "sphere0");
  // std::shared_ptr<Shape>  s2 = std::make_shared<Sphere>(position, 1.2, red, "sphere1");
  // s1->print(std::cout); 
  // s2->print(std::cout);

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    auto t = win.getTime();
    float x1(0.5 + 0.5 * std::sin(t)); float y1(0.5 + 0.5 * std::cos(t));
    float x2(0.5 + 0.5 * std::sin(2.0*t)); float y2(0.5 + 0.5 * std::cos(2.0*t));
    float x3(0.5 + 0.5 * std::sin(t-10.f)); float y3(0.5 + 0.5 * std::cos(t-10.f));

    win.drawPoint(x1, y1, 255, 0, 0);
    win.drawPoint(x2, y2, 0, 255, 0);
    win.drawPoint(x3, y3, 0, 0, 255);

    auto m = win.mousePosition();
    win.drawLine(0.1f,0.1f, 0.8f,0.1f, 255,0,0);

    win.drawLine(0.0f, m.y, 0.01f, m.y, 0,0,0);
    win.drawLine(0.99f, m.y,1.0f, m.y, 0,0,0);

    win.drawLine(m.x, 0.0f, m.x, 0.01f, 0,0,0);
    win.drawLine(m.x, 0.99f,m.x, 1.0f, 0,0,0);

    win.update();
  }

  return 0;
}
