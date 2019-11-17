// Developed by Sarjak Thakkar for Interactive Computer Graphics at NYU
// Thanks to Suraj Sharma for excellent OpenGL tutorials
#include "libs.h"
using namespace std;

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

  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
  glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  glViewport(0,0, framebufferWidth, framebufferHeight);

  glfwMakeContextCurrent(window);

  // Initialize GLEW
  #ifndef __APPLE__
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
      cout << "ERROR:GLEW_INIT_FAILED" << "\n";
      glfwTerminate();
    }
  #endif


  // Shader Init
  GLuint core_program;
  if(!loadShaders(core_program)){
      glfwTerminate();
  }

  // Main Loop
  while (!glfwWindowShouldClose(window)){

    // Update input
    glfwPollEvents();

    //Update

    // DRAW ---

    // Clear
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // Draw

    // End Draw
    glfwSwapBuffers(window);
    glFlush();

  }

  //End of Program
  glfwTerminate();
  return 0;
}
