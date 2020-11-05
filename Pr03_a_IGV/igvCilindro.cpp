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
	for (float _altura = 0; _altura <= a && cont_triangulos < num_triangulos; _altura += a / divV) { /*Creación de triangulos por cada partición de altura (En esta práctica 2)*/
		for (int j = 0; j < (divU + 1) * 2 && cont_triangulos < num_triangulos; j++) {
			/*Triangulo que empieza por el vértice superior izquierdo (relativo a un rectangulo que conecta 2 triangulos).*/
			triangulos[k++] = (divU + 1) + j; /*Vertice superior izquierdo*/
			triangulos[k++] = j; /*Vertice inferior izquierdo*/
			triangulos[k++] = (divU + 1) + j + 1; /*Vertice superior siguiente.*/

			/*Triangulo que empieza por el vértice superior derecho (relativo a un rectangulo que conecta 2 triangulos).*/
			triangulos[k++] = (divU + 1) + j + 1; /*Vertice superior derecho*/
			triangulos[k++] = j; /*Vertice inferior izquierdo*/
			triangulos[k++] = j + 1; /*Vertice inferior siguiente.*/

			/*2 triangulos añadidos, entonces:*/
			cont_triangulos += 2;
		}
	}
	

	/*for (int i = num_vertices; i > 2; i = i-2) {
		triangulos[k++] = i;
		triangulos[k++] = i - 3;
		triangulos[k++] = (unsigned int)i - 1; 
	}
	for (int i = num_vertices; i > 2; i = i - 2) {
		triangulos[k++] = (unsigned int)i - 2;
		triangulos[k++] = (unsigned int)i - 3;
		triangulos[k++] = (unsigned int)i;
	}*/
	
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