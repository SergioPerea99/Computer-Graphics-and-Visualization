#pragma once
#include <cstdlib>
#include <stdio.h>
#include "igvFuenteLuz.h"
#include "igvMaterial.h"

class Iluminacion
{
private:

	/*PARAMETROS DE COLORES PARA LAS LUCES*/
	igvColor color_ambiental, color_difuso, color_especular;

	/*FOCOS*/
	igvPunto3D pos_foco;
	igvPunto3D dir_foco;
	unsigned int idLuz; // identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
	igvFuenteLuz foco;
public:
	Iluminacion(igvColor color_ambiental, igvColor color_difuso, igvColor color_especular, igvPunto3D pos_foco, igvPunto3D dir_foco, unsigned int idLuz);
	~Iluminacion();

	igvFuenteLuz& getFoco();
};

