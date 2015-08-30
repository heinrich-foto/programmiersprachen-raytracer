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
#include <glm/glm.hpp>
#include <cmath>


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
    Hit minHit{};
    Color clr;
    Color ambientColor{scene.ambientColor};

    if (depth==0) {
      return Color{0,0,0};
    }
    else {
      // for (auto const& item : scene.shape) {
      auto item = scene.get_shape("root");
        try {
          /*
          - Inverse Transformationsmatrix auf Strahl anwenden.
              instance::intersect( ray, &hit ) {
                ray_object = transform_ray( ray, M_inv )
                object->intersect( ray_object, &hit_object )
                hit = transform_hit( hit_object, M )
              }
          - Strahlposition und Strahrichtung mit Matrix multiplizieren (homogene Koordinaten!!)
          - Intersection mit transformierten Strahl durchführen.
          - Seite 26-32 in den Folien
          (Rücktransformation der Normalen mit der Transponierten Inversen)
           */

          // if (item->transformed) {
          //   ray = transform_ray(ray, M_inv);
          // }

          Hit hit = item->intersect(ray); // intersect des Composit wird aufgerufen.
          if (hit.hit()) { 
            // Ambient Light -> jedes ka eluminierende Object erhöt the Ambient Light??!
            clr += ambientColor * (hit.object())->material().ka();
          }
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
        return shading(minHit, scene.light, ray);
        // return (minHit.object())->material().kd();
      } else {
        return clr;
      }
    }
  }

  Color Renderer::shading(Hit const& hit, std::vector<Light> const& lights, Ray const& r) const {
    // shading nicht in eigener Funktion.
    // http://glm.g-truc.net/0.9.2/api/a00006.html
    Color color {0.1,0.1,0.1}; // debug color
    // Color color {0,0,0};

    glm::vec3 hitpoint = hit.hitPoint();

    for (auto& light : lights) { 
      
      glm::vec3 LightVector = glm::normalize(light.position() - hitpoint);

      float Diffuse = glm::dot(glm::normalize(hit.normalVec()),LightVector);
      
      glm::vec3 reflectionRay = {
        hit.normalVec().x*2*Diffuse-LightVector.x,
        hit.normalVec().y*2*Diffuse-LightVector.y,
        hit.normalVec().z*2*Diffuse-LightVector.z
      };

      float Spekular = std::pow(
            glm::dot(glm::normalize(reflectionRay),glm::normalize(r.direction))
          , hit.object()->material().m()
        );

      if (Diffuse > 0.0f && Diffuse < 1) {
        // if(Material.isDiffuse())
        
        color += light.ambient() * hit.object()->material().ka() 
               + light.diffuse() * hit.object()->material().kd() * Diffuse
               + 1 /* /(distance*distance) */ * hit.object()->material().ks() * Spekular;
      } else {
        return color;
      }
    }

    return color;
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
