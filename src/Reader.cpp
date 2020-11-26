#include "Reader.h"

Reader::Reader()
{
  objects.push_back(CreateAxis());
}

Object Reader::LoadObj(const std::string &shape)
{
  Object obj;

  if (AlreadyRead(shape, obj))
  {
    return obj;
  }
  else
  {
    std::ifstream in("obj/" + shape + ".obj");
    obj.shape = shape;

    std::vector<float> vertices, normals;
    std::map<unsigned int, unsigned int> v_n;

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
            obj.indices.push_back(p1-1);
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
    MergeVerticesNormals(obj.vertices, vertices, normals, v_n);
    objects.push_back(obj);
    in.close();
    return obj;
  }
}

void Reader::MergeVerticesNormals(std::vector<float> &buffer,
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

bool Reader::AlreadyRead(const std::string shape, Object &object)
{
  for (auto it = objects.cbegin(); it != objects.cend(); ++it)
    if ((*it).shape == shape)
    {
      object = *it;
      return true;
    }
  return false;
}

Object Reader::CreateAxis()
{
  Object axis;
  axis.shape = "axis";
  axis.vertices = {
    // Vertices e normais (zeradas)
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f
  };
  axis.indices = {
    0, 1, 2, 0, 0, 3
  };
  return axis;
}
