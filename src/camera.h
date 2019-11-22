#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

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

#define PI 3.14159265

using namespace std;
class Camera{
private:
  glm::vec3 worldUp;
  glm::vec3 camPosition;
  glm::vec3 camCenter;
  glm::vec3 sphereCoordinates;
  Shader* shader;

  void updateViewMatrix(){
    glm::mat4  ViewMatrix(1.f);

    ViewMatrix = glm::lookAt(this->camPosition, this->camCenter, this->worldUp);

    this->shader->setMat4fv(ViewMatrix, "ViewMatrix");
  }

public:
  Camera(int coordinate_system,
  Shader* shader,
  glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f),
  glm::vec3 camPosition = glm::vec3(0.f, 0.f, 1.f),
  glm::vec3 camCenter = glm::vec3(0.f, 0.f, 0.f),
  glm::vec3 sphereCoordinates = glm::vec3(2.f,0.f,0.f)){

  this->shader = shader;
  this->worldUp = worldUp;
  this->camPosition = camPosition;
  this->camCenter = camCenter;
  this->sphereCoordinates = sphereCoordinates;

  if (coordinate_system == 2){
      this->setSphere();
  }


  this->updateViewMatrix();

}

  ~Camera(){

  }

  void move(glm::vec3 camPositionDelta){
    this->camPosition += camPositionDelta;
    updateViewMatrix();
  }

  void setSphere(glm::vec3 sphericalChange = glm::vec3(2.f, 0.f, 0.f)){
    this->sphereCoordinates = sphericalChange;
    float x = sphericalChange[0] * sin (sphericalChange[1]*PI/180) * cos (sphericalChange[2]*PI/180);
    float y = sphericalChange[0] * sin (sphericalChange[1]*PI/180) * sin (sphericalChange[2]*PI/180);
    float z = sphericalChange[0] * cos (sphericalChange[1]*PI/180);

    this->camPosition = glm::vec3(x,y,z);
  }

  void changeSphere(glm::vec3 sphericalChange){
    this->sphereCoordinates += sphericalChange;
    float x = this->sphereCoordinates[0] * sin (this->sphereCoordinates[1]*PI/180) * cos (this->sphereCoordinates[2]*PI/180);
    float y = this->sphereCoordinates[0] * sin (this->sphereCoordinates[1]*PI/180) * sin (this->sphereCoordinates[2]*PI/180);
    float z = this->sphereCoordinates[0] * cos (this->sphereCoordinates[1]*PI/180);

    this->camPosition = glm::vec3(x,y,z);
    updateViewMatrix();
  }



};
