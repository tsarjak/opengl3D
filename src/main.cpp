// Developed by Sarjak Thakkar for Interactive Computer Graphics at NYU
// Thanks to Suraj Sharma for excellent OpenGL tutorials
#include "libs.h"
using namespace std;

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH){
  glViewport(0, 0, fbW, fbH);
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
