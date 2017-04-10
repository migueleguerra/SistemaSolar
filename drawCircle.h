
#include <math.h>

void drawCircle(float x2){
    // usamos esta en lugar de bresenham pues necesitamos precisión flotante
    int detail=100;

    glPushMatrix();
    glScaled(x2, x2, x2);
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<detail;++i){
      glVertex2d(cos(2 * i * M_PI/detail),sin(2*i*M_PI/detail));
    }
    glEnd();
    glPopMatrix();
}