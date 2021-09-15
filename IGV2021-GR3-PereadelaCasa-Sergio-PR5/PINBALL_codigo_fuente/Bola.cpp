#include "Bola.h"

Bola::Bola()
{
	posX = -4.5;
	posY = 0.0;
	posZ = 0.0;

	color = igvColor{ 0.90, 0.91, 0.98 };
	animacion = false;

	velocidad = 0.0; //Velocidad -> Cambiante respecto al eje en el que se vaya moviendo debido a la aceleración (estática)
	aceleracion = 9.8; //Aceleración = gravedad

}

Bola::~Bola()
{
}

void Bola::visualizar(float x, float y, float z)
{
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, color.cloneToFloatArray());
		glTranslatef(posX, posY, posZ);
		glutWireSphere(0.15, 30, 30);
	glPopMatrix();
}



float Bola::getPosX() const
{
	return posX;
}

void Bola::setPosX(float x)
{
	posX = x;
}

float Bola::getPosY() const
{
	return posY;
}

void Bola::setPosY(float y)
{
	posY = y;
}

float Bola::getPosZ() const
{
	return posZ;
}

void Bola::setPosZ(float z)
{
	posZ = z;
}

bool Bola::get_animacion()
{
	return animacion;
}

void Bola::set_animacion(bool _animacion)
{
	animacion = _animacion;
}

float Bola::getVelocidad()
{
	return velocidad;
}

void Bola::setVelocidad(float v)
{
	velocidad = v;
}

float Bola::getAceleracion()
{
	return aceleracion;
}

void Bola::cambioVelocidadPalancas(float anguloPalanca, float anguloMAX, float t)
{
		velocidad = (anguloPalanca / (-anguloMAX / 3)) * aceleracion;
}

void Bola::cambioVelocidad(float anguloPalanca, float anguloMAX, float t)
{
	velocidad = (anguloPalanca / (-anguloMAX / 2)) * aceleracion;
}


