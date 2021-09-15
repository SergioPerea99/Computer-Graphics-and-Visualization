#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include "Clank.h"
#include "Bola.h"
#include <vector>
#include "igvCilindro.h"
#include "Iluminacion.h"
#include "Palanca.h"

class igvEscena3D {
protected:
	bool ejes;
	
	/*---- POSICIÓN DE LA ILUMINACIÓN DE LA ESCENA EN EL TABLERO ----*/
	float focoX, focoY, focoZ; 

	/*---- TEXTURAS ----*/
	bool texturaCargada;
	std::vector<igvTextura*> texturas;

	/*---- CARACTERISTICAS DEL TABLERO ----*/
	float anchura, profundidad, altura;

	/*---- PALANCAS ----*/
	Palanca palIzq, palDer;

	/*---- BOLA -----*/
	Bola bola;

	/*---- CLANK Y SUS OBJETOS CORRESPONDIENTES (PARA SU ANIMACIÓN) ----*/
	Clank clank;
	igvCilindro plataformaClank;
	igvCilindro rueda;
	float rotClank;
	float posPlatX, posPlatY, posPlatZ; /*Posicion de plataforma de Clank*/
	
public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// método con las llamadas OpenGL para visualizar la escena
	void visualizar();

	/*---- ESCENARIO ----*/
	void pintar_suelo_techo(float tam_x,float  tam_y,float tam_z);
	void pintar_paredes(float tam_x, float  tam_y, float tam_z);
	void pintar_tablero(float tam_x, float tam_z);
	void pintarPatas_tablero();
	void accesoriosEscenario();
	void bordesEscenario(float tamX, float tamZ);
	void creaIluminacion(float tamX, float tamZ);
	
	/*TRIÁNGULOS NECESARIOS PARA GANAR DIRECCIONES DE LA BOLA*/
	void trianguloInfDer(float anchura, float longitud);
	void trianguloInfIzq(float anchura, float longitud);
		
	/*PALANCAS*/
	Palanca& getPalIzq();
	Palanca& getPalDer();

	/*ANIMACIÓN DE MOVIMIENTO DE LA BOLA*/
	float getAnchura();
	float getLongitud();
	Bola& getBola();


	/*ANIMACIÓN DE CLANK*/
	igvCilindro& getPlataformaClank();
	Clank& getClank();
	igvCilindro& getRueda();
	float getRotClank();
	void setRotClank(float rot);
	float getPlat_posX();
	void setPlat_posX(float x);
	float getPlat_posZ();
	void setPlat_posZ(float z);





	/*---- GETTERS Y SETTERS ----*/
	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

	void set_difusoMaterialR(float difuso);
	void set_especularMaterialR(float especular);
	void set_phongMaterial(int phong);
	float get_difusoMaterialR() const;
	float get_especularMaterialR() const;
	int get_phongMaterial() const;

	void set_focoX(float x);
	void set_focoY(float y);
	void set_focoZ(float z);

	float get_focoX() const;
	float get_focoY() const;
	float get_focoZ() const;

};
#endif
