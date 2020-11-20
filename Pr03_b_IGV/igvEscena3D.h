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
	////// Apartado C: añadir quí los atributos para el control de los grados de libertad del modelo

	float cuerpo, cuello, cabeza, hombroIzq, hombroDer; //TORSO Y PARTE SUPERIOR.
	float brazoSupIzq, brazoSupDer, brazoInfIzq, brazoInfDer; //BRAZOS.
	float piernaSupDer, piernaSupIzq, piernaInfDer, piernaInfIzq; //PIERNAS.

	// Otros atributos		
	bool ejes;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	///// Apartado B: Métodos para visualizar cada parte del modelo
	void cuerpoClank();
	void barrigaClank();
	void hombroClank(float _x, float _y, float _z, double gradosRot, double gradosMov);
	void brazoClank(float _x, float _y, float _z, double gradosRot, double gradosMov);
	void piernaClank(float _x, float _y, float _z, double gradosMov);
	void manoClank(float _x, float _y, float _z, double gradosRot);
	void pieClank(float _x, float _y, float _z);

	void cuelloClank();
	void cabezaClank();
	void orejaClank(float _x,float _y, float _z);
	void ojoClank(float _x, float _y, float _z, double gradoContorno);
	void antenaClank(float _x, float _y, float _z);
	void bocaClank(float _x, float _y, float _z);

	////// Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo
	void setMovCuerpo(float n);
	void setMovCuello(float n);
	void setMovCabeza(float n);
	void setMovHombroIzq(float n);
	void setMovHombroDer(float n);
	void setMovBrazoSupDer(float n);
	void setMovBrazoSupIzq(float n);
	void setMovBrazoInfDer(float n);
	void setMovBrazoInfIzq(float n);
	void setMovPiernaSupDer(float n);
	void setMovPiernaSupIzq(float n);
	void setMovPiernaInfDer(float n);
	void setMovPiernaInfIzq(float n);




	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

};

#endif
