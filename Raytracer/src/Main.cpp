#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")  // To build in release mode comment these lines
#pragma comment(linker, "/NODEFAULTLIB:LIBCMT")  // To build in release mode comment these lines

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

//Framework includes
#include <Debug.h>
#include <Mesh.h>

constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 1000;

int main()
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // vsync; comment or set 0 to disable, set 1 to enable
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Error at glewInit!" << std::endl;
  }
  
  // Set OpenGL version to 4.6
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(Debug::DebugCallback, nullptr);


  { // Scope to call Vertex- and IndexBuffer destructor before glfwTerminate()
    glEnable(GL_DEPTH_TEST);

    // Setup meshes
    std::vector<Vertex> verts;
    {
      using namespace glm;
      //              Vertex{ position, normal, color, texCoord }
      verts.push_back(Vertex{ vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f) });
      verts.push_back(Vertex{ vec3(-1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f) });
      verts.push_back(Vertex{ vec3(1.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f) });
      verts.push_back(Vertex{ vec3(-1.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f) });
    }

    // Scale Canvas
    for (auto& v : verts)
    {
      v.position *= 20.0f;
    }

    std::vector<GLuint> indices = {
      0, 1, 2,
      3, 1, 2
    };

    std::vector<Texture> texs;

    Mesh canvas(verts, indices, texs);

    // Setup shaders
    std::string vertexShader = "res/shaders/vertexshader.vert";
    std::string fragmentShader = "res/shaders/fragmentshader.frag";
    Shader prog(vertexShader, fragmentShader);
    prog.Activate();
    
    prog.Uniform1i("u_RaysPerPixel", 32);
    prog.Uniform1i("u_MaxBounces", 5);
    //prog.Uniform3f("u_EnvLight", 0.0f, 0.0f, 1.0f);
    prog.Uniform3f("u_EnvLight", 0.5294117647f, 0.80784313725f, 0.92156862745f);  // sky color: #87CEEB

    // Setup spheres 
    prog.Uniform1i("u_NumSpheres", 5);

    GLfloat ylight = 4.0f;
    prog.Uniform3f("u_LightSphereCenter", -6.0f, ylight, 1.0f);
    prog.Uniform1f("u_LightSphereRadius", 2.0f);
    prog.Uniform3f("u_LightSphereColor", 0.0f, 0.0f, 0.0f);  // doesn't matter, emittedLight from frag shader will be displayed
    
    prog.Uniform3f("u_Sphere1Center", 4.8f, 6.0f, 3.0f);
    prog.Uniform1f("u_Sphere1Radius", 3.0f);
    prog.Uniform3f("u_Sphere1Color", 0.0f, 0.5f, 1.0f);  // blue
    
    prog.Uniform3f("u_Sphere2Center", 4.0f, -1.5f, 2.0f);
    prog.Uniform1f("u_Sphere2Radius", 1.5f);
    prog.Uniform3f("u_Sphere2Color", 0.75f, 0.0f, 0.0f);  // red

    prog.Uniform3f("u_Sphere3Center", 0.0f, 0.5f, -5.0f);
    prog.Uniform1f("u_Sphere3Radius", 6.0f);
    prog.Uniform3f("u_Sphere3Color", 0.75f, 0.52f, 0.75f);  // pink-ish

    prog.Uniform3f("u_Sphere4Center", 4.0f, -52.5f, 0.0f);
    prog.Uniform1f("u_Sphere4Radius", 50.0f);
    prog.Uniform3f("u_Sphere4Color", 0.25f, 0.75f, 0.05f);  // green
    

    Camera cam(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 50.0f));

    float inc = 0.025f;
    int frame = 0;

    // To measure FPS 
    double time = glfwGetTime();
    int numFrames = 0;

    while (!glfwWindowShouldClose(window))
    {
      glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      frame += 1;
      prog.Uniform1i("u_Frame", frame);

      // Move light
      if (ylight < 0.0f || ylight > 10.0f)
      {
        inc *= -1;
      }
      ylight += inc;
      prog.Uniform3f("u_LightSphereCenter", -6.0f, ylight, 1.0f);      

      cam.SetupMatrices(45.0f, 0.1f, 100.0f, prog);
      cam.Inputs(window);

      canvas.Draw(prog);

      time = Debug::CalculateFrameRate(time, numFrames);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}
