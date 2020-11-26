#ifndef READER_H
#define READER_H

#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <string>

struct Object {
  std::string shape;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
};

class Reader {
 private:
  std::vector<Object> objects;

  Object CreateAxis();
  bool AlreadyRead(const std::string shape, Object &object);
  void MergeVerticesNormals(std::vector<float> &buffer,
                            std::vector<float> vertices,
                            std::vector<float> normals,
                            std::map<unsigned int, unsigned int> v_n);

 public:
  Reader();
  ~Reader() = default;

  Object LoadObj(const std::string &shape);
};

#endif
