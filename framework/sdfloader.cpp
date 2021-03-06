#include "sdfloader.hpp"

std::shared_ptr<Scene> loadSDF(std::string const& file) {
        std::shared_ptr<Scene> out = std::make_shared<Scene>();
        std::ifstream sdf;
        std::vector<std::string> lines;
        sdf.open(file);
        if(sdf.is_open()) {
                std::string line;
                while(getline(sdf, line)) {
                        lines.push_back(line);
                }
                sdf.close();
        }
        else {
                std::cout << "File could not be opened!" << std::endl;
                return out;
        }

        int i = 0;

        for (auto line : lines) {
                i++;
                std::stringstream stream(line);
                std::string word;
                std::vector<std::string> words;
                while(stream.good()) {
                        stream >> word;
                        words.push_back(word);
                }

                if(words[0] == "#") {}
                
                else if(words[0] == "define") {
                        if(words[1] == "material") {
                                Color ka{std::stof(words[3]), 
                                        std::stof(words[4]),
                                        std::stof(words[5])};
                                Color kd{std::stof(words[6]), 
                                        std::stof(words[7]),
                                        std::stof(words[8])};
                                Color ks{std::stof(words[9]), 
                                        std::stof(words[10]),
                                        std::stof(words[11])};
                                out->materials[words[2]] = Material{words[2],
                                        ka, kd, ks, std::stof(words[12])};
                        }
                        else if(words[1] == "shape") {
                                if(words[2] == "sphere") {
                                        glm::vec3 center{std::stof(words[4]),
                                                std::stof(words[5]),
                                                std::stof(words[6])};
                                        out->shapes[words[3]] = std::make_shared<Sphere>(center,
                                                std::stof(words[7]), words[3],
                                                out->materials[words[8]]);
                                }
                                else if(words[2] == "box") {
                                        glm::vec3 min{std::stof(words[4]),
                                                std::stof(words[5]),
                                                std::stof(words[6])};
                                        glm::vec3 max{std::stof(words[7]),
                                                std::stof(words[8]),
                                                std::stof(words[9])};
                                        out->shapes[words[3]] = std::make_shared<Box>(min, max,
                                                words[3],
                                                out->materials[words[10]]);
                                }
                                else if(words[2] == "triangle") {
                                        glm::vec3 left{std::stof(words[4]),
                                                std::stof(words[5]),
                                                std::stof(words[6])};
                                        glm::vec3 right{std::stof(words[7]),
                                                std::stof(words[8]),
                                                std::stof(words[9])};
                                        glm::vec3 top{std::stof(words[10]),
                                                std::stof(words[11]),
                                                std::stof(words[12])};
                                        out->shapes[words[3]] = std::make_shared<Triangle>(left, 
                                                right, top, words[3], out->materials[words[13]]);
                                }
                                else {
                                        std::cout << "Syntax error in line " << 
                                        i << "!" << std::endl;
                                        std::cout << "Unknown object: " <<
                                        words[2] << std::endl;
                                }
                        }
                        else if(words[1] == "camera") {
                                glm::vec3 eye{std::stof(words[4]),
                                                std::stof(words[5]),
                                                std::stof(words[6])};
                                glm::vec3 dir{std::stof(words[7]),
                                                std::stof(words[8]),
                                                std::stof(words[9])};
                                glm::vec3 up{std::stof(words[10]),
                                                std::stof(words[11]),
                                                std::stof(words[12])};
                                out->cameras[words[2]] = Camera{words[2],
                                                        std::stof(words[3]),
                                                        eye, dir, up};
                        }
                        else if(words[1] == "light") {
                                glm::vec3 pos{std::stof(words[3]),
                                        std::stof(words[4]),
                                        std::stof(words[5])};
                                Color La{std::stof(words[6]),
                                        std::stof(words[7]),
                                        std::stof(words[8])};
                                Color Ld{std::stof(words[9]),
                                        std::stof(words[10]),
                                        std::stof(words[11])};
                                out->lights.push_back(Light{words[3], pos, La,
                                        Ld});
                        }
                        else {
                                std::cout << "Syntax error in line " << i <<
                                "!" << std::endl;
                                std::cout << "Unknown object: " << words[1] <<
                                std::endl;
                        }
                }
                
                else if(words[0] == "render")
                {
                        if(words.size() == 6) 
                        {
                                bool aa = false;
                                if(words[5] == "aa")
                                {
                                        aa = true;
                                }
                                else if(words[5] == "noaa")
                                {
                                        aa = false;
                                }
                                else
                                {
                                        std::cout << "Syntax error in line "
                                        << i << "!" << std::endl;
                                        std::cout << "Unknown expression: "
                                        << words[5] << std::endl;
                                        std::cout << "Defaulting to no AA."
                                        << std::endl;
                                }
                                out->render = Renderer
                                {
                                        (unsigned int) std::stof(words[3]),
                                        (unsigned int) std::stof(words[4]), 
                                        words[2],
                                        out->cameras[words[1]],
                                        aa
                                };
                        }
                        else
                        {
                                std::cout << "Syntax error in line " << i
                                << "!" << std::endl;
                                std::cout << "Invalid number of arguments."
                                << std::endl;
                        }      
                }

                else if(words[0] == "transform") {
                        if(words[2] == "scale"){
                                if(words.size() == 4) {
                                        glm::vec3 scale{std::stof(words[3]),
                                                        std::stof(words[3]),
                                                        std::stof(words[3])};
                                        out->shapes[words[1]]->scale(scale);
                                }
                                else if(words.size() == 6) {
                                        glm::vec3 scale{std::stof(words[3]),
                                                        std::stof(words[4]),
                                                        std::stof(words[5])};
                                        out->shapes[words[1]]->scale(scale);
                                }
                                else {
                                        std::cout << "Syntax error in line "
                                        << i << "!" << std::endl;
                                        std::cout <<
                                        "Invalid number of arguments." <<
                                        std::endl;
                                }
                        }
                        else if(words[2] == "translate") {
                                glm::vec3 direction{std::stof(words[3]),
                                                std::stof(words[4]),
                                                std::stof(words[5])};
                                out->shapes[words[1]]->translate(direction);
                        }
                        else if(words[2] == "rotate") {
                                glm::vec3 axis{std::stof(words[4]),
                                                std::stof(words[5]),
                                                std::stof(words[6])};
                                out->shapes[words[1]]->rotate(
                                                        (std::stof(words[3])
                                                        * (M_PI/180.0f)),
                                                        axis);
                        }
                        else {
                                std::cout << "Syntax error in line " << i << "!" <<
                                std::endl;
                                std::cout << "Unknown object: " << words[2] <<
                                std::endl;
                        }
                }
                     
                else {
                        std::cout << "Syntax error in line " << i << "!" <<
                        std::endl;
                        std::cout << "Unknown object: " << words[0] <<
                        std::endl;
                }       
        }
        return out;
}