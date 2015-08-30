// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  unsigned width() const;
  unsigned height() const;
  
  void render(Scene const& scene);
  Color raytrace(Ray const& ray, unsigned depth, Scene const& scene);
  Color shading(Hit const& hit, std::vector<Light> const& lights, Ray const& ray) const;
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_; // outputfile
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
