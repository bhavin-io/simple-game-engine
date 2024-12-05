#pragma once

const char *VERTEX_SHADER = R"(
#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 textureCoordinate;

out vec3 vColor;

uniform vec3 lights[20];
uniform int num_lights;
uniform mat4 model_transform;
uniform mat4 view_transform;

float near = -0.1;
float far = -50.0;
float left = -0.0552;
float right = -left;
float top = 0.0414;
float bottom = -top;

vec3 Kd = vec3(0.2);
vec3 Ld = vec3(0.2);

mat4 ortho() {
  float v11 = 2 / (right - left);
  float v22 = 2 / (top - bottom);
  float v33 = 2 / (near - far);
  float v14 = -(right + left) / (right - left);
  float v24 = -(top + bottom) / (top - bottom);
  float v34 = -(near + far) / (near - far);

  mat4 m = mat4(v11, 0.0, 0.0, 0.0,
                0.0, v22, 0.0, 0.0,
                0.0, 0.0, v33, 0.0,
                v14, v24, v34, 1.0);

  return m;
}

mat4 perspective() {
  float absn = abs(near);
  float absf = abs(far);
  float v11 = (2 * absn) / (right - left);
  float v22 = (2 * absn) / (top - bottom);
  float v33 = (absn + absf) / (absn - absf);
  float v34 = (2 * absf * absn) / (absn - absf);
  float v13 = (right + left) / (right - left);
  float v23 = (top + bottom) / (top - bottom);

  mat4 proj = mat4(v11, 0.0, 0.0, 0.0,
                   0.0, v22, 0.0, 0.0,
                   v13, v23, v33, -1.0,
                   0.0, 0.0, v34, 0.0);

  return proj;
}

mat4 translate(float x, float y, float z) {
  mat4 translate = mat4(1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        x, y, z, 1.0);

  return translate;
}

mat4 scale(float by) {
  mat4 scale = mat4(by, 0.0, 0.0, 0.0,
                    0.0, by, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);

  return scale;
}

mat4 identity() {
  mat4 ident = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);

  return ident;
}

mat4 rotateX(float by) {
  float c = cos(by);
  float s = sin(by);

  mat4 rot = mat4(1.0, 0.0, 0.0, 0.0,
                  0.0, c, s, 0.0,
                  0.0, -s, c, 0.0,
                  0.0, 0.0, 0.0, 1.0);

  return rot;
}

mat4 rotateY(float by) {
  float c = cos(by);
  float s = sin(by);

  mat4 rot = mat4(c, 0.0, -s, 0.0,
                  0.0, 1.0, 0.0, 0.0,
                  s, 0.0, c, 0.0,
                  0.0, 0.0, 0.0, 1.0);

  return rot;
}

mat4 rotateZ(float by) {
  float c = cos(by);
  float s = sin(by);

  mat4 rot = mat4(c, s, 0.0, 0.0,
                  -s, c, 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0);

  return rot;
}

vec4 maybeFlipNormal(vec4 normal, vec4 pos) {
  vec4 toOrigin = vec4(0, 0, 0, 1) - pos;
  toOrigin.w = 0;
  toOrigin = normalize(toOrigin);
  float n = dot(toOrigin, normal);

  if (n < 0) {
    return -normal;
  } else {
    return normal;
  }
}

vec3 computeLighting(vec4 tPos, vec4 tNorm, mat4 view_transform) {
  vec3 color = vec3(0, 0, 0);

  for (int i = 0; i < num_lights; i++) {
    vec4 lightPos = vec4(lights[i], 1.0);
    lightPos = view_transform * lightPos;
    vec3 s = normalize(lightPos.xyz - tPos.xyz);
    color += (Ld * Kd * max(dot(s, tNorm.xyz), 0.0)).rgb;
    color.r = min(1.0, color.r);
    color.g = min(1.0, color.g);
    color.b = min(1.0, color.b);
  }

  return color;
}

void main() {
  vec4 pos = vec4(inPosition, 1);
  vec4 normal = vec4(inNormal, 0);
  mat4 mv = view_transform * model_transform;
  mat4 mv_norm = transpose(inverse(mv));
  vec4 tPos = mv * pos;
  vec4 tNorm = mv_norm * normal;
  tNorm.w = 0;
  tNorm = normalize(tNorm);
  tNorm = maybeFlipNormal(tNorm, tPos);
  vColor = computeLighting(tPos, tNorm, view_transform);
  mat4 mvp_perspective = perspective() * mv;
  vec4 outputPos = mvp_perspective * pos;
  gl_Position = outputPos;
}
)";