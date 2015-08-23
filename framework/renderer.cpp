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

void Renderer::render(Scene const & scene)
{
  // const std::size_t checkersize = 20;
  std::cout << "Start renderer..." << std::endl;
  for (auto const& item : scene.material) std::cout << item << std::endl;
  for (auto const& item : scene.shape) std::cout << item <<  " " << *item << std::endl;
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

                Pixel p(x,y);

                Ray ray{{},{}};
                int FovX = 60;
                ray.direction.x = -int(scene.resX)/2.0f+x; 
                ray.direction.y = -int(scene.resY)/2.0f+y;
                ray.direction.z = -int(scene.resX)/tan(FovX*M_PI/180);;
      p.color = raytrace(ray,DETH,scene);
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray, unsigned depth, Scene const & scene) {
    // Hit minHit{false, std::numeric_limits<double>::infinity(), {0,0,0}, {0,0,0}, nullptr};
    Hit minHit{false, std::numeric_limits<double>::infinity(), {0,0,0}, {0,0,0}, "nullptr"};

    if (depth==0) {
      return Color{0,0,0};
    }
    else {
      for (auto const& item : scene.shape) {
        try {
          Hit hit = item->intersect(ray);
          
          if (hit.hit && hit < minHit) {
            minHit = hit;
          }
        } catch (...) {
          std::cout << "Bad weak" << std::endl;
          return Color(0.0,0.9,0.1);
        }
      }
      if (minHit.hit)
      {
        // for (light: scene_.lights) { ... }
        // std::cout << "HIT -- shading: " << minHit.object << std::flush;
        // return shading();
        return (scene.get_shape(minHit.object))->material().ka();
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
