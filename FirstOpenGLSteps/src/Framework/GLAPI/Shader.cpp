#include <Shader.h>


// readShaderFile() > CreateShader() { CompileShader(vs) > CompileShader(fs) }


Shader::Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath)
{
  std::array<std::string, 2> shaderFiles = { vertexShaderPath, fragmentShaderPath };
  ShaderProgramSource source = readShaderFile(shaderFiles);
  m_progID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
  glDeleteProgram(m_progID);
}

void Shader::Activate() const
{
  glUseProgram(m_progID);
}

void Shader::Uniform1i(const std::string& name, int v0) const
{
  glUniform1i(glGetUniformLocation(m_progID, name.c_str()), v0);
}

void Shader::Uniform1f(const std::string& name, float v0) const
{
  glUniform1f(glGetUniformLocation(m_progID, name.c_str()), v0);
}

void Shader::Uniform3f(const std::string& name, float v0, float v1, float v2) const
{
  glUniform3f(glGetUniformLocation(m_progID, name.c_str()), v0, v1, v2);
}

void Shader::Uniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
  glUniform4f(glGetUniformLocation(m_progID, name.c_str()), v0, v1, v2, v3);
}

void Shader::UniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_progID, name.c_str()), 1, GL_FALSE, &(matrix[0].x));  // same as glm::value_ptr(matrix)
}

/////////////////////////
/// Private functions ///
/////////////////////////

// First element of filePaths is the vertex shader, second the fragment shader.
ShaderProgramSource Shader::readShaderFile(const std::array<std::string, 2> filePaths) const
{
  std::stringstream ss[2];
  for (size_t i = 0; i < filePaths.size(); i++)
  {
    std::ifstream stream(filePaths[i]);
    std::string line;

    while (getline(stream, line))
    {
      ss[i] << line << '\n';
    }
  }

  ShaderProgramSource shaders = { ss[0].str(), ss[1].str() };

  return shaders;
}

// Compiles the shader on the GPU and returns an id to that shader
GLuint Shader::CompileShader(unsigned int type, const std::string& source)
{
  GLuint id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  // Error handling
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = new char[length];
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    delete[] message;
    return 0;
  }

  return id;
}

// Returns a program with both shaders loaded
GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  GLuint program = glCreateProgram();
  GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

