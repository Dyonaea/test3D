#ifndef UTIL_H
#define UTIL_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cerrno>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<stb/stb_image.h>
#include<vector>
#include <map>
#include <memory>
#include <unordered_map>
#include <FastNoiseLite/FastNoiseLite.h>
#include <future>
#include <mutex>
#include <thread>
#include <array>

enum SIDE {LEFT, RIGHT, UP, DOWN, FACE, BACK};

struct ChunkCoordHash{
    std::size_t operator()(const glm::ivec3 coord) const{
        return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y) << 1 ^ std::hash<int>()(coord.z) << 2;
    }
};

#endif