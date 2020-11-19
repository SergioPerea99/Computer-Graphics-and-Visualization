#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


enum {
	basex,
	cuerpoinferior,
	cuerposuperior,
	brazo
};

class igvEscena3D {
protected:

	//ATRIBUTOS para cambiar el grado de rotaci�n correspondiente.
	float cuerpo, cuello, cabeza, hombroIzq, hombroDer,antena;

	////// Apartado C: a�adir qu� los atributos para el control de los grados de libertad del modelo

	// Otros atributos		
	bool ejes;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// m�todo con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	///// Apartado B: M�todos para visualizar cada parte del modelo
	void cuerpoClank();
	void barrigaClank();
	void cuelloClank();
	void cabezaClank();
	void orejaClank(float _x,float _y, float _z);
	void ojoClank(float _x, float _y, float _z);
	void antenaClank(float _x, float _y, float _z);
	void bocaClank(float _x, float _y, float _z);

	////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo


	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

};

#endif
