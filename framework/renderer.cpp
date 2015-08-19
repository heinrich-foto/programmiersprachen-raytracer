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

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      // if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
      //   p.color = Color(0.0, 1.0, float(x)/height_);
      // } else {
      //   p.color = Color(1.0, 0.0, float(y)/width_);
      // }
      // ray from camera to pixel
      Ray ray{{0,0,0},{0,0,1}};
      p.color = raytrace(ray,DETH,scene);
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray, unsigned depth, Scene const & scene) {
    Hit minHit{std::numeric_limits<double>::infinity(),"__INF__"};

    if (depth==0) {
      return Color{0,0,0};
    }
    else {
      for (auto & item : scene.shape) {
        Hit hit = item->intersect(ray);
        if (hit < minHit) {
          minHit = hit;
        }
      }
      if (minHit.hit)
      {
        // for (light: scene_.lights) { ... }
        std::cout << "HIT -- shading: " << minHit.name << std::endl;
        // return shading();
        return Color(0.5,0.5,0.5);
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
