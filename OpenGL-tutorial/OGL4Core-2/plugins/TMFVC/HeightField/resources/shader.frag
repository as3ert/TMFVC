#version 450

#define M_PI 3.14159265358979323846

uniform sampler2D tex;     // The height field, which contains the height in meters (float) for each point.
uniform ivec2 texSize;     // The width and height of the field.
uniform float hMin;        // Minimum height that occurs in the texture.
uniform float hMax;        // Maximum height that occurs in the texture.
uniform float lengthScale; // Length of a single pixel in meters.
uniform int filterId;      // Rendering mode (gray = 0, normal = 1, etc.)
uniform vec3 lightDir;     // The direction of the incident light.

in vec2 texCoords;

layout(location = 0) out vec4 fragColor;

/**
 * Fetches the height at a point.
 */
float fetch(ivec2 tc) {
    return texelFetch(tex, tc, 0).r;
}

vec3 normal(ivec2 tc) {
    vec3 n = vec3(0.0f);

    // TODO

    return n;
}

vec2 principalCurvature(ivec2 coords) {
    vec2 pcurv = vec2(0.0f);

    // TODO

    return pcurv;
}

void main() {
    vec4 color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    ivec2 tc = ivec2(texCoords * texSize); // Integer (pixel) texture coordinates.

    // ------------------------------------------------------------
    //   Enter your visualization code here (calculate/set color):
    // ------------------------------------------------------------

    // TODO
    if (filterId == 0) {
        float h = (texture(tex, texCoords).r - hMin) / (hMax - hMin); // Height mapped to [0; 1] range.
        color = vec4(vec3(h), 1.0f);
    }
    fragColor  = color;
}
