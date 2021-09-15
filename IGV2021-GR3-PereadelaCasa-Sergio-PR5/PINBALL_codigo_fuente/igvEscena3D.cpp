#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include <iostream>




// Metodos constructores 
igvEscena3D::igvEscena3D (): clank(), bola(),
	rueda(1,1,50,50), plataformaClank(1.5,0.5,50,50),
	palIzq(2,80,40,45,igvColor(0.5,0.5,0.5)), palDer(2, -80, -40,-45, igvColor(0.5, 0.5, 0.5)){
	ejes = true;

	anchura = 5;
	altura = -0.2;
	profundidad= 12;

	focoX = -anchura;
	focoY = 4;
	focoZ = profundidad;

	texturaCargada = false;
	rotClank = 0.0;

	posPlatX = posPlatY = 0.0;
	posPlatZ = -5.5;
}

igvEscena3D::~igvEscena3D() {
	for (igvTextura* textura : texturas)
		delete textura;
}

// Metodos publicos 

void igvEscena3D::visualizar(void) {
	

	glPushMatrix(); // guarda la matriz de modelado
		
		if (!texturaCargada) {
			texturas.push_back(new igvTextura((char*)"cristal.png"));
			texturas.push_back(new igvTextura((char*)"acero.jpg"));
			texturas.push_back(new igvTextura((char*)"madera.jpg"));
			texturas.push_back(new igvTextura((char*)"techo_cristalera2.jpg"));
			texturaCargada = true;
		}
		
		
		creaIluminacion(anchura, profundidad);

		igvMaterial prop_material2 = igvMaterial(igvColor(0.439216, 0.576471, 0.858824), igvColor(0.439216, 0.576471, 0.858824), igvColor(0.439216, 0.576471, 0.858824), 120);
		prop_material2.aplicar();

		bola.visualizar(bola.getPosX(), bola.getPosY(), bola.getPosZ());
		
		bordesEscenario(anchura, profundidad);

		trianguloInfDer(anchura, profundidad);
		trianguloInfIzq(anchura, profundidad);
		palIzq.visualizar(-2, 0, profundidad -3);
		palDer.visualizar(2, 0, profundidad -3);

		igvMaterial prop_material3 = igvMaterial(igvColor(0, 0, 0), igvColor(0, 0, 0), igvColor(0, 0, 0), 120);
		prop_material3.aplicar();

		pintarPatas_tablero();
		
		glPushMatrix();
			igvColor coef_ambiental = igvColor(0.90, 0.91, 0.98);
			igvColor coef_difuso = igvColor(0.90, 0.91, 0.98);
			igvColor coef_especular = igvColor(0.90, 0.91, 0.98);
			igvMaterial prop_material = igvMaterial(coef_ambiental, coef_difuso, coef_especular, 120);
			prop_material.aplicar();
			glPushMatrix();
				glTranslatef(posPlatX, posPlatY, posPlatZ);
				clank.visualizar(0, 2.6, 1);
				glPushMatrix();
					texturas[1]->aplicar(0);
					plataformaClank.setGradRotX(90);
					plataformaClank.setGradRotY(rotClank);
					plataformaClank.visualizar("GL_SMOOTH", 0, 0.05, 0.5);
				glPopMatrix();
				glPushMatrix();
					texturas[0]->aplicar(0);
					rueda.visualizar("GL_FLAT", 0, 1.6, 0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			texturas[0]->aplicar(0);
			pintar_tablero(anchura, profundidad);
		glPopMatrix();

    glPopMatrix(); // restaura la matriz de modelado

	
	glPushMatrix();
		pintar_suelo_techo(anchura * 3, profundidad, profundidad * 3);
		texturas[2]->aplicar(2);
		pintar_paredes(anchura * 3, profundidad, profundidad * 3);
		accesoriosEscenario();
		texturas[0]->aplicar(0); 
	glPopMatrix();
	

}


/*---- MÉTODOS PARA LA CREACIÓN DE OBJETOS VISIBLES EN EL ESCENARIO ----*/

void igvEscena3D::pintar_suelo_techo(float tam_x, float tam_y, float tam_z) {

	int div_x = 30;
	int div_z = 30;

	texturas[2]->aplicar(0);
	glNormal3f(0, 1, 0); //CREACIÓN DEL SUELO
	for (float ini_x = -tam_x; ini_x < tam_x; ini_x += tam_x / div_x) {
		for (float ini_z = -tam_z; ini_z < tam_z; ini_z += tam_z / div_z) {
			glBegin(GL_QUADS);
			glTexCoord2f(ini_x / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, altura - 1, ini_z);

			glTexCoord2f(ini_x / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, altura - 1, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), altura - 1, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), altura - 1, ini_z);
			glEnd();
		}
	}

	texturas[3]->aplicar(2);
	//CREACIÓN DEL TECHO
	for (float ini_x = -tam_x; ini_x < tam_x; ini_x += tam_x / div_x) {
		for (float ini_z = -tam_z; ini_z < tam_z; ini_z += tam_z / div_z) {
			glBegin(GL_QUADS);
			glTexCoord2f(ini_x / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, tam_y, ini_z);

			glTexCoord2f(ini_x / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, tam_y, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), tam_y, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), tam_y, ini_z);
			glEnd();
		}
	}
}

