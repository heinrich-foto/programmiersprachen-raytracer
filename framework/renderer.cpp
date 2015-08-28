// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "sdfloader.hpp"

#include <limits>

unsigned DETH = 4;

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{ }

unsigned Renderer::width() const {
  return width_;
}
unsigned Renderer::height() const {
  return height_;
}

void Renderer::render(Scene const& scene)
{
  // std::cout << "Start renderer..." << std::endl;
  // for (auto const& item : scene.material) std::cout << item << std::endl;
  // for (auto const& item : scene.shape) std::cout << item <<  " " << *item << std::endl;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      Pixel p(x,y);

      Ray ray{scene.camera.compute_ray(p,height_,width_)};  
      // std::cout << width_ << " " << x << " " << y << " " << ray;         
      p.color = raytrace(ray,DETH,scene);
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray, unsigned depth, Scene const & scene) {
    // Hit minHit{false, std::numeric_limits<double>::infinity(), {0,0,0}, nullptr};
    Hit minHit{};

    if (depth==0) {
      return Color{0,0,0};
    }
    else {
      // for (auto const& item : scene.shape) {
      auto item = scene.get_shape("root");
        try {
          /*
          - Inverse Transformationsmatrix auf Strahl anwenden.
          - Strahlposition und Strahrichtung mit Matrix multiplizieren (homogene Koordinaten!!)
          - Intersection mit transformierten Strahl durchführen.
          - Seite 26-32 in den Folien
          (Rücktransformation der Normalen mit der Transponierten Inversen)
           */
          Hit hit = item->intersect(ray); // intersect des Composit wird aufgerufen.
          
          if (hit.hit() && hit < minHit) { // if (hit)
            minHit = hit;
          }
        } catch (...) {
          std::cout << "Bad weak" << std::endl;
          return Color(0.0,0.9,0.1);
        }
      // } // for statement
      if (minHit.hit())
      {
        // for (light: scene_.lights) { ... }
        // std::cout << "HIT -- shading: " << minHit.object << std::flush;
        // return shading();
        return (scene.get_shape(minHit.object()))->material().ka();
      } else {
        return scene.ambientColor;
      }
    }
  }

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : " 
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
