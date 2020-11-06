#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"
#include "igvCilindro.h"


// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;
	rot_X = rot_Y = rot_Z = 0;
	// Apartado B: Inserta el código para crear un cilindro
	malla = new igvMallaTriangulos();
}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

void igvEscena3D::visualizar(void) {
	GLfloat color_malla[] = { 0,0.25,0 };
	// crear luces
	GLfloat luz0[4] = { 2.0,2.5,3.0,1 }; // luz puntual para visualizar el cubo

	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();


	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena
	glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
	

	// Apartado B: la siguiente llamada hay que sustituirla por la llamada al método visualizar de la malla

	glRotatef(get_rotX(), 1, 0, 0); //MANEJO DE ROTACION SOBRE EJE X.
	glRotatef(get_rotY(), 0, 1, 0); //MANEJO DE ROTACION SOBRE EJE Y.
	glRotatef(get_rotZ(), 0, 0, 1); //MANEJO DE ROTACION SOBRE EJE Z.
	
	igvCilindro cilindro(1,1,40,2);
	cilindro.visualizar(getVisualizacion());

	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::set_rotX(float _rotX) {
	rot_X = _rotX;
}

void igvEscena3D::set_rotY(float _rotY) {
	rot_Y = _rotY;
}

void igvEscena3D::set_rotZ(float _rotZ) {
	rot_Z = _rotZ;
}

float igvEscena3D::get_rotX() const {
	return rot_X;
}

float igvEscena3D::get_rotY() const {
	return rot_Y;
}

float igvEscena3D::get_rotZ() const {
	return rot_Z;
}

std::string igvEscena3D::getVisualizacion() const {
	return tipo_visualizacion;
}

void igvEscena3D::setVisualizacion(std::string _visual) {
	tipo_visualizacion = _visual;
}