void igvEscena3D::pintar_paredes(float tam_x, float tam_y, float tam_z)
{
	int div_x = 40;
	int div_y = 40;
	int div_z = 40;


	glNormal3f(0, 0, 1); //CREACIÓN DE LA PARED DEL FONDO
	for (float ini_x = -tam_x; ini_x < tam_x; ini_x += tam_x / div_x) {
		for (float ini_y = -tam_y / 2; ini_y < tam_y; ini_y += tam_y / div_y) {
			glBegin(GL_QUADS);
			glTexCoord2f(ini_x / tam_x, ini_y / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x, ini_y, -tam_z / 2);

			glTexCoord2f(ini_x / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x, ini_y + (tam_y / div_y), -tam_z / 2);

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), ini_y + (tam_y / div_y), -tam_z / 2);

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_y / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), ini_y, -tam_z / 2);
			glEnd();
		}
	}

	//CREACIÓN DE LA PARED TRASERA
	for (float ini_x = -tam_x; ini_x < tam_x; ini_x += tam_x / div_x) {
		for (float ini_y = -tam_y; ini_y < tam_y; ini_y += tam_y / div_y) {
			glBegin(GL_QUADS);
			glTexCoord2f(ini_x / tam_x, ini_y / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x, ini_y, tam_z);

			glTexCoord2f(ini_x / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x, ini_y + (tam_y / div_y), tam_z);

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), ini_y + (tam_y / div_y), tam_z);

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_y / tam_y); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), ini_y, tam_z);
			glEnd();
		}
	}

	//CREACIÓN DE PAREDES LATERALES
	glNormal3f(1, 0, 0); //CREACIÓN DE LA PARED DEL FONDO
	for (float ini_y = -tam_y; ini_y < tam_y; ini_y += tam_y / div_y) {
		for (float ini_z = -tam_z; ini_z < tam_z; ini_z += tam_z / div_z) {
			glBegin(GL_QUADS);
			//glTexCoord2f(ini_y / tam_y, ini_z / tam_z); //Escalado entre [0,1]
			glTexCoord2f(ini_z / tam_z, ini_y / tam_y);
			glVertex3f(-tam_x, ini_y, ini_z);

			//glTexCoord2f((ini_y + (tam_y / div_y)) / tam_y, ini_z/ tam_z); //Escalado entre [0,1]
			glTexCoord2f(ini_z / tam_z, (ini_y + (tam_y / div_y)) / tam_y);
			glVertex3f(-tam_x, ini_y + (tam_y / div_y), ini_z);

			//glTexCoord2f((ini_y + (tam_y / div_y)) / tam_y, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glTexCoord2f((ini_z + (tam_z / div_z)) / tam_z, (ini_y + (tam_y / div_y)) / tam_y);
			glVertex3f(-tam_x, ini_y + (tam_y / div_y), ini_z + (tam_z / div_z));

			//glTexCoord2f(ini_y / tam_y, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glTexCoord2f((ini_z + (tam_z / div_z)) / tam_z, ini_y / tam_y);
			glVertex3f(-tam_x, ini_y, ini_z + (tam_z / div_z));
			glEnd();
		}
	}

	for (float ini_y = -tam_y; ini_y < tam_y; ini_y += tam_y / div_y) {
		for (float ini_z = -tam_z; ini_z < tam_z; ini_z += tam_z / div_z) {
			glBegin(GL_QUADS);
			//glTexCoord2f(ini_y / tam_y, ini_z / tam_z); //Escalado entre [0,1]
			glTexCoord2f(ini_z / tam_z, ini_y / tam_y);
			glVertex3f(tam_x, ini_y, ini_z);

			//glTexCoord2f((ini_y + (tam_y / div_y)) / tam_y, ini_z/ tam_z); //Escalado entre [0,1]
			glTexCoord2f(ini_z / tam_z, (ini_y + (tam_y / div_y)) / tam_y);
			glVertex3f(tam_x, ini_y + (tam_y / div_y), ini_z);

			//glTexCoord2f((ini_y + (tam_y / div_y)) / tam_y, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glTexCoord2f((ini_z + (tam_z / div_z)) / tam_z, (ini_y + (tam_y / div_y)) / tam_y);
			glVertex3f(tam_x, ini_y + (tam_y / div_y), ini_z + (tam_z / div_z));

			//glTexCoord2f(ini_y / tam_y, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glTexCoord2f((ini_z + (tam_z / div_z)) / tam_z, ini_y / tam_y);
			glVertex3f(tam_x, ini_y, ini_z + (tam_z / div_z));
			glEnd();
		}
	}


}

