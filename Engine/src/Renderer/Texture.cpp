#include "Renderer/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

Texture::Texture(const std::string& imagePath)
    : m_TextureID(0), m_Width(0), m_Height(0) {
    int width, height, channels;

    // Load image from file
    unsigned char* imageData =
        stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

    if (!imageData) {
        throw std::runtime_error(std::string("Failed to load image: ") +
                                 imagePath);
    }

    m_Width = static_cast<GLuint>(width);
    m_Height = static_cast<GLuint>(height);

    // Create OpenGL texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determine format based on number of channels
    GLenum format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    } else if (channels == 1) {
        format = GL_RED;
    }

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format,
                 GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free image data
    stbi_image_free(imageData);
}

Texture::Texture(unsigned char* data, int width, int height, int channels)
    : m_TextureID(0), m_Width(static_cast<GLuint>(width)), m_Height(static_cast<GLuint>(height)) {
    if (!data) {
        throw std::runtime_error("Texture data is null");
    }

    // Create OpenGL texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Set texture parameters to NEAREST for crisp pixel-art appearance
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Determine format based on number of channels
    GLenum format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    } else if (channels == 1) {
        format = GL_RED;
    }

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() { glDeleteTextures(1, &m_TextureID); }

void Texture::Bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

GLuint Texture::GetWidth() const { return m_Width; }

GLuint Texture::GetHeight() const { return m_Height; }

GLuint Texture::GetTextureID() const { return m_TextureID; }
