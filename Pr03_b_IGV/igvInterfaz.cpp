#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(6.0, 4.0, 8), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
		-1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3, 200);

	//par�metros de la perspectiva
	interfaz.camara.angulo = 60.0;
	interfaz.camara.raspecto = 1.0;

	//Parametro extra: apartado b.
	visualizacion = 1;
	divisiones = 0;
}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		////// Apartado C: incluir aqu� el cambio de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva 
	case 'v': // cambia la posici�n de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva
		interfaz.cambiarVista();
		break;
	case 'V': // cambia la posici�n de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva
		interfaz.cambiarVista();
		break;
	case '+': // zoom in
		interfaz.camara.zoom(0.95);
		break;
	case '-': // zoom out
		interfaz.camara.zoom(1.05);
		break;
		////// Apartado C: incluir aqu� la modificaci�n de los grados de libertad del modelo pulsando las teclas correspondientes

	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	interfaz.camara.aplicar();
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	//visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers();
}

void igvInterfaz::set_glutIdleFunc() {
	///// Apartado D: incluir el c�digo para animar el modelo de la manera m�s realista posible


}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
}

void igvInterfaz::set_visualizacion(int _visualizacion) {
	visualizacion = _visualizacion;
}

int igvInterfaz::get_visualizacion() const {
	return visualizacion;
}

void igvInterfaz::set_divisiones(int _divisiones) {
	divisiones = _divisiones;
}

int igvInterfaz::get_divisiones() const {
	return divisiones;
}

void igvInterfaz::cambiarVista() {
	switch (interfaz.get_visualizacion()) {
		case 1:
			interfaz.camara.V.set(1, 0, 0);
			interfaz.camara.P0.set(0, 5, 0);
			interfaz.set_visualizacion(2);
			break;
		case 2:
			interfaz.camara.V.set(0, 1, 0);
			interfaz.camara.P0.set(5, 0, 0);
			interfaz.set_visualizacion(3);
			break;
		case 3:
			interfaz.camara.V.set(0, 1, 0);
			interfaz.camara.P0.set(0, 0, 5);
			interfaz.set_visualizacion(4);
			break;
		case 4:
			interfaz.camara.V.set(0, 1, 0);
			interfaz.camara.P0.set(3, 2, 4);
			interfaz.set_visualizacion(1);
			break;
		default:
			break;
	}

}