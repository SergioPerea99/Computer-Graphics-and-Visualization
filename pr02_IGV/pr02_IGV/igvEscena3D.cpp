#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvInterfaz.h"

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

	// Escena seleccionada a trav�s del men� (click bot�n derecho)
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

	creaCajaZapatos();
}

void igvEscena3D::renderEscenaB() {
	GLfloat color_pieza[] = { 0,0,0.5 };

	// Practica 2a. Parte B.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	int numCajas = 3;

	for (int i = 0; i < numCajas; i++)
	{
		glPushMatrix();
			glTranslatef(0, i , 0);
			creaCajaZapatos();
		glPopMatrix();
	}

}


void igvEscena3D::renderEscenaC() {
	GLfloat color_pieza[] = { 0.5,0,0 };

	// Practica 2a. Parte C.
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	int numCajas = 3;

	for (int x = 0; x < numCajas; x++)
	{
		for (int z = 0; z < numCajas; z++)
		{
			for (int y = 0; y < numCajas; y++)
			{
				glPushMatrix();
				glTranslatef(x * 1.4, y, z * 2.4);
				creaCajaZapatos();
				glPopMatrix();
			}
		}
	}
}


void igvEscena3D::creaCajaZapatos() {
	//Caja de zapatos.
	glPushMatrix();
	glScalef(1, 1, 2);
	glutSolidCube(1);
	glPopMatrix();

	/*Tapadera de caja de zapatos:
		Para tener 0.1 de diferencia en las partes correspondientes a los ejes "x", "y" y "z", a�ado 0.1 para cada lado
		Es decir, 0.2 de m�s para los ejes "x" y "z". El escalado en "y" de 0.2 para que sobresalga tambi�n 0.1 al haberlo
		trasladado 0.4 desde el origen.*/
	glPushMatrix();
		glTranslatef(0, 0.4, 0);
		glScalef(1.2, 0.2, 2.2);
		glutSolidCube(1);
	glPopMatrix();
}

