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

using namespace std;


class Mesh{
private:

  unsigned nrOfIndices;
  unsigned nrOfVertices;

  float selected;

  unsigned originalVertices;
  float scaleFactor;


  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::mat4 ModelMatrix;

  void compute_normals(std::vector<Vertex> vertex_vector,
    const unsigned&  nrOfVertices,
    GLuint* indexArray,
    const unsigned& nrOfIndices,
    Shader* shader){

      GLuint v1;
      GLuint v2;
      GLuint v3;

      std::vector<glm::vec3> perFaceNormals;

      Vertex temp_vertex;
      temp_vertex.color = glm::vec3(1.f, 0.f, 0.f);
      temp_vertex.texcoord = glm::vec2(0.f, 1.f);

      //std::vector<Vertex> vertex_vector;

    //Calculating Perface Normals
    int curr_index = 0;
      for (int i=0; i<nrOfIndices; i+=3){

        v1 = indexArray[i];
        v2 = indexArray[i+1];
        v3 = indexArray[i+2];

        glm::vec3 e1 = vertex_vector[v2].position - vertex_vector[v1].position;
        glm::vec3 e2 = vertex_vector[v3].position - vertex_vector[v1].position;

        glm::vec3 tri_normal = glm::cross(e1, e2);
        perFaceNormals.push_back(tri_normal);

        temp_vertex.position = vertex_vector[v1].position;
        temp_vertex.normal = normalize(tri_normal);
        vertex_vector.push_back(temp_vertex);

        temp_vertex.position = vertex_vector[v2].position;
        temp_vertex.normal = normalize(tri_normal);
        vertex_vector.push_back(temp_vertex);

        temp_vertex.position = vertex_vector[v3].position;
        temp_vertex.normal = normalize(tri_normal);
        vertex_vector.push_back(temp_vertex);

      }

      this->originalVertices = nrOfVertices;

      //Calculating per vertex Normals


      Vertex vertices_[nrOfVertices + nrOfIndices];
      std::copy(vertex_vector.begin(), vertex_vector.end(), vertices_);

      this->initVAO(vertices_, nrOfVertices + nrOfIndices, indexArray, nrOfIndices, shader);

    }


  void read_from_file(string fileName, Shader* shader){
    string temp = "";
    int count = 0;
    unsigned numPoints;
    unsigned numIndices;
    int fileindex=0;
    int first_check=0;
    int indice_actual_count = 0;
    Vertex temp_vertex;

    std::vector<Vertex> vertex_vector;
    std::vector<GLuint> indices_vector;

    glm::vec3 toCenter = glm::vec3(0.f);

    std::ifstream in_file;

    in_file.open(fileName);

    if(in_file.is_open()){
      while(getline(in_file, temp)){

        //Checking for OFF file
        if (count == 0 && temp == "OFF"){
          std::cout<<"OFF format detected.\n";
          count++;
        }

        //Getting details about the number of points
        else if(count==1){
          std::string word;
          int internal_count = 0;
          for ( std::istringstream is( temp ); is >> word; ){
              if (internal_count == 0){
                numPoints = stoi(word);
                cout<<"Num Points: "<<numPoints<<"\n";
                internal_count++;
                } else if (internal_count == 1){
                numIndices = stoi(word) * 3;
                cout<<"Num Indices: "<<numIndices<<"\n";
                internal_count++;
            }
          }
          count++;
        }


        else if(count > 1){
          Vertex temp_vertex;


          if (fileindex < numPoints){
            std::string word;
            std::vector<float> temp_pts;

              for ( std::istringstream is( temp ); is >> word; ){
                temp_pts.push_back(stof(word));
              }

  //cout<<fileindex<<"\n";
              temp_vertex.position = glm::vec3(temp_pts[0], temp_pts[1], temp_pts[2]);
              temp_vertex.color = glm::vec3(0.f, 0.f, 0.f);
              temp_vertex.texcoord = glm::vec2(0.f, 1.f);
              temp_vertex.normal = glm::vec3(0.f, 0.f, 1.f);

              toCenter += temp_vertex.position;

              vertex_vector.push_back(temp_vertex);
              fileindex++;
        }

        else if (fileindex >= numPoints){

          int first_check = 0;
          std::string word;
          for ( std::istringstream is( temp ); is >> word; ){

            if (first_check == 0){
              first_check++;
            } else {
            indices_vector.push_back(GLuint(stoi(word)));
            indice_actual_count++;
          }
        }
        }

      }
    }

  }

  in_file.close();

  glm::vec3 average = toCenter / float(numPoints);

  for (int i=0; i<vertex_vector.size(); i++){
    vertex_vector[i].position = (vertex_vector[i].position - average) * this->scaleFactor;
  }

  //Vertex vertices_[numPoints];
  GLuint indices_[numIndices];

  //std::copy(vertex_vector.begin(), vertex_vector.end(), vertices_);
  std::copy(indices_vector.begin(), indices_vector.end(), indices_);

  std::cout<<sizeof(indices_)/sizeof(indices_[0])<<"\n";
  //std::cout<<sizeof(vertices_)/sizeof(vertices_[0])<<"\n";

  std::cout<<"Now created the required arrays"<<"\n"<<indice_actual_count<<"\n";

  this->compute_normals(vertex_vector, numPoints, indices_, numIndices, shader);

}

