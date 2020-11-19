#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//Inicialización de los grados para la rotación de cada parte de la figura:
	cuerpo = 0.0; //FUNCIONANDO ESTE PARAMETRO. MOVER EL CUERPO ALREDEDOR DEL EJE Y 360º.
	cuello = -20.0; //FUNCIONANDO ESTE PARAMETRO. GIRAR HACIA DELANTE Y HACIA ATRÁS EN EL INTERVALO [-30,30].
	cabeza = -30.0; //FUNCIONANDO ESTE PARAMETRO. GIRAR MAX DESDE -90 HASTA 90 GRADOS.
	hombroIzq = 0.0; //FUNCIONANDO ESTE PARAMETRO.
	hombroDer = 0.0; //FUNCIONANDO ESTE PARAMETRO.

	brazoSupDer = 0.0;
	brazoSupIzq = 0.0;
	brazoInfDer = 50.0;
	brazoInfIzq = 10.0;


	piernaSupDer = 100.0; //LIMITAR A 30 Y 150
	piernaSupIzq = 60.0; //LIMITAR A 30 Y 150
	piernaInfDer = 20.0;
	piernaInfIzq = 20.0;

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

/*TORSO DE CLANK*/

void igvEscena3D::cuerpoClank() {
	float gris1[3] = { 1 * 0.4, 1 * 0.4, 1 * 0.4 };
	glMaterialfv(GL_FRONT, GL_EMISSION, gris1);
	glTranslatef(0, 1, 0);
	glRotatef(cuerpo, 0, 1, 0);
	glScalef(1, 1.2, 1);
	glutSolidCube(1);

	barrigaClank();
}

void igvEscena3D::barrigaClank()
{
	float negro[3] = { 0, 0, 0 }; //Porcentaje de grises a usar. 
	float gris1[3] = { 1 * 0.4, 1 * 0.4, 1 * 0.4 };
	glPushMatrix();
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
	glPopMatrix();
}





/*PARTE SUPERIOR DE CLANK*/

void igvEscena3D::cuelloClank() {

	
	glTranslatef(0, 0.75, 0);
	glRotatef(cuello, 1, 0, 0); //TODO: CONTROLA EL MOV DEL CUELLO HACIA ATRAS Y HACIA DELANTE.

	glPushMatrix();
		//Cilindro para el cuello
		glRotatef(90, 1, 0, 0);
		float negro[3] = { 0.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, negro);
		GLUquadricObj* cuello = gluNewQuadric();
		gluCylinder(cuello, 0.1, 0.1, 0.3, 40, 3);
		gluDeleteQuadric(cuello);
		cuello = nullptr;
	glPopMatrix();

}

void igvEscena3D::cabezaClank() {
	//CONTORNO PRINCIPAL DE LA CABEZA.
	float gris2[3] = { 1 * 0.3,1 * 0.3,1 * 0.3 };
	glMaterialfv(GL_FRONT, GL_EMISSION, gris2);
	glTranslatef(0, 0.6, 0);
	glRotatef(cabeza, 0, 1, 0);
	glutSolidSphere(0.8, 20, 20);
	//Accesorios de la cara sin posterior movilidad propia:
	//OREJAS.
	glPushMatrix();
	float gris3[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, gris3);
	orejaClank(0.8, 0, 0);
	orejaClank(-0.85, 0, 0);
	glPopMatrix();

	//ANTENA
	antenaClank(0, 1.2, -0.2);

	//BOCA
	bocaClank(0, -0.4, 0.7);

	//OJOS
	ojoClank(0.3, 0.2, 0.75,10);
	ojoClank(-0.3, 0.2, 0.75,-10);

}

void igvEscena3D::orejaClank(float _x, float _y, float _z)
{
	glPushMatrix();
		glTranslatef(_x, _y, _z);
		glRotatef(90, 0, 1, 0);
		GLUquadricObj* oreja = gluNewQuadric(); //Creo el espacio en memoria para mostrarlo y luego borrarlo en el destructor.
		gluCylinder(oreja, 0.2, 0.2, 0.1, 40, 20);
		gluDeleteQuadric(oreja);

		oreja = gluNewQuadric(); //Creo el espacio en memoria para mostrarlo y luego borrarlo en el destructor.
		gluCylinder(oreja, 0.1, 0.2, 0.1, 40, 20);
		gluDeleteQuadric(oreja);
		oreja = nullptr;
	glPopMatrix();
}

