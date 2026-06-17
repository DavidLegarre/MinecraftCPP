#include <iostream>
#include "stb_image.h"

unsigned char* load_stone_image(int& width, int& height, int& channels) {
    const char* path = "assets/textures/blocks/stone.png";
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    return data;
}