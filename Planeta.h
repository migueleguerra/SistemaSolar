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
    double inclinacionZ;
    double inclinacionY;
    double tamano;
    double tiempoDelta;
    
    double ubicacionActualEje;
    double ubicacionActualSistema;
    
    double pX;
    double pY;
    double pZ;
    
    char* direccionTextura;
    GLuint TexturePath;
    GLuint textura;
    Planeta *sateliteDe;
    
    Planeta();
    
    Planeta(string nombre, double aphelion, double perihelion, double periodoOrbital,
            char* direccionTextura, double tamano, double inclinacion, Planeta *sateliteDe = NULL);
    
    void Orbita(double grado, double escalaRotacionEje);
    
    void Dibujar();
};


#endif /* Planeta_h */
