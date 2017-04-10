//
//  Planeta.h
//  Projecto
//
//  Created by Miguel Enrique Guerra Topete on 01/04/17.
//  Copyright © 2017 Miguel Enrique Guerra Topete. All rights reserved.
//

#ifndef Planeta_h
#define Planeta_h

#include <stdio.h>
#include <string>
#include "texture.h"

using namespace std;

class Planeta
{
public:
    double _aphelion;
    float radio = 100.0;
    string nombre;
    double velocidadOrbital;
    double aphelion;
    double perihelion;
    double periodoOrbital;
    double rotacion;
    double inclinacionZ;
    double inclinacionY;
    double tamano;
    double tiempoDelta;
    
    double ubicacionActualEje;
    double ubicacionActualSistema;
    
    double pX;
    double pY;
    double pZ;
    
    string texturePath;
    GLuint TexturePath;
    Texture *textura;
    Planeta *sateliteDe;
    
    //Planeta();
    
    Planeta(string nombre, double aphelion, double perihelion, double periodoOrbital, double periodoRotacion,
            const std::string texturePath, double tamano, double inclinacion, Planeta *sateliteDe = NULL);
    
    virtual ~Planeta();

    void Orbita(double grado, double escalaRotacionEje);
    
    void Dibujar();

private:
    Planeta(const Planeta& planeta) {}
    void operator=(const Planeta& planeta) {}
    
};


#endif /* Planeta_h */
