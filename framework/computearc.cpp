#include "computearc.hpp"

float computeDiffuseArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  //std::cout << "SurfacePoint: " << surfacePoint.x << surfacePoint.y << surfacePoint.z << std::endl;
  Ray n{sphere.center(), sphere.center() - surfacePoint}; //Normalenvektor
  Ray l{surfacePoint, surfacePoint - light.getposition()};
  float n_length = glm::length(n.direction);
  float l_length = glm::length(l.direction);
  float diffuseArc = (std::max(glm::dot(n.direction, l.direction), 0.0f))/(n_length*l_length);
  /*
  float deg = (360.0 / (2*M_PI)) * arc;
  std::cout << "Arc: " << deg << "°" << "\n";
  */
  /*
  if(glm::sin(diffuseArc) >= 0) 
  {
    return glm::cos(diffuseArc);
  }
  else 
  {
    return (0 - glm::cos(diffuseArc));
  }
  */
  return diffuseArc;
}

float computeSpecularArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  Ray n{sphere.center(), glm::normalize(sphere.center() - surfacePoint)}; //Normalenvektor
  Ray l{surfacePoint, glm::normalize(surfacePoint - light.getposition())};
  // glm::vec3 s = glm::reflect(l.direction, n.direction);
  /*
  glm::vec3 s{n.direction.x - l.direction.x + n.direction.x,
              n.direction.y - l.direction.y + n.direction.y,
              n.direction.z - l.direction.z + n.direction.z};
  */
  //glm::vec3 s = (2 * glm::dot(l.direction, n.direction))*n.direction - l.direction;
  glm::vec3 s = (2 * std::max(glm::dot(n.direction, l.direction), 0.0f))*n.direction - l.direction;
  s = glm::normalize(s);
  auto c = glm::normalize(r.direction);
  float specularCos = glm::dot(s, c);
  float specularArc = glm::acos(specularCos);
  float specularSin = glm::sin(specularArc);
  // std::cout << specularArc << std::endl;
  if(specularSin > 0) 
  {
    return specularCos;
  }
  else 
  {
    return (0 - specularCos);
  }
  

  /*
  float n_length = glm::length(n.direction);
  float r_length = glm::length(r.direction);
  // Winkel zwischen cameraRay und Normalenvektor minus Winkel zwischen Lichtquelle und Normalenvektor
  float specularArc = ((glm::dot(n.direction, r.direction))/(n_length*r_length))
                      - (computeDiffuseArc(sphere, d, r, light));
  //specularArc = glm::cos(specularArc);
  */
}

float computeDiffuseArc(Box const& box, float & d, Ray const& r, Light const& light)
{
  glm::vec3 n;
  glm::vec3 surfacePoint{d*r.direction};
  //std::cout << "d: " << d << std::endl;
  // std::cout << surfacePoint.x << ", " << surfacePoint.y << ", " << surfacePoint.z << std::endl;
  Ray l{surfacePoint, surfacePoint - light.getposition()};

//test x plane
  if( surfacePoint.y >= box.min().y &&
      surfacePoint.y <= box.max().y &&
      surfacePoint.z >= box.min().z &&
      surfacePoint.z <= box.max().z)
  {
    if (surfacePoint.x < box.max().x)
    {//if surfacepoint on x-min-plane glm::vec3 n{-1, 0, 0}
      n = glm::normalize(glm::vec3{box.min().x, box.max().y, box.max().z}-box.max());
    }
    if (surfacePoint.x > box.min().x)
    { //if surfacepoint on x-max-plane glm::vec3 n{1, 0, 0}
      n = glm::normalize(box.max() - glm::vec3{box.min().x, box.max().y, box.max().z});
    }
  }
  //test y plane
  if( surfacePoint.x <= box.max().x &&
    surfacePoint.x >= box.min().x &&
    surfacePoint.z <= box.max().z &&
    surfacePoint.z >= box.min().z)
  {
    if(surfacePoint.y < box.max().y)
    { //if surfpoint on y-min-plane:
      n = glm::normalize(glm::vec3{box.max().x, box.min().y, box.max().z} - box.max());
    }
    if(surfacePoint.y > box.min().y)
    { //if surfpoint on y-max plane
      n = glm::normalize(box.max() - glm::vec3{box.max().x, box.min().y, box.max().z});
    }
    //std::cout << "i'm here" << std::endl;
    
  }

//tests z plane
  if (surfacePoint.x <= box.max().x &&
    surfacePoint.x >= box.min().x &&
    surfacePoint.y <= box.max().y &&
    surfacePoint.y >= box.min().y)
  {
    if(surfacePoint.z < box.max().z)
    {
      //if on z min plane:
      n = glm::normalize(glm::vec3{box.max().x, box.max().y, box.min().z} - box.max());
    }
    if(surfacePoint.z > box.min().z)
    { //if on z max plane
      n = glm::normalize(box.max() - glm::vec3{box.max().x, box.max().y, box.min().z});
    }
  }


  // std::cout << n.x << n.y << n.z << std::endl;
  float n_length = glm::length(n);
  float l_length = glm::length(l.direction);
  float diffuseArc = (std::max(glm::dot(n, l.direction), 0.0f))/(n_length*l_length);
  if (!(glm::isnan(diffuseArc))) {
    std::cout << "diffusearc: " << diffuseArc << std::endl;
  }
  return diffuseArc;
}

