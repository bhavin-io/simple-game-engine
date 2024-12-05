#pragma once
#include "model.h"
#include <string>

class ObjLoader {
public:
    Model LoadObjFile(const std::string& filename);
};
