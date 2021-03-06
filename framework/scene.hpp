#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <vector>
#include <map>
#include <memory>
#include "material.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "renderer.hpp"

struct Scene {
        std::map<std::string, Material> materials;
        std::map<std::string, std::shared_ptr<Shape>> shapes;
        std::vector<Light> lights;
        std::map<std::string, Camera> cameras;
        Renderer render;
};


#endif // BUW_SCENE_HPP