float computeSpecularArc(Box const& box, float & d, Ray const& r, Light const& light)
{

}

float computeDiffuseArc(Triangle const& triangle, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  //std::cout << "SurfacePoint: " << surfacePoint.x << surfacePoint.y << surfacePoint.z << std::endl;
  glm::vec3 right{triangle.getright().x - triangle.getleft().x,
              triangle.getright().y - triangle.getleft().y, 
              triangle.getright().z - triangle.getleft().z}; // direction of triangleplane
  glm::vec3 top{triangle.gettop().x - triangle.getleft().x,  
              triangle.gettop().y - triangle.getleft().y,
              triangle.gettop().z - triangle.getleft().z}; // direction of triangleplane
  glm::vec3 n = glm::cross(right, top);//Normalenvektor
  Ray l{surfacePoint, surfacePoint - light.getposition()};
  float n_length = glm::length(n);
  float l_length = glm::length(l.direction);
  float diffuseArc = (std::max(glm::dot(n, l.direction), 0.0f))/(n_length*l_length);

  return diffuseArc;
}

float computeSpecularArc(Triangle const& triangle, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  glm::vec3 right{triangle.getright().x - triangle.getleft().x,
              triangle.getright().y - triangle.getleft().y, 
              triangle.getright().z - triangle.getleft().z}; // direction of triangleplane
  glm::vec3 top{triangle.gettop().x - triangle.getleft().x,  
              triangle.gettop().y - triangle.getleft().y,
              triangle.gettop().z - triangle.getleft().z}; // direction of triangleplane
  glm::vec3 n = glm::cross(right, top);//Normalenvektor
  Ray l{surfacePoint, glm::normalize(surfacePoint - light.getposition())};
  // glm::vec3 s = glm::reflect(l.direction, n.direction);
  /*
  glm::vec3 s{n.direction.x - l.direction.x + n.direction.x,
              n.direction.y - l.direction.y + n.direction.y,
              n.direction.z - l.direction.z + n.direction.z};
  */
  //glm::vec3 s = (2 * glm::dot(l.direction, n.direction))*n.direction - l.direction;
  glm::vec3 s = (2 * std::max(glm::dot(n, l.direction), 0.0f))*n - l.direction;
  s = glm::normalize(s);
  auto c = glm::normalize(r.direction);
  float specularCos = glm::dot(s, c);
  float specularArc = glm::acos(specularCos);
  float specularSin = glm::sin(specularArc);
  // std::cout << specularArc << std::endl;
  if(specularSin > 0) 
  {
    return specularCos;
  }
  else 
  {
    return (0 - specularCos);
  }
}


