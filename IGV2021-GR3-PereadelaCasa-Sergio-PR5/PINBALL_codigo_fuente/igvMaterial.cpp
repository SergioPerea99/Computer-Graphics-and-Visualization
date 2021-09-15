#include "igvMaterial.h"

// Metodos constructores 


igvMaterial::igvMaterial() {

}

igvMaterial::~igvMaterial() {

}

igvMaterial::igvMaterial(const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {

	// APARTADO C
	// Aplicar los valores de los atributos del objeto igvMaterial:
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());// - coeficiente de reflexi�n de la luz ambiental
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());// - coeficiente de reflexi�n difuso
	glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());// - coeficiente de reflesi�n especular
	glMaterialf(GL_FRONT, GL_SHININESS, Ns);// - exponente de Phong

	igvColor color_emision = igvColor(0, 0, 0);
	glMaterialfv(GL_FRONT, GL_EMISSION, color_emision.cloneToFloatArray());// establecer como color de emisi�n (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)


}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