void igvEscena3D::pintar_tablero(float tam_x, float tam_z) {
	int div_x = 100;
	int div_z = 100;


	glNormal3f(0, 1, 0); //CREACIÓN PARAMETRIZADA DE QUADS SEGÚN DIVISIONES:
	for (float ini_x = -anchura; ini_x < tam_x; ini_x += tam_x / div_x) {
		for (float ini_z = -profundidad; ini_z < tam_z; ini_z += tam_z / div_z) {
			glBegin(GL_QUADS);
			glTexCoord2f(ini_x / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, altura, ini_z);

			glTexCoord2f(ini_x / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x, altura, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_z + (tam_z / div_z)) / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), altura, ini_z + (tam_z / div_z));

			glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_z / tam_z); //Escalado entre [0,1]
			glVertex3f(ini_x + (tam_x / div_x), altura, ini_z);
			glEnd();
		}
	}

}

void igvEscena3D::pintarPatas_tablero() {
	glPushMatrix();
		float negro[3] = { 0.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, negro);
		GLUquadricObj* pata = gluNewQuadric();
		//INFERIOR IZQUIERDA
		glPushMatrix();
			glTranslatef(-anchura+0.2,altura,profundidad-0.2);
			glRotatef(90, 1, 0, 0);
			glScalef(0.3,0.3,2);
			gluCylinder(pata, 1, 1, 1, 40, 3);
		glPopMatrix();
		//INFERIOR DERECHA
		glPushMatrix();
			glTranslatef(anchura-0.2, altura, profundidad-0.2);
			glRotatef(90, 1, 0, 0);
			glScalef(0.3, 0.3, 2);
			gluCylinder(pata, 1, 1, 1, 40, 3);
		glPopMatrix();
		//SUPERIOR IZQUIERDA
		glPushMatrix();
			glTranslatef(-anchura+0.2, altura, -profundidad+0.2);
			glRotatef(90, 1, 0, 0);
			glScalef(0.3, 0.3, 2);
			gluCylinder(pata, 1, 1, 1, 40, 3);
		glPopMatrix();
		//SUPERIOR DERECHA
		glPushMatrix();
			glTranslatef(anchura-0.2, altura, -profundidad+0.2);
			glRotatef(90, 1, 0, 0);
			glScalef(0.3, 0.3, 2);
			gluCylinder(pata, 1, 1, 1, 40, 3);
		glPopMatrix();
		gluDeleteQuadric(pata);
		pata = nullptr;
	glPopMatrix();
}

