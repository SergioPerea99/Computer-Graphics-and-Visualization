#include "Palanca.h"

Palanca::Palanca(float longitud, float gradosMax, float gradosMin, float gradosIni, igvColor color):
	longitud(longitud), gradosMAXrot(gradosMax), gradosMINrot(gradosMin), rotPalanca(gradosIni), cilindro(gluNewQuadric()), color(color)
{
	subiendo = bajando = false;
	llegadoLimiteMAX = false; 
	llegadoLimiteMIN = true; //PARTE DEL LIMITE MINIMO DE ROTACION QUE PUEDE ESTAR LA PALANCA.
}

Palanca::~Palanca()
{
	cilindro = nullptr;
}

void Palanca::visualizar(float x, float y, float z)
{
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, color.cloneToFloatArray());
		glTranslatef(x, y, z);
		glRotatef(rotPalanca, 0, 1, 0);
		gluCylinder(cilindro, 0.1, 0.05, longitud, 20, 20);
	glPopMatrix();
}

bool Palanca::getSubiendo_Palanca()
{
	return subiendo;
}

void Palanca::setSubiendo_Palanca(bool activacion)
{
	subiendo = activacion;
}

bool Palanca::getBajando_Palanca()
{
	return bajando;
}

void Palanca::setBajando_Palanca(bool activacion)
{
	bajando = activacion;
}

float Palanca::getPalancaMAXrot()
{
	return gradosMAXrot;
}

float Palanca::getPalancaMINrot()
{
	return gradosMINrot;
}

bool Palanca::getPalancaLimitMAX()
{
	return llegadoLimiteMAX;
}

void Palanca::setPalancaLimitMAX(bool limit)
{
	llegadoLimiteMAX = limit;
}

bool Palanca::getPalancaLimitMIN()
{
	return llegadoLimiteMIN;
}

void Palanca::setPalancaLimitMIN(bool limit)
{
	llegadoLimiteMIN = limit;
}

float Palanca::getPalancaRot()
{
	return rotPalanca;
}

void Palanca::setPalancaRot(float grados)
{
	rotPalanca = grados;
}

float Palanca::getPalancaRotMAX()
{
	return gradosMAXrot;
}

float Palanca::getPalancaRotMIN()
{
	return gradosMINrot;
}

float Palanca::getLongitud()
{
	return longitud;
}
