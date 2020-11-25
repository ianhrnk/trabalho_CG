#include "SceneObject.h"

SceneObject::SceneObject(const std::string &shape, const std::string &name)
{
  this->name = name;
  Init(shape);
}

SceneObject::~SceneObject()
{
  delete vao;
  delete vbo;
  delete ebo;
}

void SceneObject::Init(const std::string shape)
{
  std::vector<float> vertices, normals, buffer;
  std::vector<unsigned int> indices;
  std::map<unsigned int, unsigned int> v_n;

  if (shape == "axis")
  {
    buffer = {
      // Vertices e normais (zeradas)
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    indices = {
      0, 1, 2, 0, 0, 3
    };
  }
  else
  {
    if (shape == "cube")
      LoadObj("obj/cube.obj", vertices, normals, indices, v_n);
    else if (shape == "sphere")
      LoadObj("obj/sphere.obj", vertices, normals, indices, v_n);
    else if (shape == "cone")
      LoadObj("obj/cone.obj", vertices, normals, indices, v_n);
    else
      LoadObj("obj/torus.obj", vertices, normals, indices, v_n);

    MergeVerticesNormals(buffer, vertices, normals, v_n);
  }

  vao = new VertexArray();
  vbo = new VertexBuffer(buffer.size(), &buffer[0]);
  vao->AddBuffer(vbo);
  ebo = new ElementBuffer(indices.size(), &indices[0]);

  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();
}

void
SceneObject::MergeVerticesNormals(std::vector<float> &buffer,
                                  std::vector<float> vertices,
                                  std::vector<float> normals,
                                  std::map<unsigned int, unsigned int> v_n)
{
  buffer.reserve(2 * vertices.size());
  std::vector<float>::iterator it_vertices = vertices.begin();
  std::vector<float>::iterator it_normals;
  for (unsigned int i = 0; i < v_n.size(); ++i)
  {
    buffer.insert(buffer.end(), it_vertices, it_vertices + 3);
    it_vertices += 3;
    it_normals = normals.begin() + (v_n[i] * 3);
    buffer.insert(buffer.end(), it_normals, it_normals + 3);
  }
}

void
SceneObject::LoadObj(const std::string &filename, std::vector<float> &vertices,
                    std::vector<float> &normals, std::vector<unsigned int> &indices,
                    std::map<unsigned int, unsigned int> &v_n)
{
  std::ifstream in(filename);
  std::string line_header, temp, temp2;
  float v1, v2, v3;
  unsigned int p1, p2;

  if (in.is_open())
  {
    while (!in.eof())
    {
      in >> line_header;
      if (line_header == "v")
      {
        in >> v1 >> v2 >> v3;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
      }
      else if (line_header == "vn")
      {
        in >> v1 >> v2 >> v3;
        normals.push_back(v1);
        normals.push_back(v2);
        normals.push_back(v3);
      }
      else if (line_header == "f")
      {
        for (int i = 0; i < 3; ++i)
        {
          in >> temp;
          p1 = std::stoul(temp.substr(0, temp.find("//")), nullptr, 10);
          p2 = std::stoul(temp.substr(temp.find("//")+2, temp.length()), nullptr, 10);
          indices.push_back(p1-1);
          v_n.insert(std::pair<unsigned int, unsigned int>(p1-1, p2-1));
        }
      }
      else if (line_header == "#")
      {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      line_header.clear();
    }
  }
  in.close();
}

void SceneObject::Bind()
{
  vao->Bind();
  ebo->Bind();
}

void SceneObject::Unbind()
{
  vao->Unbind();
  ebo->Unbind();
}

void SceneObject::Translate(glm::vec3 value)
{
  model_matrix = glm::translate(model_matrix, value);
}

void SceneObject::Scale(glm::vec3 value)
{
  model_matrix = glm::scale(model_matrix, value);
}

void SceneObject::Shear(float v0, float v1, float v2, float v3,
                        float v4, float v5)
{
  model_matrix = glm::shearX3D(model_matrix, v0, v1);
  model_matrix = glm::shearY3D(model_matrix, v2, v3);
  model_matrix = glm::shearZ3D(model_matrix, v4, v5);
}

void SceneObject::Rotate(float angle, glm::vec3 value)
{
  model_matrix = glm::rotate(model_matrix, glm::radians(angle), value);
}

unsigned int SceneObject::GetNumIndices()
{ return ebo->NumElementos(); }

std::string SceneObject::GetName()
{ return name; }

glm::vec3 SceneObject::GetColor()
{ return color; }

glm::mat4 SceneObject::GetModelMatrix()
{ return model_matrix; }

void SceneObject::SetColor(glm::vec3 value)
{ color = value; }
