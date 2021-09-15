#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <stdio.h>
#include "igvColor.h"

class Palanca
{
private:

	
	float longitud; //Tamaño en el eje x de la palanca;

	GLUquadricObj* cilindro; //Material de la palanca

	float gradosMAXrot, gradosMINrot, rotPalanca; //Grados de rotación de la palanca

	igvColor color; //Color de la palanca

	bool subiendo, bajando, llegadoLimiteMAX, llegadoLimiteMIN;

public:
	Palanca(float longitud, float gradosMax, float gradosMin,float gradosIni, igvColor color);
	~Palanca();

	

	/*MÉTODOS DE LA PALANCA DEL PINBALL*/
	void visualizar(float x, float y, float z);

	/*---- ACTIVACIÓN DE LOS MOVIMIENTOS ----*/
	bool getSubiendo_Palanca();
	void setSubiendo_Palanca(bool activacion);

	bool getBajando_Palanca();
	void setBajando_Palanca(bool activacion);

	/*---- COMPROBACIÓN DE LLEGAR O NO AL LIMITE ----*/
	float getPalancaMAXrot();
	float getPalancaMINrot();

	bool getPalancaLimitMAX();
	void setPalancaLimitMAX(bool limit);

	bool getPalancaLimitMIN();
	void setPalancaLimitMIN(bool limit);

	/*---- ROTACIONES DE LAS PALANCAS ----*/
	float getPalancaRot();
	void setPalancaRot(float grados);

	float getPalancaRotMAX();
	float getPalancaRotMIN();

	/*---- LONGITUD DE LA PALANCA ----*/
	float getLongitud();
};

