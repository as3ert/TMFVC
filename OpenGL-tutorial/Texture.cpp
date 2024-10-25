#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    // Assign the type of the texture to the texture object
    type = texType;

    // Variables to store the width, height, and number of color channels of the image
    int widthImg, heightImg, numColCh;

    // Flip the image vertically so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    
    // Read the image from a file and store it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
    if (!bytes) {
        std::cerr << "Failed to load texture: " << image << std::endl;
        return; // Early return if loading fails
    }

    // Generate an OpenGL texture object
    glGenTextures(1, &ID);
    
    // Assign the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Configure texture filtering
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Configure texture wrapping
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Assign the image to the OpenGL Texture object
    GLenum internalFormat = (numColCh == 3) ? GL_RGB : GL_RGBA; // Choose format based on channels
    glTexImage2D(texType, 0, internalFormat, widthImg, heightImg, 0, internalFormat, pixelType, bytes);

    // Generate mipmaps
    glGenerateMipmap(texType);

    // Free the image data as it is now in the OpenGL Texture object
    stbi_image_free(bytes);

    // Unbind the OpenGL Texture object
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    // Get the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.shader_id, uniform);
    if (texUni == -1) {
        std::cerr << "Warning: uniform '" << uniform << "' not found in shader!" << std::endl;
        return; // Return if uniform location is invalid
    }

    // Activate the shader before changing the value of a uniform
    shader.init(); // Assuming Init activates the shader

    // Set the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::bind() {
    glBindTexture(type, ID);
}

void Texture::unbind() {
    glBindTexture(type, 0);
}

void Texture::deleteTex() {
    glDeleteTextures(1, &ID);
}