#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

class igvEscena3D {
    public:
        const int EscenaA = 1;
		const int EscenaB = 2;
		const int EscenaC = 3;

		const char *Nombre_EscenaA = "Escena A";
		const char *Nombre_EscenaB = "Escena B";
		const char* Nombre_EscenaC = "Escena C";

	protected:
		// Atributos
		bool ejes;
        // Declarar variables para manejar las transformaciones para la escena B

		//Necesito crear estos atributos para poder realizar el final de la práctica: ejercicio C.
		unsigned int tamX = 0;
		unsigned int tamY = 0;
		unsigned int tamZ = 0;

	public:
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
        void visualizar(int escena);

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};

		int get_tamX() { return tamX; };
		void incrementar_tamX(int _tamX) { tamX += _tamX; };
		void decrementar_tamX(int _tamX) { tamX -= _tamX; };

		int get_tamY() { return tamY; };
		void incrementar_tamY(int _tamY) { tamY += _tamY; };
		void decrementar_tamY(int _tamY) { tamY -= _tamY; };

		int get_tamZ() { return tamZ; };
		void incrementar_tamZ(int _tamZ) { tamZ += _tamZ; };
		void decrementar_tamZ(int _tamZ) { tamZ -= _tamZ; };

    protected:
        void renderEscenaA();
        void renderEscenaB();
		void renderEscenaC();

		void creaCajaZapatos();

};

#endif