  void initVAO(Vertex* vertexArray,
    const unsigned&  nrOfVertices,
    GLuint* indexArray,
    const unsigned& nrOfIndices,
    Shader* shader){
      //Set variables
      this->nrOfVertices = nrOfVertices;
      this->nrOfIndices = nrOfIndices;

      cout<<"Number of Vertices : "<< this->nrOfVertices;
      cout<<"Number of Indices : "<< this->nrOfIndices;

    std::cout<<"In INITVAO"<<"\n";

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    std::cout<<"Bound VAO"<<"\n";

    //Gen VBO and bind
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

    std::cout<<"Bound VBO"<<"\n";

    //Gen EBO and bind
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

    std::cout<<"Bound EBO"<<"\n";

    //Set Vertex Array Attribs
    shader->setAttribLocation("vertex_position", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    shader->setAttribLocation("vertex_color", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    shader->setAttribLocation("vertex_texcoord", 2, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    shader->setAttribLocation("vertex_normal", 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    //Bind
    glBindVertexArray(0);

  }

  void  updateModelMatrix(){
    this->ModelMatrix = glm::mat4(1.f);
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
  }

  void updateUniforms(Shader* shader){
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
    shader->setVec1f(this->selected, "selected");
  }

public:
  Mesh(Vertex* vertexArray,
        const unsigned& nrOfVertices,
        GLuint* indexArray,
        const unsigned& nrOfIndices,
        Shader* shader,
        glm::vec3 position = glm::vec3(0.f),
        glm::vec3 rotation = glm::vec3(0.f),
        glm::vec3 scale = glm::vec3(1.f)) {

    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->selected = 0.f;

    this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices, shader);
    this->updateModelMatrix();
}
  // }
  // glm::vec3 position = glm::vec3(0.f, -0.2, -6.f),
  // glm::vec3 rotation = glm::vec3(0.f),
  // glm::vec3 scale = glm::vec3(0.7f)

  Mesh(string fileName,
      Shader* shader,
      float scaleFactor,
      glm::vec3 position = glm::vec3(0.f),
      glm::vec3 rotation = glm::vec3(0.f),
      glm::vec3 scale = glm::vec3(1.f)
    ){
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
      this->selected = 0.f;
      this->scaleFactor = scaleFactor;
      this->read_from_file(fileName, shader);
      this->updateModelMatrix();
    }

  ~Mesh(){
    //glDeleteVertexArrays(1, &this->VAO);
    //glDeleteBuffers(1, &this->VBO);
    //glDeleteBuffers(1, &this->EBO);
  }


  void setPosition(const glm::vec3 position){
    this->position = position;
  }

  void setRotation(const glm::vec3 rotation){
    this->rotation = rotation;
  }

  void setScale(const glm::vec3 scale){
    this->scale = scale;
  }

  void scaleUp(const glm::vec3 scale){
    this->scale += scale;
  }

  //Functions
  void move(const glm::vec3 position){
    this->position += position;
  }
  void rotate(const glm::vec3 rotation){
    this->rotation += rotation;
  }


  void update(){

  }

  void render(Shader* shader){
    this->ModelMatrix = glm::mat4(1.f);
    this->updateModelMatrix();
    this->updateUniforms(shader);
    shader->use();
    glBindVertexArray(this->VAO);

    //
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, this->originalVertices, this->nrOfIndices);//this->nrOfIndices, GL_UNSIGNED_INT, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

  }

  void setSelected(){
    this->selected = 1.f;
  }

  void unsetSelected(){
    this->selected = 0.f;
  }

};
