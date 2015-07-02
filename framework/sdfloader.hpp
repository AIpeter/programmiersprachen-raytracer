#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "scene.hpp"

Scene* loadSDF(std::string const& file);

#endif