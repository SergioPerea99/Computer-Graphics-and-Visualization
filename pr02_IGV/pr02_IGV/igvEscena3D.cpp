#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores -----------------------------------

igvEscena3D::igvEscena3D() { ejes = true; }

igvEscena3D::~igvEscena3D() {}


// Metodos publicos ----------------------------------------

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

void igvEscena3D::visualizar(int escena) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	//Luces
	GLfloat light0[] = { 10,8,9,1 }; // point light source
	glLightfv(GL_LIGHT0, GL_POSITION, light0);
	glEnable(GL_LIGHT0);

	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();

	// Escena seleccionada a través del menú (click botón derecho)
	if (escena == EscenaA) renderEscenaA();
	else if (escena == EscenaB) renderEscenaB();
	else if (escena == EscenaC) renderEscenaC();

	glPopMatrix(); // restaura la matriz de modelado
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvEscena3D::renderEscenaA() {
	GLfloat color_pieza[] = { 0,0.25,0 };

	// Practica 2a. Parte A.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	glPushMatrix();
	glutSolidCube(1);
	glPopMatrix();
}

void igvEscena3D::renderEscenaB() {
	GLfloat color_pieza[] = { 0,0,0.5 };

	// Practica 2a. Parte B.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	glPushMatrix();
	glutSolidCube(1);
	glPopMatrix();
}


void igvEscena3D::renderEscenaC() {
	GLfloat color_pieza[] = { 0.5,0,0 };

	// Practica 2a. Parte C.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	glPushMatrix();
	glutSolidCube(1);
	glPopMatrix();
}




