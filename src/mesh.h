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

#include "vertex.h"
#include "material.h"
#include "shader.h"
#include<vector>


class Mesh{
private:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::mat4 ModelMatrix;


  void initVertexData(Vertex* vertexArray, const unsigned&  nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices){
    for (size_t i = 0; i < nrOfVertices; i++){
      this->vertices.push_back(vertexArray[i]);
    }
    for (size_t i = 0; i < nrOfIndices; i++){
      this->indices.push_back(indexArray[i]);
    }
  }

  void initVAO(Shader* shader){

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //Gen VBO and bind
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    //Gen EBO and bind
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  this->indices.size() * sizeof(Vertex), indices.data(), GL_STATIC_DRAW);

    //Set Vertex Array Attribs
    shader->setAttribLocation("vertex_position", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    shader->setAttribLocation("vertex_color", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    shader->setAttribLocation("vertex_texcoord", 2, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    shader->setAttribLocation("vertex_normal", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    //Bind
    glBindVertexArray(0);

  }

  void initModelMatrix(){

    this->position = glm::vec3(0.f);
    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);

    this->ModelMatrix = glm::mat4(1.f);
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
  }

  void updateUniforms(Shader* shader){
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
  }

public:
  Mesh(Vertex* vertexArray,
        const unsigned& nrOfVertices,
        GLuint* indexArray,
        const unsigned& nrOfIndices,
        Shader* shader){

    this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
    this->initVAO(shader);
    this->initModelMatrix();

  }

  ~Mesh(){
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
  }

  void update(){

  }

  void render(Shader* shader){
    this->updateUniforms(shader);
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  }
};
