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

    float heightLeft = fetch(tc - ivec2(1, 0));
    float heightRight = fetch(tc + ivec2(1, 0));
    float heightUp = fetch(tc + ivec2(0, 1));
    float heightDown = fetch(tc - ivec2(0, 1));
    float heightCenter = fetch(tc);

    // Calculate the normal using the central difference method
    vec3 t_x = vec3(2.0f, 0.0f, (heightRight - heightLeft) / lengthScale);
    vec3 t_y = vec3(0.0f, 2.0f, (heightUp - heightDown) / lengthScale);

    n = normalize(cross(t_x, t_y));

    return n;
}

vec2 principalCurvature(ivec2 tc) {
    vec2 pcurv = vec2(0.0f);

    float heightLeft = fetch(tc - ivec2(1, 0));
    float heightRight = fetch(tc + ivec2(1, 0));
    float heightUp = fetch(tc + ivec2(0, 1));
    float heightDown = fetch(tc - ivec2(0, 1));
    float heightCenter = fetch(tc);

    // Calculate the hessian matrix
    float h_xx = (heightLeft - 2.0f * heightCenter + heightRight) / (lengthScale * lengthScale);
    float h_yy = (heightDown - 2.0f * heightCenter + heightUp) / (lengthScale * lengthScale);
    float h_xy = (heightLeft + heightRight - heightUp - heightDown) / (4.0f * lengthScale * lengthScale);

    // Calculate the eigenvalues
    float eigenvalue1 = 0.5f * (h_xx + h_yy + sqrt((h_xx - h_yy) * (h_xx - h_yy) + 4.0f * h_xy * h_xy));
    float eigenvalue2 = 0.5f * (h_xx + h_yy - sqrt((h_xx - h_yy) * (h_xx - h_yy) + 4.0f * h_xy * h_xy));

    pcurv = vec2(eigenvalue1, eigenvalue2);

    return pcurv;
}

void main() {
    vec4 color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    ivec2 tc = ivec2(texCoords * texSize); // Integer (pixel) texture coordinates.

    // ------------------------------------------------------------
    //   Enter your visualization code here (calculate/set color):
    // ------------------------------------------------------------

    if (filterId == 0) {
        float h = (texture(tex, texCoords).r - hMin) / (hMax - hMin); // Height mapped to [0; 1] range.
        color = vec4(vec3(h), 1.0f);
    } else if (filterId == 1) {
        vec3 n = normal(tc);
        color = vec4(vec3(n), 1.0f);
    } else if (filterId == 2) {
        vec3 n = normal(tc);
        float h = dot(n, lightDir);
        color = vec4(vec3(h), 1.0f);
    } else {
        vec2 pcurv = principalCurvature(tc);
        float h = (pcurv.x + pcurv.y) * 0.5f;
        color = vec4(vec3(h), 1.0f);
    }

    fragColor  = color;
}
