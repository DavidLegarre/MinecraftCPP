#pragma once

#include <glad/gl.h>

#include <string>

class Texture {
   public:
    Texture(const std::string& imagePath);
    Texture(unsigned char* data, int width, int height, int channels);
    ~Texture();

    void Bind(GLuint slot = 0) const;

    GLuint GetWidth() const;
    GLuint GetHeight() const;
    GLuint GetTextureID() const;

   private:
    GLuint m_TextureID;
    GLuint m_Width;
    GLuint m_Height;
};
