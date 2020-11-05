#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */

	
	num_vertices = (divU+1)*(divV+1); //Formula sacada de hacer comprobaciones
	vertices = new float[num_vertices*3];

	float i = 0; int k = 0;
	while (i <= a) { /*MIENTRAS no se pase de la altura pasada por parametro.*/
		k = creaCircunferencia(i, r, divU, k); /*Ahora creo una circunferencia, por cada posición de altura actual.*/
		i += a / divV;
	}

	/*Instancia de los indices de arriba a abajo en sentido antihorario.*/
	
	num_triangulos = (divU*2) * divV; //Formula sacada de hacer comprobaciones.
	triangulos = new unsigned [num_triangulos * 3];
	
	int cont_triangulos = 0; k = 0; /*Con la i voy a controlar el numero de triangulos añadidos.*/
	for (float altu = 0; altu < a; altu += a/divV) { /*Creación de triangulos por cada partición de altura (En esta práctica 2)*/
		for (int j = 0; j+1 < (divU + 1); j++) {
			/*Triangulo que empieza por el vértice superior izquierdo (relativo a un rectangulo que conecta 2 triangulos).*/
			triangulos[k++] = (divU)+ altu + j; /*Vertice superior izquierdo*/
			triangulos[k++] = j+ altu; /*Vertice inferior izquierdo*/
			triangulos[k++] = (divU) + altu + j + 1; /*Vertice superior siguiente.*/

			/*Triangulo que empieza por el vértice superior derecho (relativo a un rectangulo que conecta 2 triangulos).*/
			triangulos[k++] = (divU)+altu + j + 1; /*Vertice superior derecho*/
			triangulos[k++] = j+altu; /*Vertice inferior izquierdo*/
			triangulos[k++] = j + altu + 1; /*Vertice inferior siguiente.*/

			/*2 triangulos añadidos, entonces:*/
			cont_triangulos += 2;
		}
	}
	
	
	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
}


int igvCilindro::creaCircunferencia(float _altura,float r, int divU, int k) {
	float radianes = 0; float aux;
	while (radianes <= 2*PI*r) {
		vertices[k++] = cos(radianes) * r; aux = vertices[k - 1];
		vertices[k++] = _altura;  aux = vertices[k - 1];
		vertices[k++] = sin(radianes) * r;  aux = vertices[k - 1];
		radianes += (2*PI)/divU;
	}

	
	return k;
}