#include "Model.h"

unsigned int Model::wire = GL_TRIANGLES;

Model::Model(const std::string &shape, const std::string &name)
{
  this->name = name;
  Init(shape);
}

Model::~Model()
{
  delete vao;
  delete vbo;
  delete ebo;
}

void Model::Init(const std::string shape)
{
  std::vector<float> vertices, normais, buffer;
  std::vector<unsigned int> indices;
  std::map<unsigned int, unsigned int> vertices_normal;

  if (shape.compare("cube") == 0)
    LoadObj("obj/cube.obj", vertices, normais, indices, vertices_normal);
  else if (shape.compare("sphere") == 0)
    LoadObj("obj/sphere.obj", vertices, normais, indices, vertices_normal);
  else if (shape.compare("cone") == 0)
    LoadObj("obj/cone.obj", vertices, normais, indices, vertices_normal);
  else
    LoadObj("obj/torus.obj", vertices, normais, indices, vertices_normal);

  // Unir os vertices e suas normais em um buffer
  buffer.reserve(2 * vertices.size());
  std::vector<float>::iterator it_vertices = vertices.begin();
  std::vector<float>::iterator it_normais;
  for (int i = 0; i < vertices_normal.size(); ++i)
  {
    buffer.insert(buffer.end(), it_vertices, it_vertices + 3);
    it_vertices += 3;
    it_normais = normais.begin() + (vertices_normal[i] * 3);
    buffer.insert(buffer.end(), it_normais, it_normais + 3);
  }

  vao = new VertexArray();
  vbo = new VertexBuffer(buffer.size(), &buffer[0]);
  vao->AddBuffer(vbo);
  ebo = new ElementBuffer(indices.size(), &indices[0]);

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();
}

void Model::LoadObj(const std::string &filename, std::vector<float> &vertices,
                    std::vector<float> &normais, std::vector<unsigned int> &indices,
                    std::map<unsigned int, unsigned int> &vertices_normal)
{
  std::ifstream entrada(filename);
  std::string line_header, temp, temp2;
  float v1, v2, v3;
  unsigned int p1, p2;

  if (entrada.is_open())
  {
    while (!entrada.eof())
    {
      entrada >> line_header;
      if (line_header.compare("v") == 0)
      {
        entrada >> v1 >> v2 >> v3;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
      }
      else if (line_header.compare("vn") == 0)
      {
        entrada >> v1 >> v2 >> v3;
        normais.push_back(v1);
        normais.push_back(v2);
        normais.push_back(v3);
      }
      else if (line_header.compare("f") == 0)
      {
        for (int i = 0; i < 3; ++i)
        {
          entrada >> temp;
          p1 = std::stoul(temp.substr(0, temp.find("//")), nullptr, 10);
          p2 = std::stoul(temp.substr(temp.find("//")+2, temp.length()), nullptr, 10);
          indices.push_back(p1-1);
          vertices_normal.insert(std::pair<unsigned int, unsigned int>(p1-1, p2-1));
        }
      }
      else if (line_header.compare("#") == 0)
      {
        entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      line_header.clear();
    }
  }
  entrada.close();
}

void Model::Bind()
{
  vao->Bind();
  ebo->Bind();
}

void Model::Unbind()
{
  vao->Unbind();
  ebo->Unbind();
}

const unsigned int Model::GetNumIndices()
{
  return ebo->GetNumElementos();
}

const std::string Model::GetName()
{
  return name;
}

const glm::vec3 Model::GetColor()
{
  return color;
}

unsigned int Model::GetWire()
{
  return Model::wire;
}

void Model::SetColor(float v0, float v1, float v2)
{
  color.x = v0;
  color.y = v1;
  color.z = v2;
}

void Model::SetWire(unsigned int mode)
{
  Model::wire = mode;
}
