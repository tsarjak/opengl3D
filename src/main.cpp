// Developed by Sarjak Thakkar for Interactive Computer Graphics at NYU
// Thanks to Suraj Sharma for excellent OpenGL tutorials
#include "libs.h"
using namespace std;

Vertex vertices[]={
  glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
  glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),glm::vec3(0.f, 0.f, 1.f),
  glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),glm::vec3(0.f, 0.f, 1.f),

  glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.f),
  glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),glm::vec3(0.f, 0.f, 1.f),
  glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),glm::vec3(0.f, 0.f, 1.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =  {
  0, 1, 2,
  0, 2, 3
};

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

int numberOfMeshes = 0;
int curr_selected = -1;
int insert_now = 0;


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
      }
  }
}

// int selectMesh(GLFWwindow* window, int numberOfMeshes, int curr_selected){
//   if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
//     std::cout<<"\nPressed : ";
//     curr_selected += 1;
//
//       if (curr_selected >= numberOfMeshes){
//       curr_selected -= 1;
//     }
//   }
//
//   if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
//     curr_selected -= 1;
//     if (curr_selected == -2){
//       curr_selected += 1;
//       return curr_selected;
//     }
//   }
//
//   return curr_selected;
// }

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

}

int main(void){

  //Needed Variables


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
  //MODEL
  //Mesh mesh(vertices, nrOfVertices, indices, nrOfIndices, &core_program);
  //Mesh mesh(vertices, nrOfVertices, indices, nrOfIndices, &core_program);

  std::vector<Mesh> meshes;
  //Mesh mesh("../src/meshes/bunny.off", &core_program, 8.f);
  //Mesh mesh2("../src/meshes/bumpy_cube.off", &core_program, 0.2f,glm::vec3(-1.f,0.f,0.f));
  //Mesh mesh3("../src/meshes/unit_cube.off", &core_program, 1.f,glm::vec3(+1.f,0.f,0.f));

  //meshes.push_back(Mesh("../src/meshes/bunny.off", &core_program, 8.f));
  //meshes.push_back(mesh3);
  //meshes.push_back(mesh2);


  numberOfMeshes = meshes.size();

  //meshes.push_back(mesh);
  //meshes.push_back(mesh_2);
  //"../src/meshes/bumpy_cube.off"

  Material material0(glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(1.f));

  glm::vec3 worldUp(0.f, 1.f, 0.f);
  glm::vec3 camPosition(0.f, 0.f, 2.f);
  glm::vec3 camCenter(0.f, 0.f, 0.f);
  glm::vec3 sphereCoordinates = glm::vec3(2.f,0.f,0.f);
  Camera cam(2, &core_program, worldUp, camPosition, camCenter, sphereCoordinates);
  // glm::mat4  ViewMatrix(1.f);
  // ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

  float fov = 90.f;
  float nearPlane = 0.1f;
  float farPlane = 100.f;
  glm::mat4 ProjectionMatrix(1.f);

  //ProjectionMatrix = glm::ortho(0, 640, 480, 0, 0, 1000);

  ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

  glm::vec3 lightPos0(0.f, 0.f, 1.f);

  core_program.use();

  //core_program.setMat4fv(ModelMatrix, "ModelMatrix");
  //core_program.setMat4fv(ViewMatrix, "ViewMatrix");
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

    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);
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
