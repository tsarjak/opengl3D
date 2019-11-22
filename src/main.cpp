// Developed by Sarjak Thakkar for Interactive Computer Graphics at NYU
// Thanks to Suraj Sharma for excellent OpenGL tutorials
#include "libs.h"
using namespace std;

int numberOfMeshes = 0;
int curr_selected = -1;
int insert_now = 0;
int projectionType = 0;
std::vector<Mesh> meshes;

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH){
  glViewport(0, 0, fbW, fbH);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS){
    // Update the position of the first vertex if the keys 1,2, or 3 are pressed
      switch (key)
      {
          case GLFW_KEY_M:
            std::cout<<"\nPressed : ";
            curr_selected += 1;

            if (curr_selected >= numberOfMeshes){
                curr_selected -= 1;
                }
          break;
          case GLFW_KEY_N:
            curr_selected -= 1;
              if (curr_selected == -2){
                curr_selected += 1;
              }
          break;
          case GLFW_KEY_1:
            insert_now = 1;
            break;
          case GLFW_KEY_2:
            insert_now = 2;
            break;
          case GLFW_KEY_3:
            insert_now = 3;
            break;

          case GLFW_KEY_SPACE:
            if(projectionType == 0){
              projectionType = 1;
            } else {
              projectionType = 0;
            }
      }
  }
}

void moveCamera(GLFWwindow* window, Camera &cam){
  if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){ //Move up
    cam.move(glm::vec3(0.f, 0.01f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){ //Move Down
    cam.move(glm::vec3(0.f, -0.01f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){ //Move left
    cam.move(glm::vec3(-0.01f, 0.f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){ //Move Right
    cam.move(glm::vec3(0.01f, 0.f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){ // Move out
    cam.move(glm::vec3(0.f, 0.f, 0.01f));
  }
  if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
    cam.move(glm::vec3(0.f, 0.f, -0.01f));
  }

  if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
    cam.changeSphere(glm::vec3(0.f, 0.08f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){
    cam.changeSphere(glm::vec3(0.f, -0.08f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
    cam.changeSphere(glm::vec3(0.f, 0.f, 0.08f));
  }
  if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
    cam.changeSphere(glm::vec3(0.f, 0.f, -0.08f));
  }
}

void moveMesh(GLFWwindow* window, Mesh &mesh){
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    mesh.move(glm::vec3(0.f, 0.f, -0.0001f));
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    mesh.move(glm::vec3(0.f, 0.f, 0.0001f));
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    mesh.move(glm::vec3(-0.001f, 0.f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    mesh.move(glm::vec3(0.001f, 0.f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    mesh.rotate(glm::vec3(0.f, -0.1f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
    mesh.rotate(glm::vec3(0.f, 0.1f, 0.f));
  }
  if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
    mesh.scaleUp(glm::vec3(0.001f));
  }
  if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
    mesh.scaleUp(glm::vec3(-0.001f));
  }

  if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
    mesh.changeRenderMode(0);
  }
  if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
    mesh.changeRenderMode(1);
  }
  if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
    mesh.changeRenderMode(2);
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

  Shader core_program("../src/shaders/vertex_core.glsl", "../src/shaders/fragment_core.glsl");

  numberOfMeshes = meshes.size();

  Material material0(glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(1.f));

  glm::vec3 worldUp(0.f, 1.f, 0.f);
  glm::vec3 camPosition(0.f, 0.f, 2.f);
  glm::vec3 camCenter(0.f, 0.f, 0.f);
  glm::vec3 sphereCoordinates = glm::vec3(2.f,0.f,0.f);
  Camera cam(2, &core_program, worldUp, camPosition, camCenter, sphereCoordinates);

  float fov = 90.f;
  float nearPlane = 0.1f;
  float farPlane = 100.f;

  glm::mat4 ProjectionMatrix(1.f);

  if (projectionType == 0){
    ProjectionMatrix = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
  } else {
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);
  }

  glm::vec3 lightPos0(0.f, 0.f, 1.f);

  core_program.use();

  core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

  core_program.setVec3f(lightPos0, "lightPos0");
  core_program.setVec3f(camPosition, "cameraPos");

  glfwSetKeyCallback(window, key_callback);

  glUseProgram(0);

  // Main Loop
  while (!glfwWindowShouldClose(window)){


    // Update input
    glfwPollEvents();


    //Check insert condition
    if (insert_now != 0){
      if (insert_now == 1){
      meshes.push_back(Mesh("../src/meshes/bunny.off", &core_program, 8.f));
    } else if (insert_now == 2){
      meshes.push_back(Mesh("../src/meshes/bumpy_cube.off", &core_program, 0.2f));
    } else if (insert_now == 3){
      meshes.push_back(Mesh("../src/meshes/unit_cube.off", &core_program, 1.f));
    }
      numberOfMeshes = meshes.size();
      insert_now = 0;
    }

    //Check Selection
    for(int i = 0; i < numberOfMeshes; i++){
        meshes[i].unsetSelected();
    }

    if (curr_selected != -1){
      meshes[curr_selected].setSelected();
      moveMesh(window, meshes[curr_selected]);
    }

    //Check renderMode


    //move Camera if any button clicked
    moveCamera(window, cam);

    //Update

    // DRAW ---

    // Clear
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    material0.sendToShader(core_program);

    //core_program.setMat4fv(ModelMatrix, "ModelMatrix");
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    ProjectionMatrix = glm::mat4(1.f);

    if (projectionType == 0){
      ProjectionMatrix = glm::ortho(-2.0f,2.0f,-2.0f,2.0f,0.0f,100.0f);
    } else {
      ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);
    }

    //ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);
    //ProjectionMatrix = glm::ortho(-2.0f,2.0f,-2.0f,2.0f,0.0f,100.0f);
    core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    // Draw
    core_program.use();


    for (int j=0;j<numberOfMeshes;j++){
      meshes[j].render(&core_program);
    }

    // End Draw
    glfwSwapBuffers(window);
    glFlush();

  }

  //End of Program
  glfwTerminate();
  return 0;


}
