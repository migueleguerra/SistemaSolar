



#ifndef UNIVERSO_H
#define UNIVERSO_H

#include <string>
#include "texture.h"

class Universo
{
public:
  
  Universo(const std::string texturePath, double size);
  virtual ~Universo();   

  void draw();

private:
  Universo(const Universo& universe) {}
  void operator=(const Universo& other) {}

  
  Texture *textura;
  double size;
};

#endif