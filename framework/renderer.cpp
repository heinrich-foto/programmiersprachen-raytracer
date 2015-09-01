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

#if defined(ENABLE_OPENMP)
#include <omp.h>
#else
typedef int omp_int_t;
inline omp_int_t omp_get_thread_num() { return 0;}
inline omp_int_t omp_get_max_threads() { return 1;}
#endif


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
  scene_ = std::make_shared<Scene> (scene);
  // std::cout << "Start renderer..." << std::endl;
  // for (auto const& item : scene.material) std::cout << item << std::endl;
  // for (auto const& item : scene.shape) std::cout << item <<  " " << *item << std::endl;
  #pragma omp parallel for
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      Pixel p(x,y);
      
      Ray ray{scene_->camera.compute_ray(p,height_,width_)};  
      // std::cout << width_ << " " << x << " " << y << " " << ray; 

      if (scene_->SSAA_>0){//SSAA Supersampling (Jiggle)
      int samples = sqrt(scene_->SSAA_);
        for (int xAA=1;xAA<samples+1;++xAA){
          for (int yAA=1;yAA<samples+1;++yAA){
            float xA = ray.direction.x +(float) (xAA)/(float)samples-0.5f; 
            float yA = ray.direction.y +(float) (yAA)/(float)samples-0.5f;
            float zA = ray.direction.z;
            Ray aaRay{ray.origin, {xA,yA,zA}};
            p.color +=raytrace(aaRay,DETH);
          }
        }
      }
      if (scene_->SSAA_>0) {
        p.color /=scene_->SSAA_;
      } else {
        p.color +=raytrace(ray,DETH);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray, unsigned depth) {
    Color clr;
    Color ambientColor{scene_->ambientColor}; // not used

    if (depth==0) {
      return Color{0,0,0};
    }
    else {

          Hit hit = intersect(ray, depth); 

      if (hit.hit())
      {
        return shading(hit, scene_->light, ray);
        // return (minHit.object())->material().kd();
      } else {
        return clr;
      }
    }
  }

Hit Renderer::intersect(Ray const& ray, unsigned depth) const {
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
          // } (Gehört in Composite)
  auto item = scene_->get_shape("root");
  try { // intersect des Composit wird aufgerufen.
  Hit hit = item->intersect(ray);
  return (hit.hit()==true)? hit : Hit {};
  } catch (...) {
          std::cout << "Bad weak Pointer in Intersection." << std::endl;
          return Hit {};
  }
}

  Color Renderer::shading(Hit const& hit, std::vector<Light> const& lights, Ray const& r) const {
    // shading nicht in eigener Funktion.
    // http://glm.g-truc.net/0.9.2/api/a00006.html
    // http://graphics.ucsd.edu/courses/cse168_s06/ucsd/lecture01.pdf
    // http://graphics.ucsd.edu/courses/cse168_s06/
    // Color color {0.1,0.1,0.1}; // debug color
    Color color {0,0,0};

    glm::vec3 hitpoint = hit.hitPoint();

    for (auto& light : lights) { 
      
      glm::vec3 LightVector = glm::normalize(light.position() - hitpoint);

      float Diffuse = std::max(0.0f,glm::dot(glm::normalize(hit.normalVec()),LightVector));
      
      glm::vec3 reflectionRay = {
        hit.normalVec().x*2*Diffuse-LightVector.x,
        hit.normalVec().y*2*Diffuse-LightVector.y,
        hit.normalVec().z*2*Diffuse-LightVector.z
      };

      // float Specular = std::pow(
      //       glm::dot(glm::normalize(reflectionRay),glm::normalize(r.direction))
      //     , hit.object()->material().m()
      //   );

      // Ambient Light
      color += light.ambient() * hit.object()->material().ka(); 

      // Shadow?
      glm::vec3 epsilonPosition = hitpoint +0.0001f*glm::normalize(hitpoint);
      Ray LightRay {hitpoint, LightVector};
      LightRay.max_t = glm::length(light.position()-hitpoint);
      Hit shadow = intersect(LightRay,1);
      if ((!shadow.hit())&&(Diffuse > 0.0f && Diffuse < 1)) {
      // if ((Diffuse > 0.0f && Diffuse < 1)) {
        // Diffuse
        // if(Material.isDiffuse())

        color += light.diffuse() * hit.object()->material().kd() * Diffuse;
               // + 1 /* /(distance*distance) */ * hit.object()->material().ks() * Spekular;
               //+ hit.object()->material().ks() * Spekular;
      } 
      // Spekular
      glm::vec3 Reflect = glm::reflect(LightVector,hit.normalVec());
      // glm::vec3 Reflect = glm::reflect(-LightVector,hit.normalVec());
      float Dot = std::max(0.0f,glm::dot(Reflect, glm::normalize(r.direction)));

      float Base = Dot > 0.0f ? Dot : 0.0f;
      float Specular = glm::pow(Base, hit.object()->material().m());
      color += hit.object()->material().ks() * Specular;
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
