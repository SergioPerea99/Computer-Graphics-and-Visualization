#include "Clank.h"


/*---- MÉTODOS PARA EL MUÑECO CLANK ----*/

Clank::Clank() {
	/*---- MÉTODOS PARA EL MUÑECO CLANK ----*/
	animacion = true;
	limitIntervalo = true;
	actualValor = 0.0;

	/*NO CAMBIAR LOS VALORES DEL CONSTRUCTOR PARA QUE TENGA SENTIDO LAS MODIFICACIONES DE LOS VALORES EN LAS TECLAS.*/
	cuerpo = 0.0; //FUNCIONANDO ESTE PARAMETRO. MOVER EL CUERPO ALREDEDOR DEL EJE Y 360º.
	cuello = 0.0; //FUNCIONANDO ESTE PARAMETRO. GIRAR HACIA DELANTE Y HACIA ATRÁS EN EL INTERVALO [-30,30].
	cabeza = 0.0; //FUNCIONANDO ESTE PARAMETRO. GIRAR MAX DESDE -90 HASTA 90 GRADOS.
	hombroIzq = 0.0; //FUNCIONANDO ESTE PARAMETRO.
	hombroDer = 0.0; //FUNCIONANDO ESTE PARAMETRO.

	brazoSupDer = 0.0;
	brazoSupIzq = 0.0;
	brazoInfDer = 0.0;
	brazoInfIzq = 0.0;


	piernaSupDer = 90.0; //LIMITAR A 30 Y 150. 
	piernaSupIzq = 90.0; //LIMITAR A 30 Y 150
	piernaInfDer = 0.0;
	piernaInfIzq = 0.0;
}

Clank::~Clank() {}

void Clank::visualizar(float x,float y, float z) {
	/*CREACIÓN DEL MUÑECO CLANK*/
	
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, igvColor(1,1,1).cloneToFloatArray());
		glScalef(0.3, 0.3, 0.3);
		glTranslatef(x, y, z);
		glRotatef(90,0,1,0);
		cuerpoClank();

		glPushMatrix(); /* ---> CONTROL DE LA PARTE SUPERIOR*/
		cuelloClank();
		glPushMatrix();
		cabezaClank();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DEL BRAZO DERECHO.*/
		hombroClank(0.75, 0.5, 0, -90, hombroDer);
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
		hombroClank(-0.75, 0.5, 0, 90, hombroIzq);
		glPushMatrix();
		brazoClank(0, 0, 0, 90, brazoSupIzq);
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
		piernaClank(0, 0, 0.4, piernaInfDer);
		glPushMatrix();
		pieClank(0, 0.16, 0.35);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix(); /*---> CONTROL DE LA PIERNA IZQUIERDA*/
		piernaClank(0.4, -0.5, 0, piernaSupIzq); //TODO: AÑADIR PARAMETRO
		glPushMatrix();
		piernaClank(0, 0, 0.4, piernaInfIzq);
		glPushMatrix();
		pieClank(0, 0.16, 0.35);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void Clank::cuerpoClank() {
	float gris1[3] = { 1 * 0.4, 1 * 0.4, 1 * 0.4 };
	glMaterialfv(GL_FRONT, GL_EMISSION, gris1);
	glTranslatef(0, 1, 0);
	glRotatef(cuerpo, 0, 1, 0);
	glScalef(1, 1.2, 1);
	glutSolidCube(1);

	barrigaClank();
}

void Clank::barrigaClank()
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


