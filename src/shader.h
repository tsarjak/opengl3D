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

// Timer
#include <chrono>

class Shader{
private:
  GLuint id;

  std::string loadShaderSource(char* fileName){
    std::string temp = "";
    std::string src = "";

    std::ifstream in_file;

    // VertexShader
    in_file.open(fileName);

    if(in_file.is_open()){
      while(getline(in_file, temp))
        src += temp + "\n";
    } else {
      std::cout << "ERROR::SHADER::Couldn't open SHADER file" << fileName << "\n";
    }

    in_file.close();

    return src;
  }

  GLuint loadShader(GLenum type, char* fileName){

    char infolog[512];
    GLint success;

    GLuint shader = glCreateShader(type);
    std::string str_src = this->loadShaderSource(fileName);
    const GLchar* src = str_src.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
      glGetShaderInfoLog(shader, 512, NULL, infolog);
      std::cout<<"ERROR::SHADER::could not compile shader: " << fileName <<"\n";
      std::cout<<infolog<<"\n";
    }

    return shader;
  }

  void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader){
    char infolog[512];
    GLint success;

    this->id = glCreateProgram();

    glAttachShader(this->id, vertexShader);

    if(geometryShader)
      glAttachShader(this->id, geometryShader);

    glAttachShader(this->id, fragmentShader);

    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success){
      glGetProgramInfoLog(this->id, 512, NULL, infolog);
      std::cout<<"ERROR::SHADER::could not link program" << "\n";
      std::cout<<infolog;
    }


    // End
    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

  }

public:

  Shader(char* vertexFile = "", char* fragmentFile = "", char* geometryFile = ""){
    GLuint vertexShader = 0;
    GLuint geometryShader = 0;
    GLuint fragmentShader = 0;

    vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

    if(geometryFile != ""){
      geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
    }

    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

    this->linkProgram(vertexShader, geometryShader, fragmentShader);

  }

  ~Shader(){
    glDeleteProgram(this->id);
  }

  void use(){
    glUseProgram(this->id);
  }

  void unuse(){
    glUseProgram(0);
  }

  void setVec3f(glm::fvec3 value, const GLchar* name){
    this->use();
    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
    this->unuse();
  }

  void setVec2f(glm::fvec2 value, const GLchar* name){
    this->use();
    glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
    this->unuse();
  }

  void setVec1f(GLfloat value, const GLchar* name){
    this->use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
    this->unuse();
  }

  void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE){
    this->use();
    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
    this->unuse();
  }

  void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE){
    this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
    this->unuse();
  }

  void setVec4f(glm::fvec4 value, const GLchar* name){
    this->use();
    glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
    this->unuse();
  }

  void setAttribLocation(GLchar* name, GLuint length, std::size_t size, GLvoid* offset){
    this->use();
    GLuint attribLoc = glGetAttribLocation(this->id, name);
    glVertexAttribPointer(attribLoc, length, GL_FLOAT, GL_FALSE, size, offset);
    glEnableVertexAttribArray(attribLoc);
    this->unuse();
  }

  //Set uniform functions
};
