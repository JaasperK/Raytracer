#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")
#pragma comment(linker, "/NODEFAULTLIB:LIBCMT")

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

// glm includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Framework includes
#include <Debug.h>
#include <Mesh.h>

constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 1000;
constexpr float PI = 3.1415927f;

static void calculateSphereTexCoords(std::vector<Vertex> &verts)
{
  float u = 0;
  float v = 0;

  for (unsigned int i = 0; i < verts.size(); i++)
  {
    float x = verts[i].position.x;
    float y = verts[i].position.y;
    float z = verts[i].position.z;

    u = 0.5f + std::atan2(-x, -z) / (2.0f * PI);
    //v = 0.5f - std::asin(y) / PI;  // latitudes
    v = 0.5f - 0.5f * y;  // linear mapping

    verts[i].texUV.x = u;
    verts[i].texUV.y = v;

    std::cout << "u: " << u << ", v: " << v << std::endl;
  }
}

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

    // Setup Buffers
    const GLfloat x = 0.52573111212f;
    const GLfloat z = 0.85065080835f;    

    std::vector<Vertex> vertices = {
    //                      Positions      |            Normals          |            Colors         | Texture coordinates (calculated later)
       Vertex{ glm::vec3(  -x, 0.0f,    z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(   x, 0.0f,    z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(  -x, 0.0f,   -z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(   x, 0.0f,   -z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(0.0f,    z,    x), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(0.0f,    z,   -x), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(0.0f,   -z,    x), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(0.0f,   -z,   -x), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(   z,    x, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(  -z,    x, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(   z,   -x, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
       Vertex{ glm::vec3(  -z,   -x, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
    };

    std::vector<GLuint> indices = {
       0,  4,  1,
       0,  9,  4,
       9,  5,  4,
       4,  5,  8,
       4,  8,  1,
       8, 10,  1,
       8,  3, 10,
       5,  3,  8,
       5,  2,  3,
       2,  7,  3,
       7, 10,  3,
       7,  6, 10,
       7, 11,  6,
      11,  0,  6,
       0,  1,  6,
       6,  1, 10,
       9,  0, 11,
       9, 11,  2,
       9,  2,  5,
       7,  2, 11
    };

    Texture earth("res/textures/earth.png");
    std::vector<Texture> textures;
    textures.push_back(earth);

    calculateSphereTexCoords(vertices);

    Mesh spheroid(vertices, indices, textures);

    // Setup shaders
    std::string vertexShader = "res/shaders/vertexshader.vert";
    std::string fragmentShader = "res/shaders/fragmentshader.frag";
    Shader prog(vertexShader, fragmentShader);
    prog.Activate();
    prog.Uniform1f("u_AmbLight", 0.1f);

    textures[0].Bind(1);
    prog.Uniform1i("jasper", 1);

    Camera cam(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

    // Init rotation params
    float rotAmount = 0.0f;
    glm::vec3 rotAxis = glm::vec3(0.0f, 1.0f, 0.0f);    
    
    // To measure FPS 
    double time = glfwGetTime();
    int numFrames = 0;
    while (!glfwWindowShouldClose(window))
    {
      glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      cam.SetupMatrices(45.0f, 0.1f, 100.0f, prog);
      cam.Inputs(window);
      rotAmount += 0.02f;
      prog.UniformMat4f("u_ModelMatrix", glm::rotate(glm::mat4(1.0f), rotAmount, rotAxis));

      spheroid.Draw(prog, cam);

      time = Debug::CalculateFrameRate(time, numFrames);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}