void Clank::cuelloClank() {


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

void Clank::cabezaClank() {
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
	ojoClank(0.3, 0.2, 0.75, 10);
	ojoClank(-0.3, 0.2, 0.75, -10);

}

void Clank::orejaClank(float _x, float _y, float _z)
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

void Clank::ojoClank(float _x, float _y, float _z, double gradoContorno)
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

void Clank::antenaClank(float _x, float _y, float _z)
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

void Clank::bocaClank(float _x, float _y, float _z) {
	float rosado[3] = { 0, 0, 0.0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, rosado);
	glTranslated(_x, _y, _z - 0.02);
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


void Clank::hombroClank(float _x, float _y, float _z, double gradosRot, double gradosMov) {
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosRot, 0, 1, 0);
	glRotatef(gradosMov, 0, 0, 1); //TODO: HACERLO RESPECTO al grado que va cambiando y rota el hombro
	glutSolidCone(0.2, 0.3, 30, 20);
}

void Clank::brazoClank(float _x, float _y, float _z, double gradosRot, double gradosMov)
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

void Clank::piernaClank(float _x, float _y, float _z, double gradosMov)
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

void Clank::manoClank(float _x, float _y, float _z, double gradosRot) {
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glRotatef(gradosRot, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 40, 20);
}

void Clank::pieClank(float _x, float _y, float _z) {
	float negro[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, negro);
	glTranslatef(_x, _y, _z);
	glScalef(0.1, 0.4, 0.1);
	glutSolidCube(1);
}


void Clank::setMovCuerpo(float n)
{
	cuerpo = ((int)(cuerpo + n) % 360);
}

void Clank::setMovCuello(float n)
{
	if (cuello + n >= -30 && cuello + n <= 30) cuello += n;
}

void Clank::setMovCabeza(float n)
{
	if (cabeza + n >= -90 && cabeza + n <= 90) cabeza += n;
}

void Clank::setMovHombroIzq(float n)
{
	hombroIzq = ((int)(hombroIzq + n) % 360);
}

void Clank::setMovHombroDer(float n)
{
	hombroDer = ((int)(hombroDer + n) % 360);
}

void Clank::setMovBrazoSupDer(float n) //COMPROBADO QUE DEBE SER ASÍ. SIEMPRE Y CUANDO DIGAMOS QUE EL BRAZO LO PUEDES GIRAR 360º GRACIAS AL HOMBRO Y NO AL BRAZO SUPERIOR.
{
	if (brazoSupDer + n >= -60 && brazoSupDer + n <= 90) brazoSupDer += n;
}

void Clank::setMovBrazoSupIzq(float n) //COMPROBADO QUE DEBE SER ASÍ.  SIEMPRE Y CUANDO DIGAMOS QUE EL BRAZO LO PUEDES GIRAR 360º GRACIAS AL HOMBRO Y NO AL BRAZO SUPERIOR.
{
	if (brazoSupIzq + n >= -90 && brazoSupIzq + n <= 60) brazoSupIzq += n;
}

void Clank::setMovBrazoInfDer(float n) //COMPROBADO QUE DEBE SER ASÍ
{
	if (brazoInfDer + n >= 0 && brazoInfDer + n <= 90)  brazoInfDer += n;
}

void Clank::setMovBrazoInfIzq(float n) //COMPROBADO QUE DEBE SER ASÍ
{
	if (brazoInfIzq + n >= -90 && brazoInfIzq + n <= 0) brazoInfIzq += n;
}

void Clank::setMovPiernaSupDer(float n)
{
	if (piernaSupDer + n >= 30 && piernaSupDer + n <= 150) piernaSupDer += n;
}

void Clank::setMovPiernaSupIzq(float n)
{
	if (piernaSupIzq + n >= 30 && piernaSupIzq + n <= 150) piernaSupIzq += n;
}

void Clank::setMovPiernaInfDer(float n)
{
	if (piernaInfDer + n >= 0 && piernaInfDer + n <= 90) piernaInfDer += n;
}

void Clank::setMovPiernaInfIzq(float n)
{
	if (piernaInfIzq + n >= 0 && piernaInfIzq + n <= 90) piernaInfIzq += n;
}

bool Clank::get_animacion()
{
	return animacion;
}

void Clank::set_animacion(bool _animacion)
{
	animacion = _animacion;
}

bool Clank::get_limitIntervalo()
{
	return limitIntervalo;
}

void Clank::set_limitIntervalo(bool _cambia)
{
	limitIntervalo = _cambia;
}

float Clank::get_actualValor()
{
	return actualValor;
}

void Clank::set_actualValor(float _nuevo)
{
	actualValor = _nuevo;
}