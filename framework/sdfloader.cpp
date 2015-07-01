#include "sdfloader.hpp"

std::vector<Material> loadSDF(std::string const& file) {
        std::vector<Material> out;
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

        for (auto line : lines) {
                std::stringstream stream(line);
                std::string word;
                std::vector<std::string> words;
                while(stream.good()) {
                        stream >> word;
                        words.push_back(word);
                }

                if(words[0] == "#") {}
                
                if(words[0] == "define") {
                        if(words[1] == "material") {
                                std::string name = words[2];
                                Color ka{std::stof(words[3]), 
                                        std::stof(words[4]),
                                        std::stof(words[5])};
                                Color kd{std::stof(words[6]), 
                                        std::stof(words[7]),
                                        std::stof(words[8])};
                                Color ks{std::stof(words[9]), 
                                        std::stof(words[10]),
                                        std::stof(words[11])};
                                float m = std::stof(words[12]);
                                out.push_back(Material{name, ka, kd, ks, m});
                        }
                }
        }
        return out;
}