#pragma once

#include <string>
#include <iostream>
#include <fstream>


#include <vector>
#include <Eigen/Core>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include "vertex.h"
#ifdef _WIN32
#  include <windows.h>
#  undef max
#  undef min
#  undef DrawText
#endif

#ifndef __APPLE__
#  define GLEW_STATIC
#  include <GL/glew.h>
#endif

#ifdef __APPLE__
#   include <OpenGL/gl3.h>
#   define __gl_h_ /* Prevent inclusion of the old gl.h */
#else
#   ifdef _WIN32
#       include <windows.h>
#   endif
#   include <GL/gl.h>
#endif

#include "shader.h"

class Material{

private:
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

public:
  Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
  }

  ~Material(){}

  //Functions
  void sendToShader(Shader& program){
    program.setVec3f(this->ambient, "material.ambient");
    program.setVec3f(this->diffuse, "material.diffuse");
    program.setVec3f(this->specular, "material.specular");
  }
};
