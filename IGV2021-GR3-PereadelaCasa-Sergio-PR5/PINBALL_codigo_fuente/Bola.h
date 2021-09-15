#pragma once
#include <cstdlib>
#include <stdio.h>
#include "igvMaterial.h"

class Bola
{
private:
	float posX, posY, posZ; /*POSICIONAMIENTO DE LA BOLA*/

	unsigned int dirX, dirZ; /*INDICACIÓN DE HACIA DONDE DEBE IR*/

	igvColor color; /*COLOR DE LA BOLA*/

	bool animacion; /*ACTIVACIÓN DE ANIMACIÓN PARA JUGAR*/

	float velocidad, aceleracion; /*ATRIBUTOS PARA AÑADIR REALISMO DE MOVIMIENTO*/

public:

	Bola();
	~Bola();

	void visualizar(float x, float y, float z);

	void cambioVelocidadPalancas(float anguloPalanca, float anguloMAX, float t);
	void cambioVelocidad(float anguloPalanca, float anguloMAX, float t);

	/*---- GETTERS Y SETTERS ----*/
	float getPosX() const;
	void setPosX(float x);
	float getPosY() const;
	void setPosY(float y);
	float getPosZ() const;
	void setPosZ(float z);

	bool get_animacion();
	void set_animacion(bool _animacion);

	float getVelocidad();
	void setVelocidad(float v);

	float getAceleracion();


};