void igvEscena3D::creaIluminacion(float tamX, float tamZ) {
	glEnable(GL_LIGHTING); //Activar la iluminación

	/*FOCO IZQUIERDO ABAJO TABLERO*/
	Iluminacion luz_foco1(igvColor(0, 0, 0, 1), igvColor(0.25, 0.0, 0, 1), igvColor(0.25, 0.0, 0, 1), igvPunto3D(-tamX, focoY , tamZ), igvPunto3D(1, -1, -1), GL_LIGHT0);
	luz_foco1.getFoco().aplicar();

	/*FOCO IZQUIERDO ARRIBA TABLERO*/
	Iluminacion luz_foco2(igvColor(0, 0, 0, 1), igvColor(0.5, 0.0, 0, 1), igvColor(0.5, 0.0, 0), igvPunto3D(-tamX, focoY , -tamZ), igvPunto3D(1, -1, 1), GL_LIGHT1);
	luz_foco2.getFoco().aplicar();

	/*FOCO DERECHO ARRIBA TABLERO*/
	Iluminacion luz_foco3(igvColor(0, 0, 0, 1), igvColor(0.5, 0.0, 0, 1), igvColor(0.5, 0.0, 0), igvPunto3D(tamX, focoY , -tamZ), igvPunto3D(-1, -1, 1), GL_LIGHT2);
	luz_foco3.getFoco().aplicar();

	/*FOCO DERECHO ABAJO TABLERO*/
	Iluminacion luz_foco4(igvColor(0, 0, 0, 1), igvColor(0.5, 0.0, 0, 1), igvColor(0.5, 0.0, 0), igvPunto3D(tamX, focoY, tamZ), igvPunto3D(-1, -1, -1), GL_LIGHT3);
	luz_foco4.getFoco().aplicar();


	/*FOCO ENCIMA DE LAS PALANCAS DEL TABLERO*/
	Iluminacion luz_foco5(igvColor(0, 0, 0, 1), igvColor(0.5, 0.5, 0.5, 1), igvColor(0.5, 0.5, 0.5), igvPunto3D(0, focoY-1.7, tamZ), igvPunto3D(0, -1, 0), GL_LIGHT4);
	luz_foco5.getFoco().aplicar();

	/*ILUMINACION A LA VENTANA*/
	Iluminacion luz_foco6(igvColor(0, 0, 0, 1), igvColor(0.5, 0.5, 0, 1), igvColor(0.5, 0.5, 0), igvPunto3D(0, altura + 2, -profundidad - 6), igvPunto3D(0, -1, 1), GL_LIGHT5);
	luz_foco6.getFoco().aplicar();

}