void igvEscena3D::ojoClank(float _x, float _y, float _z, double gradoContorno)
{
	glPushMatrix();
		float negro[3] = { 0,0,0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, negro);
		glTranslatef(_x, _y, _z);
		glRotatef(gradoContorno, 0, 1, 0);
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
		glRotatef(45, 1, 0, 0);
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
	float rosado[3] = { 0, 0, 0.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x, _y, _z-0.02);
		glScalef(0.6, 0.05, 0.05);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x + 0.4, _y + 0.07, _z - 0.1);
		glRotatef(30, 0, 0, 1);
		glRotatef(20, 0, 1, 0);
		glScalef(0.3, 0.04, 0.05);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
		glTranslated(_x - 0.4, _y + 0.07, _z - 0.1);
		glRotatef(-30, 0, 0, 1);
		glRotatef(-20, 0, 1, 0);
		glScalef(0.3, 0.04, 0.05);
		glutSolidCube(1);
	glPopMatrix();

}


/*MIEMBROS ARTICULADOS DE CLANK*/

void igvEscena3D::hombroClank(float _x, float _y, float _z, double gradosRot, double gradosMov) {
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosRot, 0, 1, 0);
	glRotatef(gradosMov, 0, 0, 1); //TODO: HACERLO RESPECTO al grado que va cambiando y rota el hombro
	glutSolidCone(0.2, 0.3, 30, 20);
}

void igvEscena3D::brazoClank(float _x, float _y, float _z, double gradosRot, double gradosMov)
{
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosRot, 1, 0, 0);
	glRotatef(gradosMov, 0, 1, 0); //TODO: HACERLO RESPECTO al grado que va cambiando y rota el brazo superior
	GLUquadricObj* cilindro = gluNewQuadric();
	gluCylinder(cilindro, 0.05, 0.03, 0.4, 40, 3);
	gluDeleteQuadric(cilindro);
	cilindro = nullptr;
}

void igvEscena3D::piernaClank(float _x, float _y, float _z, double gradosMov)
{
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosMov, 1, 0, 0); //TODO: HACERLO RESPECTO al grado que va cambiando y rota el brazo superior
	GLUquadricObj* cilindro = gluNewQuadric();
	gluCylinder(cilindro, 0.05, 0.03, 0.4, 40, 3);
	gluDeleteQuadric(cilindro);
	cilindro = nullptr;
}

void igvEscena3D::manoClank(float _x, float _y, float _z, double gradosRot) {
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosRot, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1,40,20);

	
	
}





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
		cuerpoClank();

		glPushMatrix(); /* ---> CONTROL DE LA PARTE SUPERIOR*/
			cuelloClank();
			glPushMatrix();
				cabezaClank();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DEL BRAZO DERECHO.*/
			hombroClank(0.75, 0.5, 0,-90,hombroDer);
			
			glPushMatrix();
				brazoClank(0, 0, 0, 90, brazoSupDer); 
				glPushMatrix();
					brazoClank(0, 0, 0.4, 0, brazoInfDer);
					glPushMatrix();
						manoClank(0, 0, 0.4, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DEL BRAZO IZQUIERDO.*/
			hombroClank(-0.75, 0.5, 0,90,hombroIzq);
			glPushMatrix();
				brazoClank(0, 0, 0, 90,brazoSupIzq); 
				glPushMatrix();
					brazoClank(0, 0, 0.4, 0, brazoInfIzq);
					glPushMatrix();
						manoClank(0, 0, 0.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DE LA PIERNA DERECHA*/
			piernaClank(-0.4, -0.5, 0, piernaSupDer); //TODO: AÑADIR PARAMETRO
			glPushMatrix();
				piernaClank(0, 0, 0.3,piernaInfDer);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DE LA PIERNA IZQUIERDA*/
			piernaClank(0.4, -0.5, 0,piernaSupIzq); //TODO: AÑADIR PARAMETRO
			glPushMatrix();
				piernaClank(0, 0, 0.3, piernaInfIzq);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();


	glPopMatrix(); // restaura la matriz de modelado
}

