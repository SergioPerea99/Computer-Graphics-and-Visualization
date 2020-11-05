#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */

	igvMallaTriangulos();
	
	/*Instanciar los vertices, según la cantidad de vértices que se necesite.*/
	static const float long_cirfunferencia = 360;
	int k = 0; 

	num_vertices = divU;
	vertices = new float[num_vertices*3];
	int circunf_debajo = 0;
	float angulo = long_cirfunferencia / num_vertices;
	
	float i = 0; 
	/*Inicio de la altura para los vertices hasta la altura indicada.*/
	while (i <= a) {
		k = creaCircunferencia(i, r, divU, k); /*Ahora creo una circunferencia, por cada posición de altura actual.*/
		i += a / divV;
	}

	/*Instancia de los indices de arriba a abajo en sentido antihorario.*/
	k = 0;
	num_triangulos = (num_vertices - 2); 
	triangulos = new unsigned int[num_triangulos*3];

	for (int i = num_vertices; i > 2; i = i-2) {
		triangulos[k++] = i;
		triangulos[k++] = i - 3;
		triangulos[k++] = (unsigned int)i - 1; 
	}
	for (int i = num_vertices; i > 2; i = i - 2) {
		triangulos[k++] = (unsigned int)i - 2;
		triangulos[k++] = (unsigned int)i - 3;
		triangulos[k++] = (unsigned int)i;
	}
	
	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
}


int igvCilindro::creaCircunferencia(float _altura,float r, int divU, int k) {
	float angulo = 0;
	while (angulo < 360) {
		/*Hay que convertilo en radianes para que funcione, entonces multiplico el angulo por PI / 180 */
		float radianes = angulo * PI / 180;
		vertices[k++] = cos(radianes) * r;
		vertices[k++] = _altura;
		vertices[k++] = sin(radianes) * r;
		angulo = angulo + (360 / divU);
	}
	return k;
}