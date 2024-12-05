#pragma once

const char *FRAGMENT_SHADER = R"(

#version 410
in vec3 vColor;
out vec4 fragColor;
void main() {
fragColor = vec4(vColor, 1.0);
// fragColor = vec4(0.4, 0.5, 0.6, 1.4);
}
)";