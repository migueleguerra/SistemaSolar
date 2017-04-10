


#include <GLUT/glut.h>

#include "Universo.h"

Universo::Universo(const std::string texturePath, double size) :
  textura(new Texture(texturePath)),
  size(size)
{

}


Universo::~Universo(){
  delete textura;
}

void Universo::draw() {
  GLUquadric *qobj = gluNewQuadric();
  gluQuadricOrientation(qobj, GLU_INSIDE);
  gluQuadricTexture(qobj, GL_TRUE);
  glEnable(GL_TEXTURE_2D);

  glRotated(270.0f, 1.0f, 0.0f, 0.0f);
  textura->Bind();
  
  glPushMatrix();
  gluSphere(qobj, size, 30, 30);
  glPopMatrix();
  
  glDisable(GL_TEXTURE_2D);
  gluDeleteQuadric(qobj);
  glPopMatrix();
}