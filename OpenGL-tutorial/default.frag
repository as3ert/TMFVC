#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs from the Vertex Shader
in vec3 color;          // Color input
in vec2 texCoord;      // Texture coordinates input

// Texture sampler
uniform sampler2D tex0;

void main()
{
    // Sample the texture using the provided texture coordinates
    FragColor = texture(tex0, texCoord);
}