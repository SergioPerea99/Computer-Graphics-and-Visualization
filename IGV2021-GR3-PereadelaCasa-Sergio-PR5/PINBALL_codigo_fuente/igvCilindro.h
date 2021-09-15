
#include "igvMallaTriangulos.h"
constexpr auto PI = 3.141592;
class igvCilindro : public igvMallaTriangulos {


public:

	//// Constructores por y destructor
	igvCilindro();
	igvCilindro(float r, float a, int divU, int divV);
	~igvCilindro();
	float getRadio();
private:
	float radio;
	int creaCircunferencia(float _altura, float r, int divU, int k);

};