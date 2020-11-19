#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//Inicialización de los grados para la rotación de cada parte de la figura:
	cuerpo = 0.0;
	cuello = 90;
	cabeza = 0.0;
	hombroIzq = 0.0;
	hombroDer = 0.0;
	antena = 45;
	// Apartado C: inicializar los atributos para el control de los grados de libertad del modelo 

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

///// Apartado B: Métodos para visualizar cada parte del modelo

////// Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena (también habría que desactivar la de arriba).



	///// Apartado B: aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
	/////             se recomienda crear una método auxiliar que encapsule todo el código para la visualización
	/////             del modelo, dejando aquí sólo la llamada a ese método, así como distintas funciones una para cada
	/////			  parte del modelo. 
	
	//JERARQUÍA DEL ÁRBOL.
	glPushMatrix(); 
		glTranslatef(0, 1, 0);
		cuerpoClank();
		glPushMatrix();
			glTranslatef(0, 0.75, 0);
			//TODO:ROTAR CUELLO HACIA ATRAS Y HACIA DELANTE HASTA UN CIERTO LIMITE.
			cuelloClank();
			glPushMatrix();
				glTranslatef(0, 0.8, 0);
				//TODO:ROTAR CABEZA HACIA IZQ Y DER HASTA UN CIERTO LIMITE.
				cabezaClank();
				glPushMatrix();
					//TODO: INTERCAMBIAR COLOR DE LOS OJOS SEGÚN SE VAYA PULSANDO UNA TECLA.
					ojoClank(0.3, 0.2, 0.8);
					ojoClank(-0.3, 0.2, 0.8);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


	glPopMatrix(); // restaura la matriz de modelado
}




/*TORSO DE CLANK*/

void igvEscena3D::cuerpoClank() {
	float negro[3] = { 0, 0, 0 }; //Porcentaje de grises a usar. 
	float gris1[3] = { 1 * 0.4, 1 * 0.4, 1 * 0.4 };
	float blanco[3] = { 1,1,1 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, gris1);
		glRotatef(cuerpo, 0, 1, 0);
		glScalef(1, 1.2, 1);
		glutSolidCube(1);

		barrigaClank();
	glPopMatrix();
}

void igvEscena3D::barrigaClank()
{
	float negro[3] = { 0, 0, 0 }; //Porcentaje de grises a usar. 
	float gris1[3] = { 1 * 0.4, 1 * 0.4, 1 * 0.4 };

	glTranslatef(0, -0.1, 0.5);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glScalef(0.7, 0.6, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, gris1);
	glScalef(0.6, 0.5, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glScalef(0.5, 0.4, 0.4);
	glutSolidCube(1);
	glPopMatrix();
}





/*PARTE SUPERIOR DE CLANK*/

void igvEscena3D::cuelloClank() {
	glPushMatrix();

	float negro[3] = { 0.0, 0.0, 0.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glRotatef(cuello, 1, 0 , 0);

	//Cilindro para el cuello
	GLUquadricObj* cuello = gluNewQuadric();
	gluCylinder(cuello, 0.1, 0.1, 0.3, 40, 3);
	gluDeleteQuadric(cuello);
	cuello = nullptr;

	glPopMatrix();
}

void igvEscena3D::cabezaClank() {
	glPushMatrix();
		//CONTORNO PRINCIPAL DE LA CABEZA.
		float gris2[3] = {1*0.3,1*0.3,1*0.3};
		glMaterialfv(GL_FRONT, GL_EMISSION, gris2);
		glRotatef(cabeza, 0, 0, 0);
		glutSolidSphere(0.8, 20, 20);
		//Accesorios de la cara sin posterior movilidad propia:
		//OREJAS.
		glPushMatrix();
			float gris3[3] = {0,0,0};
			glMaterialfv(GL_FRONT, GL_EMISSION, gris3);
			orejaClank(0.8, 0, 0);
			orejaClank(-0.85, 0, 0);
		glPopMatrix();

		//ANTENA
		antenaClank(0,1.2,-0.2);

		//BOCA
		bocaClank(0, -0.4, 0.7);

	glPopMatrix();
}

void igvEscena3D::orejaClank(float _x, float _y, float _z)
{
	glPushMatrix();
		glTranslatef(_x, _y, _z);
		glRotatef(90, 0, 1, 0);
		GLUquadricObj* oreja = gluNewQuadric(); //Creo el espacio en memoria para mostrarlo y luego borrarlo en el destructor.
		gluCylinder(oreja, 0.2, 0.2, 0.1, 40, 3);
		gluDeleteQuadric(oreja);

		oreja = gluNewQuadric(); //Creo el espacio en memoria para mostrarlo y luego borrarlo en el destructor.
		gluCylinder(oreja, 0.1, 0.1, 0.1, 40, 3);
		gluDeleteQuadric(oreja);
		oreja = nullptr;
	glPopMatrix();
}

void igvEscena3D::ojoClank(float _x, float _y, float _z)
{
	glPushMatrix();
		float negro[3] = {0,0,0};
		glMaterialfv(GL_FRONT, GL_EMISSION, negro);
		glTranslatef(_x, _y, _z);
		glutSolidTorus(0.05, 0.2, 30, 20);
		glPushMatrix();
			float verde[3] = { 0,1,0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, verde);
			glutSolidSphere(0.15, 30, 4);
		glPopMatrix();
	glPopMatrix();
}

void igvEscena3D::antenaClank(float _x, float _y, float _z)
{
	glPushMatrix();
		float negro[3] = { 0.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, negro);
		glTranslatef(_x, _y, _z);
		glRotatef(antena, 1, 0, 0);
		//Cilindro para la antena
		GLUquadricObj* antena = gluNewQuadric();
		gluCylinder(antena, 0.005, 0.03, 0.8, 40, 3);
		gluDeleteQuadric(antena);
		antena = nullptr;
		glPushMatrix();
			float rojo[3] = { 1,0,0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
			glutSolidSphere(0.1, 30, 4);
		glPopMatrix();
	glPopMatrix();
}

void igvEscena3D::bocaClank(float _x, float _y, float _z) {
	float rosado[3] = { 0.1, 0.05, 0.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x, _y,_z);
		glScalef(0.6, 0.05, 0.05);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x+0.4, _y+0.05, _z-0.1);
		glRotatef(30, 0, 0, 1);
		glRotatef(20, 0, 1, 0);
		glScalef(0.3, 0.04, 0.05);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x - 0.4, _y + 0.05, _z-0.1);
		glRotatef(-30, 0, 0, 1);
		glRotatef(-20, 0, 1, 0);
		glScalef(0.3, 0.04, 0.05);
		glutSolidCube(1);
	glPopMatrix();
	
}
