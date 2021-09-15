#pragma once
#include <cstdlib>
#include <stdio.h>
#include "igvMaterial.h"
#include "igvTextura.h"


class Clank
{
private:
	/*---- ATRIBUTOS PARA EL MUÑECO CLANK ----*/
	float cuerpo, cuello, cabeza, hombroIzq, hombroDer; //TORSO Y PARTE SUPERIOR.
	float brazoSupIzq, brazoSupDer, brazoInfIzq, brazoInfDer; //BRAZOS.
	float piernaSupDer, piernaSupIzq, piernaInfDer, piernaInfIzq; //PIERNAS.	
	bool animacion;
	bool limitIntervalo;
	float actualValor;

	/*---- MÉTODOS PARA EL MUÑECO CLANK ----*/
public:
	Clank();
	~Clank();

	void visualizar(float x, float y, float z);


	void cuerpoClank();
	void barrigaClank();
	void hombroClank(float _x, float _y, float _z, double gradosRot, double gradosMov);
	void brazoClank(float _x, float _y, float _z, double gradosRot, double gradosMov);
	void piernaClank(float _x, float _y, float _z, double gradosMov);
	void manoClank(float _x, float _y, float _z, double gradosRot);
	void pieClank(float _x, float _y, float _z);
	void cuelloClank();
	void cabezaClank();
	void orejaClank(float _x, float _y, float _z);
	void ojoClank(float _x, float _y, float _z, double gradoContorno);
	void antenaClank(float _x, float _y, float _z);
	void bocaClank(float _x, float _y, float _z);


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

	//ANIMACIONES Y LIMITACIONES
	bool get_animacion();
	void set_animacion(bool _animacion);
	bool get_limitIntervalo();
	void set_limitIntervalo(bool _cambia);
	float get_actualValor();
	void set_actualValor(float _nuevo);

};

