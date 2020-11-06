#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */

	
	num_vertices = (divU+1)*(divV+1); //Formula sacada de hacer comprobaciones
	vertices = new float[num_vertices*3];
	normales = new float[num_vertices * 3]; /*Mismo numero de normales que de vertices.*/
	float i = 0; int k = 0;
	while (i <= a) { /*MIENTRAS no se pase de la altura pasada por parametro.*/
		k = creaCircunferencia(i, r, divU, k); /*Ahora creo una circunferencia, por cada posición de altura actual.*/
		i += a / divV;
	}

	/*Instancia de los indices de arriba a abajo en sentido antihorario.*/
	
	num_triangulos = (divU*2) * divV + 2; //Formula sacada de hacer comprobaciones. El +2 es para contar la union del extremo final con el otro inicial, al final de la iteración.
	triangulos = new unsigned int [num_triangulos * 3];
	
	int cont_triangulos = 0; k = 0; /*Con la i voy a controlar el numero de triangulos añadidos.*/
	
	/*Triangulo que empieza por el vértice superior izquierdo (relativo a un rectangulo que conecta 2 triangulos).*/
	for (int j = 0; j <= (int)num_triangulos/2 - 1; j++) {
		triangulos[k++] = divU + j + 1; /*Vertice superior izquierdo*/
		triangulos[k++] = j; /*Vertice inferior izquierdo*/
		triangulos[k++] = ((divU + 1) + j + 1) % num_vertices; /*Vertice superior siguiente.*/
		triangulos[k++] = (divU + 1 + j + 1) % num_vertices; /*Vertice superior derecho*/
		triangulos[k++] = j; /*Vertice inferior izquierdo*/
		triangulos[k++] = j + 1; /*Vertice inferior siguiente.*/	
	}

}

igvCilindro::~igvCilindro()
{
}


int igvCilindro::creaCircunferencia(float _altura,float r, int divU, int k) {
	float radianes = 0; float aux;
	while (radianes < 2*PI*r) { /*Lo dejo en < estricto ya que debe de ser por igual el calculo del radian con valor 0 que con valor 2PI*R */
		vertices[k] = cos(radianes) * r; 
		normales[k++] = vertices[k] / r;
		vertices[k] = _altura; 
		normales[k++] = 0;
		vertices[k] = sin(radianes) * r;
		normales[k++] = vertices[k] / r;
		radianes += (2*PI)/divU;
	}
	vertices[k] = vertices[0];
	normales[k++] = vertices[0] / r;
	vertices[k] = _altura;
	normales[k++] = 0;
	vertices[k] = vertices[1];
	normales[k++] = vertices[1] / r;

	return k;
}