//
//  main.cpp
//  Projecto
//
//  Created by Miguel Enrique Guerra Topete on 01/04/17.
//  Copyright © 2017 Miguel Enrique Guerra Topete. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "List.h"
#include "Planeta.h"
#include "Universo.h"

Planeta *planetaHover;
List<Planeta*> *planetas;
Universo *universo;

GLuint estreallas;
double multiplicarTiempo = 0.05;
double contadorReloj = 0;
double zoom = 5;
double arrastrarX = -1;
double arrastrarY = -1;
double mouseX;
double mouseY;
double eliminarA = 0;
double eliminarB = 0;
GLfloat distanciaAEstrealas = 600;

using namespace std;

void intPlanetas();
void menu(unsigned char key);
void initSistema();
void rWin(int w, int h);
void dibujar();
void botones(unsigned char key, int A, int B);
void irAPlaneta(int index);
void movimientoMouse(int x, int y);
void orbita();
void mouse(int boton, int estado, int x, int y);
void agregarTextura();

void initPlanetas()
{
    planetas= new List<Planeta*>();
    
    /*Planeta(string nombre, double aphelion, double perihelion, double periodoOrbital,
    char* direccionTextura, double tamano, double inclinacion, Planeta *sateliteDe = NULL);
     
    - aphelion y perihelion es que tan cerca esta orbitando del sol
    - *sateliteDe seria la luna y especificando a quien pertenece.
    */
    int scale = 6;

    // rotation to 1 day o earth
    // mercurio 0.24
    // venus 0.0041
    // marte 1
    
    planetas->Add(new Planeta("Sol", 0, 0, 0, 20,"texturas/2k_sun.jpg", 109/30, 1.0));
    planetas->Add(new Planeta("Mercurio", 7.0*scale, 4.6*scale, 0.24, 58.82, "texturas/2k_mercury.jpg", .38, 1.0));
    planetas->Add(new Planeta("Venus", 10.893*scale, 10.747*scale, 0.61, 243, "texturas/2k_venus_atmosphere.jpg", .815, 1.0));
    planetas->Add(new Planeta("Tierra", 15.19*scale, 14.95*scale, 4.15, 1, "texturas/Tierra.jpg", 1, 25.0));
    planetas->Add(new Planeta("Marte", 20.67*scale, 24.92*scale, 1.8821, 1, "texturas/2k_mars.jpg", .53, 23.0));
    planetas->Add(new Planeta("Luna", 8, 8, 0.07, 2.5,"texturas/2k_moon.jpg", 0.18, 15.0, planetas->Get(3)));
    
    planetaHover = planetas->Get(0);
}

void menu(unsigned char key)
{
    for(int i = 0; i < planetas->Length() - 1; i++)
        cout << "Presiona " << i << " para ver " << planetas->Get(i)->nombre << endl;
    
    cout << "Presiona W para hacer zoom in" << endl;
    cout << "Presiona S para hacer zoom out" << endl;
    cout << "Presiona + para acelerar la velocidad" << endl;
    cout << "Presiona - para disminuir la velocidad" << endl;
    cout << "Presiona sin soltar el click izquierdo del mouse y jalalo para mover la camara" << endl;
    cout << "--------------------------------------" << endl;
    cout << "--------------------------------------" << endl;
    
    if(key >= '0' && key <= planetas->Length())
        cout << "Este es el " << planetas->Get(key - '0')->nombre;
    
}

void rWin(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, w/h, 1.0, 1500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    double x, y, z;
    const double mitadPI = 3.1416 / 180;
    
    x = sin((-mouseX + arrastrarX) * mitadPI) * cos((mouseY - arrastrarY) * mitadPI) * zoom;
    y = sin((mouseY - arrastrarY) * mitadPI) * zoom;
    z = cos((-mouseX + arrastrarX) * mitadPI) * cos((mouseY - arrastrarY) * mitadPI) * zoom;
    
    gluLookAt(planetaHover->pX + x, planetaHover->pY + y, planetaHover->pZ + z,
              planetaHover->pX, planetaHover->pY, planetaHover->pZ, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    universo->draw();
    for(int i = 0; i < planetas->Length(); i++)
        planetas->Get(i)->Dibujar();
    glPopMatrix();
    
    glutSwapBuffers();
}

void irAPlaneta(int index)
{
    Planeta * planeta;
    planeta = planetas->Get(index);
    planetaHover = planeta;
}

void botones(unsigned char key, int A, int B)
{
    int number = key - '0';
    switch(key)
    {
        case 'w': zoom--;
            break;
        case 's': zoom++;
            break;
        case 'a': eliminarA += 0.1;
            break;
        case 'd': eliminarB += 0.1;
            break;
        case '0': irAPlaneta(0);
            break;
        case '1': irAPlaneta(1);
            break;
        case '-': multiplicarTiempo /= multiplicarTiempo < 0.001 ? 1 : 2;
            break;
        case '+': multiplicarTiempo *= multiplicarTiempo > 10 ? 1 : 2;
            break;
        case 27:  exit(0);
            break;
        default:  break;
    }
    if (number >= 0 && number < 5){
        planetaHover = planetas->Get(number);
    }
}

void mouse(int boton, int estado, int x, int y)
{
    switch(boton)
    {
        case 0:
            if(estado == 0)
            {
                if(arrastrarX == -1)
                {
                    arrastrarX = x;
                    arrastrarY = y;
                }
                else
                {
                    arrastrarX += x - mouseX;
                    arrastrarY += y - mouseY;
                }
                mouseX = x;
                mouseY = y;
            }
            break;
        case 1:
            break;
        default:
            break;
    }
}

void movimientoMouse(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

void orbita()
{
    long nuevoContadorReloj = clock();
    
    for(int i = 0; i < planetas->Length(); i++)
        planetas->Get(i)->Orbita(multiplicarTiempo * ((nuevoContadorReloj - contadorReloj) / 20), 30);
    
    contadorReloj = nuevoContadorReloj;
    glutPostRedisplay();
}

void agregarTextura()
{
    
}

void initSistema()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Proyecto");
    
    initPlanetas();
    menu(0);
    universo = new Universo("texturas/2k_stars+milky_way.jpg", 60);
    // agregarTextura();
    glutReshapeFunc(rWin);
    glutDisplayFunc(dibujar);
    glutKeyboardFunc(botones);
    glutMotionFunc(movimientoMouse);
    glutMouseFunc(mouse);
    
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    // glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MULTISAMPLE);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutIdleFunc(orbita);
    glutMainLoop();
    
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    initSistema();
    return 0;
}
