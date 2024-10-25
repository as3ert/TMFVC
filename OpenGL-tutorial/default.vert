#version 410 core

// Vertex Attributes
layout (location = 0) in vec3 aPos;       // Positions/Coordinates
layout (location = 1) in vec3 aColor;     // Colors
layout (location = 2) in vec2 aTex;       // Texture Coordinates

// Outputs to the Fragment Shader
out vec3 color;        // Color output
out vec2 texCoord;    // Texture coordinates output

// Uniforms
uniform float scale;  // Controls the scale of the vertices
uniform float aspect_ratio; // Aspect ratio of the window

void main()
{
    vec3 pos = aPos;
    pos.x /= aspect_ratio;  // Scale the x-component by the aspect ratio
    
    // Scale the vertex positions
    gl_Position = vec4(pos * scale, 1.0);  // Scale all components by the uniform scale
    
    // Pass through color
    color = aColor;

    // Pass through texture coordinates
    texCoord = aTex;
}