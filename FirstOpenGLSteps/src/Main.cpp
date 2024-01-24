#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")
#pragma comment(linker, "/NODEFAULTLIB:LIBCMT")

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

// glm includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <VertexArray.h>
#include <VertexBuffer.h>
#include <BufferLayout.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>
#include <Debug.h>


constexpr auto PI = 3.1415926535897932384626433832795028841971693993751058209749445923f;
static void calculateSphereTexCoords(GLfloat* verts, int size)
{
  float u = 0;
  float v = 0;

  for (int i = 0; i < size; i += 5)
  {
    float x = verts[i];
    float y = verts[i + 1];
    float z = verts[i + 2];

    u = 0.5f + std::atan2(-x, -z) / (2.0f * PI);
    //v = 0.5f - std::asin(y) / PI;  // latitudes
    v = 0.5f - 0.5f * y;  // linear mapping

    verts[i + 3] = u;
    verts[i + 4] = v;

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
  window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

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
  glDebugMessageCallback(Debug::debugCallback, nullptr);


  { // Scope to call Vertex- and IndexBuffer destructor before glfwTerminate()
    glEnable(GL_DEPTH_TEST);

    // Setup Buffers
    const GLfloat x = 0.52573111212f;
    const GLfloat z = 0.85065080835f;

    GLfloat positions[] = {
       -x,  0,  z,
        x,  0,  z,
       -x,  0, -z,
        x,  0, -z,
        0,  z,  x,
        0,  z, -x,
        0, -z,  x,
        0, -z, -x,
        z,  x,  0,
       -z,  x,  0,
        z, -x,  0,
       -z, -x,  0,
    };
    
    // TODO: figure out real texture coordinates
    int vertsSize = 12 * 5;
    GLfloat vertices[] = {
      // Positions | Texture coordinates
       -x,  0,  z,   1.0f, 1.0f,
        x,  0,  z,   0.0f, 0.0f,
       -x,  0, -z,   0.0f, 0.0f,
        x,  0, -z,   0.0f, 0.0f,
        0,  z,  x,   0.0f, 0.0f,
        0,  z, -x,   0.0f, 0.0f,
        0, -z,  x,   0.0f, 0.0f,
        0, -z, -x,   0.0f, 0.0f,
        z,  x,  0,   0.0f, 0.0f,
       -z,  x,  0,   0.0f, 0.0f,
        z, -x,  0,   0.0f, 0.0f,
       -z, -x,  0,   0.0f, 0.0f,
    };

    calculateSphereTexCoords(vertices, vertsSize);
    Debug::printVertices(vertices, vertsSize);

    GLuint indices[] = {
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
    
    VertexArray va;
    va.Bind();

    VertexBuffer vertsBuf(&vertices, sizeof(vertices));
    vertsBuf.Bind();

    BufferLayout layout;
    layout.Push<float>(3, GL_FALSE);
    layout.Push<float>(2, GL_FALSE);

    va.LinkAttrib(vertsBuf, layout);

    //va.LinkAttrib(vertsBuf, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (0 * sizeof(GLfloat))); // Links vao[0] to the buffer, that is currently bound
    //va.LinkAttrib(vertsBuf, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat))); // Links vao[1] to the buffer, that is currently bound

    IndexBuffer indBuf(&indices, sizeof(indices));
    indBuf.Bind();

    Texture earth("res/images/earth.png");
    GLuint texSlot = 0;
    earth.Bind(texSlot);

    // Setup shaders
    std::string vertexShader = "res/shaders/vertexshader.vert";
    std::string fragmentShader = "res/shaders/fragmentshader.frag";
    Shader prog(vertexShader, fragmentShader);
    prog.Activate();
    prog.Uniform1f("u_AmbLight", 10.0f);
    prog.Uniform1i("u_Earth", texSlot);
    prog.UniformMat4f("u_ProjectionMatrix", glm::mat4(1.0f));
    prog.UniformMat4f("u_ViewMatrix", glm::mat4(1.0f));

    // Init rotation params
    float rotAmount = 0.0f;
    glm::vec3 rotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      rotAmount += 0.02f;
      prog.UniformMat4f("u_ModelMatrix", glm::rotate(glm::mat4(1.0f), rotAmount, rotAxis));

      glDrawElements(GL_TRIANGLES, indBuf.GetCount() , GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}