void igvEscena3D::accesoriosEscenario() {
	//Contorno del cuadro en la pared 
	glPushMatrix();
		glTranslatef(0,altura+3,-profundidad * 1.5);
		glScalef(anchura*1.5,1,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, altura + 8, -profundidad * 1.5);
		glScalef(anchura*1.5, 1, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(anchura * 1.5/ 2, altura + 5.5, -profundidad * 1.5);
		glScalef(1, 6, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-anchura * 1.5 / 2, altura + 5.5, -profundidad * 1.5);
		glScalef(1, 6, 1);
		glutSolidCube(1);
	glPopMatrix();
	texturas[3]->aplicar(2);
	//QUAD para generar la imagen en el cuadro
	glPushMatrix();
		int div_x = 20;
		int div_y = 20;
		float tam_x = anchura * 1.5, tam_y = altura + 8, tam_z = profundidad * 1.49;
		glNormal3f(0, 0, 1); //CREACIÓN DE LA PARED DEL FONDO
		for (float ini_x = -tam_x/2; ini_x < tam_x/2; ini_x += tam_x / div_x) {
			for (float ini_y = altura + 3; ini_y < tam_y; ini_y += tam_y / div_y) {
				glBegin(GL_QUADS);
				glTexCoord2f(ini_x / tam_x, ini_y / tam_y); //Escalado entre [0,1]
				glVertex3f(ini_x, ini_y, -tam_z);

				glTexCoord2f(ini_x / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
				glVertex3f(ini_x, ini_y + (tam_y / div_y), -tam_z );

				glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, (ini_y + (tam_y / div_y)) / tam_y); //Escalado entre [0,1]
				glVertex3f(ini_x + (tam_x / div_x), ini_y + (tam_y / div_y), -tam_z);

				glTexCoord2f((ini_x + (tam_x / div_x)) / tam_x, ini_y / tam_y); //Escalado entre [0,1]
				glVertex3f(ini_x + (tam_x / div_x), ini_y, -tam_z );
				glEnd();
			}
		}
	glPopMatrix();
}


/*---- MÉTODOS PARA LA CREACIÓN DE BORDES Y ELIMINACIÓN DE ESQUINAS INFERIORES DEL TABLERO ----*/

void igvEscena3D::bordesEscenario(float tamX, float tamZ) {
	glPushMatrix();
		igvMaterial prop_material2 = igvMaterial(igvColor(0.8, 0.8, 0.8), igvColor(0.8, 0.8, 0.8), igvColor(0.8, 0.8, 0.8), 120);
		prop_material2.aplicar();
		/*PARED DE LA IZQUIERDA*/
		glPushMatrix();
			glTranslatef(-tamX, 0, 0);
			glScalef(0.5, 0.5, tamZ*2);
			glutSolidCube(1);
		glPopMatrix();

		/*PARED DE LA DERECHA*/
		glPushMatrix();
			glTranslatef(tamX, 0, 0);
			glScalef(0.5, 0.5, tamZ*2);
			glutSolidCube(1);
		glPopMatrix();

		/*PARED DEL FONDO*/
		glPushMatrix();
			glTranslatef(0, 0, -tamZ);
			glScalef(tamX*2+0.5, 0.5, 0.5);
			glutSolidCube(1);
		glPopMatrix();

		/*PARED DEL INICIO*/
		glPushMatrix();
			glTranslated(0, 0, tamZ);
			glScalef(tamX*2+0.5, 0.5, 0.5);
			glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();
	
}

void igvEscena3D::trianguloInfDer(float anchura, float profundidad)
{
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glTranslatef(anchura - (anchura / 2 - 1), altura, profundidad - profundidad / 3 + 1);
	glScalef((anchura / 2), 0.4, profundidad / 2 - 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	igvCilindro triangulo(1.65, 0.3, 3, 40);
	triangulo.setGradRotX(90);
	triangulo.visualizar("GL_SMOOTH", anchura - 1.05, altura, profundidad / 2 + 0.5);
	glPopMatrix();
}

void igvEscena3D::trianguloInfIzq(float anchura, float profundidad)
{
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glTranslatef(-anchura + (anchura / 2 - 1), altura, profundidad - profundidad / 3 + 1);
	glScalef((anchura / 2), 0.4, profundidad / 2 - 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	igvCilindro triangulo(1.65, 0.3, 3, 40);
	triangulo.setGradRotY(180);
	triangulo.setGradRotX(90);
	triangulo.visualizar("GL_SMOOTH", -anchura + 1.05, altura, profundidad / 2 + 0.5);
	glPopMatrix();

}



/*---- GETTERS Y SETTERS ----*/

void igvEscena3D::set_focoX(float x)
{
	focoX = x;
}

void igvEscena3D::set_focoY(float y)
{
	focoY = y;
}

void igvEscena3D::set_focoZ(float z)
{
	focoZ = z;
}

float igvEscena3D::get_focoX() const
{
	return focoX;
}

float igvEscena3D::get_focoY() const
{
	return focoY;
}

float igvEscena3D::get_focoZ() const
{
	return focoZ;
}

Palanca& igvEscena3D::getPalIzq()
{
	return palIzq;
}

Palanca& igvEscena3D::getPalDer()
{
	return palDer;
}

float igvEscena3D::getAnchura()
{
	return anchura;
}

float igvEscena3D::getLongitud() {
	return profundidad;
}

Bola& igvEscena3D::getBola()
{
	return bola;
}

float igvEscena3D::getRotClank()
{
	return rotClank;
}

void igvEscena3D::setRotClank(float rot)
{
	rotClank = rot;
}

float igvEscena3D::getPlat_posX()
{
	return posPlatX;
}

void igvEscena3D::setPlat_posX(float x)
{
	posPlatX = x;
}

float igvEscena3D::getPlat_posZ()
{
	return posPlatZ;
}

void igvEscena3D::setPlat_posZ(float z)
{
	posPlatZ = z;
}


igvCilindro& igvEscena3D::getPlataformaClank()
{
	return plataformaClank;
}

Clank& igvEscena3D::getClank()
{
	return clank;
}

igvCilindro& igvEscena3D::getRueda()
{
	return rueda;
}

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

