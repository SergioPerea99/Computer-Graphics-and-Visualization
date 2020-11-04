#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */

	igvMallaTriangulos();
	
	
	//static const int num_vertices_max = 10;
	static const float long_cirfunferencia = 2 * 3.14 * r;
	
	/*Instanciar los vertices, según la cantidad de vértices que se necesite.*/
	double angulo;
	int k = 0; int aux = 0;
	num_vertices = 8;
	vertices = new float[num_vertices*3];
	bool circunf_debajo = true;
	for (int i = 1; i <= num_vertices; i++) {
		angulo = long_cirfunferencia / i;
		if (circunf_debajo) {
			vertices[k++] = cos(angulo)*r; aux = 
			vertices[k++] = 0;
			vertices[k++] = sin(angulo)*r;
			circunf_debajo = false;
		}
		else {
			vertices[k++] = cos(angulo)*r;
			vertices[k++] = 4;
			vertices[k++] = sin(angulo)*r;
			circunf_debajo = true;
		}
	}

	/*Instancia de los indices de arriba a abajo en sentido antihorario.*/
	k = 0;
	num_triangulos = (num_vertices - 2); //18
	triangulos = new unsigned int[num_triangulos*3];
	bool intercambia = true;
	for (int i = num_vertices; i > 2; i = i-2) {
		triangulos[k++] = (unsigned int)i;  aux = triangulos[k - 1];
		triangulos[k++] =(unsigned int) i - 3; aux = triangulos[k - 1];
		triangulos[k++] = (unsigned int)i - 1; aux = triangulos[k - 1];
	}
	for (int i = num_vertices; i > 2; i = i - 2) {
		triangulos[k++] = (unsigned int)i - 2; aux = triangulos[k - 1];
		triangulos[k++] = (unsigned int)i - 3; aux = triangulos[k - 1];
		triangulos[k++] = (unsigned int)i; aux = triangulos[k - 1];
	}
	
	visualizar();
	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
}
