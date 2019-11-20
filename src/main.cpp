// Developed by Sarjak Thakkar for Interactive Computer Graphics at NYU
// Thanks to Suraj Sharma for excellent OpenGL tutorials
#include "libs.h"
using namespace std;

Vertex vertices[]={
  glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, -1.f),
  glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),glm::vec3(0.f, 0.f, -1.f),
  glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),glm::vec3(0.f, 0.f, -1.f),
  glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),glm::vec3(0.f, 0.f, -1.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =  {
  0, 1, 2,
  0, 2, 3
};

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH){
  glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint &program){

  bool loadSuccess = true;
  char infolog[512];
  GLint success;

  string temp = "";
  string src = "";

  ifstream in_file;

  // VertexShader
  in_file.open("../src/shaders/vertex_core.glsl");

  if(in_file.is_open()){
    while(getline(in_file, temp))
      src += temp + "\n";
  } else {
    cout << "ERROR::loadShaders::Couldn't open vertex file" << "\n";
  }

  in_file.close();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vertSrc = src.c_str();
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
    cout<<"ERROR::loadshaders::could not compile vertex shaders" << "\n";
    cout<<infolog<<"\n";
  }

  temp = "";
  src = "";

  // Fragment Shader
  in_file.open("../src/shaders/fragment_core.glsl");

  if(in_file.is_open()){
    while(getline(in_file, temp))
      src += temp + "\n";
  } else {
    cout << "ERROR::loadShaders::Couldn't open fragment file" << "\n";
  }

  in_file.close();

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragSrc = src.c_str();
  glShaderSource(fragmentShader, 1, &fragSrc, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
    cout<<"ERROR::loadshaders::could not compile fragment shaders" << "\n";
    cout<<infolog<<"\n";
  }

  // Program
  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(program, 512, NULL, infolog);
    cout<<"ERROR::LOADSHADERS::could not link program" << "\n";
    cout<<infolog;
    loadSuccess = false;
  }


  // End
  glUseProgram(0);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return loadSuccess;
}

void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale){
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    position.z -= 0.01f;
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    position.z += 0.01f;
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    position.x -= 0.01f;
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    position.x += 0.01f;
  }
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    rotation.y -= 0.1f;
  }
  if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
    rotation.y += 0.1f;
  }
  if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
    scale += 0.0001f;
  }
  if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
    scale -= 0.001f;
  }
}

int main(void){

  // Initialize GLFW
  if(!glfwInit()){
    return -1;
  }

  // Create Window
  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;
  int framebufferWidth =  0;
  int framebufferHeight = 0;

  // Activate supersampling
  glfwWindowHint(GLFW_SAMPLES, 8);

  // Ensure that we get at least a 3.2 context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow* window  = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL3D", NULL, NULL);

  glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
  //glViewport(0,0, framebufferWidth, framebufferHeight);

  glfwMakeContextCurrent(window);

  // Enable some options for 3D
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


  // Initialize GLEW
  #ifndef __APPLE__
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
      cout << "ERROR:GLEW_INIT_FAILED" << "\n";
      glfwTerminate();
    }
  #endif

  Shader test("../src/shaders/vertex_core.glsl", "../src/shaders/fragment_core.glsl");

  // Shader Init
  GLuint core_program;
  if(!loadShaders(core_program)){
      glfwTerminate();
  }

  //MODEL

  //VAO, VBO, EBO

  //Gen VAO and bind
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //Gen VBO and bind
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //Gen EBO and bind
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);


  //Set Vertex Array Attribs
  //Position
  GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
  glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(attribLoc);

  //Color
  GLuint attribLoc_2 = glGetAttribLocation(core_program, "vertex_color");
  glVertexAttribPointer(attribLoc_2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
  glEnableVertexAttribArray(attribLoc_2);

  //Texture Coordinate
  GLuint attribLoc_3 = glGetAttribLocation(core_program, "vertex_texcoord");
  glVertexAttribPointer(attribLoc_3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
  glEnableVertexAttribArray(attribLoc_3);

  GLuint attribLoc_4 = glGetAttribLocation(core_program, "vertex_normal");
  glVertexAttribPointer(attribLoc_4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(attribLoc_4);

  //Bind
  glBindVertexArray(0);

  glm::vec3 position(0.f);
  glm::vec3 rotation(0.f);
  glm::vec3 scale(1.f);

  glm::mat4 ModelMatrix(1.f);
  ModelMatrix = glm::translate(ModelMatrix, position);
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
  ModelMatrix = glm::scale(ModelMatrix, scale);

  glm::vec3 worldUp(0.f, 1.f, 0.f);
  glm::vec3 camPosition(0.f, 0.f, 1.f);
  glm::vec3 camFront(0.f, 0.f, -1.f);
  glm::mat4  ViewMatrix(1.f);
  ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

  float fov = 90.f;
  float nearPlane = 0.1f;
  float farPlane = 100.f;
  glm::mat4 ProjectionMatrix(1.f);

  ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

  glm::vec3 lightPos0(0.f, 0.f, 1.f);


  glUseProgram(core_program);

  glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

  glUniform3fv(glGetUniformLocation(core_program, "lightPos0"), 1, glm::value_ptr(lightPos0));
  glUniform3fv(glGetUniformLocation(core_program, "cameraPos"), 1, glm::value_ptr(camPosition));

  glUseProgram(0);


  // Main Loop
  while (!glfwWindowShouldClose(window)){

    // Update input
    glfwPollEvents();
    updateInput(window, position, rotation, scale);

    //Update

    // DRAW ---

    // Clear
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    //Use Program
    glUseProgram(core_program);

    //Move. rotate and scale

    ModelMatrix = glm::mat4(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    //glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    ProjectionMatrix = glm::mat4(1.f);
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    //Bind vertex array object
    glBindVertexArray(VAO);


    // Draw
    glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


    // End Draw
    glfwSwapBuffers(window);
    glFlush();

  }

  //End of Program
  glfwTerminate();
  return 0;
}
