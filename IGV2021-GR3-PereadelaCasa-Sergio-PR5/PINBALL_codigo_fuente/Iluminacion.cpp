#include "Iluminacion.h"

Iluminacion::Iluminacion(igvColor color_ambiental, igvColor color_difuso, igvColor color_especular, igvPunto3D pos_foco, igvPunto3D dir_foco, unsigned int idLuz) :
	color_ambiental(color_ambiental), color_difuso(color_difuso), color_especular(color_especular), pos_foco(pos_foco), dir_foco(dir_foco),
	idLuz(idLuz),foco(idLuz,pos_foco,color_ambiental,color_difuso,color_especular, 1, 0, 0, dir_foco, 45, 0)
{
}

Iluminacion::~Iluminacion()
{
}

igvFuenteLuz& Iluminacion::getFoco()
{
	return foco;
}
