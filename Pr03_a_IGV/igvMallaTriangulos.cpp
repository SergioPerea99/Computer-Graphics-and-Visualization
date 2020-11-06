#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "igvMallaTriangulos.h"

igvMallaTriangulos::igvMallaTriangulos() :num_vertices(0), vertices(nullptr), num_triangulos(0), triangulos(nullptr),normales(nullptr)
{
}

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float* _vertices, long int _num_triangulos, unsigned int* _triangulos) {

	num_vertices = _num_vertices;
	vertices = new float[num_vertices * 3];
	for (long int i = 0; i < (num_vertices * 3); ++i) {
		vertices[i] = _vertices[i];
	}

	normales = nullptr;

	num_triangulos = _num_triangulos;
	triangulos = new unsigned int[num_triangulos * 3];
	for (long int i = 0; i < (num_triangulos * 3); ++i) {
		triangulos[i] = _triangulos[i];
	}


}

igvMallaTriangulos::~igvMallaTriangulos() {
	if (vertices)
		delete []vertices;
	if (normales)
		delete []normales;
	if (triangulos)
		delete []triangulos;
}


void igvMallaTriangulos::visualizar(std::string _visualizacion) {

	if (_visualizacion== "GL_FLAT")
		glShadeModel(GL_FLAT);
	else if (_visualizacion == "GL_SMOOTH")
		glShadeModel(GL_SMOOTH);

	/* Apartado B: TODO */

	glEnableClientState(GL_VERTEX_ARRAY); /*Activar la utilización de arrays de vértices.*/
	glEnableClientState(GL_NORMAL_ARRAY); /*Activar la utilización de arrays de normales.*/
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normales);
	glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
