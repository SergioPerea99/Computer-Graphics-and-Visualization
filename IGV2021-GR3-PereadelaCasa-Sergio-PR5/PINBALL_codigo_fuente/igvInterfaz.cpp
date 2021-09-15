#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"
#include <iostream>


extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {

	interfaz.camara.set(IGV_PERSPECTIVA, igvPunto3D(0,6.0,20),igvPunto3D(0,0,0),igvPunto3D(0,1.0,0),
		-1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 100);

	//parámetros de la perspectiva
	interfaz.camara.angulo = 60.0;
	interfaz.camara.raspecto = 1.0;


	visualizacion = 1;
	tiempo = 0.0;
	dirX = 0;
	tocaTecho = tocaPlataformaClank_baja = tocaPlataformaClank_alta = false;
	modificado = modificadoPalIzq = modificadoPalDer = false;
	bolaChocadaMovX = 0.0;

	interfaz.escena.getBola().setPosX((rand() % ((int)interfaz.escena.getAnchura() * 2 - 1)) - 4.5);
	interfaz.escena.getBola().setPosZ(-interfaz.escena.getLongitud() + 1);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_ancho_ventana,_alto_ventana);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());
	
	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer

	glClearColor(0,0,0,1); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	glEnable(GL_TEXTURE_2D); // activa el uso de texturas
	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutSpecialFunc(int key, int x, int y) {
	
	switch (key) {
	case GLUT_KEY_DOWN:
		interfaz.camara.set(igvPunto3D(interfaz.camara.P0.c[0], interfaz.camara.P0.c[1], interfaz.camara.P0.c[2]+0.1), interfaz.camara.r,interfaz.camara.V);
		break;
	case GLUT_KEY_UP:
		interfaz.camara.set(igvPunto3D(interfaz.camara.P0.c[0], interfaz.camara.P0.c[1], interfaz.camara.P0.c[2] - 0.1), interfaz.camara.r, interfaz.camara.V);
		break;
	case GLUT_KEY_LEFT:
		interfaz.camara.set(igvPunto3D(interfaz.camara.P0.c[0] - 0.1, interfaz.camara.P0.c[1] , interfaz.camara.P0.c[2]), interfaz.camara.r, interfaz.camara.V);
		break;
	case GLUT_KEY_RIGHT:
		interfaz.camara.set(igvPunto3D(interfaz.camara.P0.c[0] + 0.1, interfaz.camara.P0.c[1], interfaz.camara.P0.c[2]), interfaz.camara.r, interfaz.camara.V);
		break;
	}

	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'V': // cambia la posición de la cámara 
	case 'v': // cambia la posición de la cámara 
		interfaz.cambiarVista();
		break;
	case 'A': /*ACTIVAR/DESACTIVAR ANIMACION DE CLANK*/
	case 'a': /*ACTIVAR/DESACTIVAR ANIMACION DE CLANK*/
		interfaz.escena.getClank().get_animacion() ? interfaz.escena.getClank().set_animacion(false) : interfaz.escena.getClank().set_animacion(true);
		break;
	case 'B':  /*ACTIVAR/DESACTIVAR ANIMACION DE LA BOLA*/
	case 'b': /*ACTIVAR/DESACTIVAR ANIMACION DE LA BOLA*/ 
		interfaz.escena.getBola().get_animacion() ?  interfaz.escena.getBola().set_animacion(false) : interfaz.escena.getBola().set_animacion(true);
		break;
	case 'Q': /*ACTIVACIÓN DE MOVIMIENTO DE LA PALANCA DE LA IZQUIERDA*/
	case 'q': /*ACTIVACIÓN DE MOVIMIENTO DE LA PALANCA DE LA IZQUIERDA*/
		if(!interfaz.escena.getPalIzq().getSubiendo_Palanca()) interfaz.escena.getPalIzq().setSubiendo_Palanca(true);
		break;
	case 'W': /*ACTIVACIÓN DE MOVIMIENTO DE LA PALANCA DE LA DERECHA*/
	case 'w': /*ACTIVACIÓN DE MOVIMIENTO DE LA PALANCA DE LA DERECHA*/
		if (!interfaz.escena.getPalDer().getSubiendo_Palanca()) interfaz.escena.getPalDer().setSubiendo_Palanca(true);
		break;
	case '+': // zoom in
		interfaz.camara.zoom(0.95);
		break;
	case '-': // zoom out
		interfaz.camara.zoom(1.05);
		break;
	case 'P': // cambia el tipo de proyección de paralela a perspectiva y viceversa
	case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		interfaz.camara.tipo == IGV_PARALELA ? interfaz.camara.tipo = IGV_PERSPECTIVA : interfaz.camara.tipo = IGV_PARALELA;
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	//interfaz.camara.aplicar();
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();

	//visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutSpecialFunc(set_glutSpecialFunc);
	glutIdleFunc(set_glutIdleFunc);
}

void igvInterfaz::cambiarVista() {
	switch (interfaz.get_visualizacion()) {
	case 1:
		interfaz.camara.V.set(0, 1, 0);
		interfaz.camara.P0.set(10, 4, interfaz.escena.getLongitud() * 2);
		interfaz.set_visualizacion(2);
		break;
	case 2:
		interfaz.camara.V.set(0, 1, 0);
		interfaz.camara.P0.set(-10, 4, interfaz.escena.getLongitud() * 2);
		interfaz.set_visualizacion(3);
		break;
	case 3:
		interfaz.camara.V.set(0, 1, 0);
		interfaz.camara.P0.set(-10, 4, -interfaz.escena.getLongitud() - 2);
		interfaz.set_visualizacion(4);
		break;
	case 4:
		interfaz.camara.V.set(0, 1, 0);
		interfaz.camara.P0.set(10, 4, -interfaz.escena.getLongitud() - 2);
		interfaz.set_visualizacion(5);
		break;
	case 5:
		interfaz.camara.V.set(0, 1, 0);
		interfaz.camara.P0.set(0, 6.0, 20);
		interfaz.set_visualizacion(1);
		break;
	default:
		break;
	}

}


void igvInterfaz::set_glutIdleFunc() {

	/*ANIMACIÓN CLANK*/
	if (interfaz.escena.getClank().get_animacion()) interfaz.animacionClank();
	
	/*ANIMACIÓN DE LAS PALANCAS*/
	if ( interfaz.escena.getPalIzq().getSubiendo_Palanca() ) interfaz.subirPalancaIzq();
	if ( interfaz.escena.getPalDer().getSubiendo_Palanca() ) interfaz.subirPalancaDer();

	/*ANIMACIÓN BOLA*/
	if (interfaz.escena.getBola().get_animacion()) interfaz.animacionBola(); 
	
	glutPostRedisplay(); //PARA REFRESCAR LA ESCENA Y QUE SALGA LA ANIMACIÓN CON SU NUEVOS PARAMETROS CAMBIADOS.
}

int igvInterfaz::get_visualizacion() const {
	return visualizacion;
}

void igvInterfaz::set_visualizacion(int _visualizacion) {
	visualizacion = _visualizacion;
}


void igvInterfaz::animacionBola() {
	

	/*LA BOLA SE ENCUENTRA EN POSICIÓN DE DARLE CON LAS PALANCAS*/
	if (interfaz.escena.getBola().getPosZ() <= (interfaz.escena.getLongitud() - 1) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() - 2)) { /*Si la bola se encuentra en posición de ser dada por las palancas...*/
		modificado = modificadoPalDer = modificadoPalIzq = false;
		
		/*JUSTAMENTE CENTRO*/
		if (interfaz.escena.getBola().getPosX() >= -0.05 && interfaz.escena.getBola().getPosX() <= 0.05) {
			if (interfaz.escena.getPalIzq().getSubiendo_Palanca() && interfaz.escena.getPalDer().getSubiendo_Palanca()) { /*Si la palanca además se encuentra subiendo...*/
				interfaz.escena.getBola().cambioVelocidadPalancas(interfaz.escena.getPalIzq().getPalancaRot(), interfaz.escena.getPalIzq().getPalancaRotMAX(), interfaz.tiempo); //Se cambia la dirección de la bola mediante el angulo que tenga en ese momento la palanca
				modificado = true;
			}
		}
		/*PARTE DE LA DERECHA DEL TABLERO*/
		if (interfaz.escena.getBola().getPosX() >= 0.0 && interfaz.escena.getBola().getPosX() < interfaz.escena.getPalDer().getLongitud() && !modificado) { 
			if (interfaz.escena.getPalDer().getSubiendo_Palanca()) { /*Si la palanca además se encuentra subiendo...*/
				interfaz.escena.getBola().cambioVelocidadPalancas(interfaz.escena.getPalDer().getPalancaRot(), interfaz.escena.getPalDer().getPalancaRotMAX(), interfaz.tiempo); //Se cambia la dirección de la bola mediante el angulo que tenga en ese momento la palanca
				modificadoPalDer = true;
				interfaz.dirX = -1;
			}
		}
		/*PARTE DE LA IZQUIERDA DEL TABLERO*/
		if (interfaz.escena.getBola().getPosX() <= 0.0 && interfaz.escena.getBola().getPosX() > -interfaz.escena.getPalIzq().getLongitud() && !modificado) {
			if (interfaz.escena.getPalIzq().getSubiendo_Palanca()) { /*Si la palanca además se encuentra subiendo...*/
				interfaz.escena.getBola().cambioVelocidad(interfaz.escena.getPalIzq().getPalancaRot(), interfaz.escena.getPalIzq().getPalancaRotMAX(), interfaz.tiempo); //Se cambia la dirección de la bola mediante el angulo que tenga en ese momento la palanca
				modificadoPalIzq = true;
				interfaz.dirX = 1;
			}
		}
	}

	/*CHOCAR CON LA PARED DE LA IZQUIERDA*/
	if (interfaz.escena.getBola().getPosX() <= -interfaz.escena.getAnchura() + 0.2) {
		interfaz.dirX = 1;
		interfaz.bolaChocadaMovX = 0.1;
	}

	/*CHOCAR CON LA PARED DE LA DERECHA*/
	if (interfaz.escena.getBola().getPosX() >= interfaz.escena.getAnchura()- 0.2) {
		interfaz.dirX = -1;
		interfaz.bolaChocadaMovX = -0.1;
	}

	/*CHOCAR CON EL "TECHO"*/
	if (interfaz.escena.getBola().getPosZ() <= -interfaz.escena.getLongitud() + 1 && !tocaTecho) {
		interfaz.escena.getBola().setVelocidad(-interfaz.escena.getBola().getVelocidad()/2);
		interfaz.tiempo = interfaz.tiempo / 2;
		tocaTecho = true;
	}
	else if (interfaz.escena.getBola().getPosZ() > -interfaz.escena.getLongitud() + 1.01 && interfaz.escena.getBola().getPosZ() < -interfaz.escena.getLongitud() + 1.2) {
		tocaTecho = false;
	}
	
	
	/*CHOCAR CON EL MURO INFERIOR DERECHO:
	* Para intervalo [anchura-1,anchura]
	* Para intervalo [anchura-2,anchura-1]
	* Para intervalor [anchura-3,longitud Palanca derecha]
	*/
	if (interfaz.escena.getBola().getPosX() > (interfaz.escena.getAnchura() - 1)  && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3 )) {
		interfaz.escena.getBola().cambioVelocidad(27, 45, interfaz.tiempo);
		if (interfaz.dirX != -1) interfaz.dirX = -1;
	}
	else if (interfaz.escena.getBola().getPosX() > (interfaz.escena.getAnchura() - 2) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3 + 0.5)) {
		interfaz.escena.getBola().cambioVelocidad(25, 45, interfaz.tiempo);
		if (interfaz.dirX != -1) interfaz.dirX = -1;
	}
	else if (interfaz.escena.getBola().getPosX() > (interfaz.escena.getAnchura() - 3) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3 + 1)) {
		interfaz.escena.getBola().cambioVelocidad(20, 45, interfaz.tiempo);
		if (interfaz.dirX != -1) interfaz.dirX = -1;
	}
	
	/*CHOCAR CON EL MURO INFERIOR IZQUIERDO:
	* Para intervalo [-anchura,-anchura+1]
	* Para intervalo [-anchura+1,-anchura+2]
	* Para intervalor [-anchura+2,-anchura+3]
	*/
	if (interfaz.escena.getBola().getPosX() < (-interfaz.escena.getAnchura() + 1) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3)) {
		interfaz.escena.getBola().cambioVelocidad(27, 45, interfaz.tiempo);
		if (interfaz.dirX != 1) interfaz.dirX = 1;
	}
	else if (interfaz.escena.getBola().getPosX() < (-interfaz.escena.getAnchura() + 2) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3 + 0.5)) {
		interfaz.escena.getBola().cambioVelocidad(25, 45, interfaz.tiempo);
		if (interfaz.dirX != 1) interfaz.dirX = 1;
	}
	else if (interfaz.escena.getBola().getPosX() < (-interfaz.escena.getAnchura() + 3) && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getLongitud() / 3 + 1)) {
		interfaz.escena.getBola().cambioVelocidad(20, 45, interfaz.tiempo);
		if (interfaz.dirX != 1) interfaz.dirX = 1;
	}




	/*CHOCAR CON OBJETO ANIMACIÓN CLANK:
	* Por la izquierda abajo
	* Por la izquierda en medio
	* Por la izquierda arriba
	* Por la derecha abajo
	* Por la derecha en medio
	* Por la derecha arriba
	*/
	/*PARTE IZQUIERDA ABAJO*/
	if (interfaz.escena.getBola().getPosX() < interfaz.escena.getPlat_posX() 
		&& interfaz.escena.getBola().getPosX() > interfaz.escena.getPlat_posX() - interfaz.escena.getPlataformaClank().getRadio() 
		&& interfaz.escena.getBola().getPosZ() > interfaz.escena.getPlat_posZ() 
		&& interfaz.escena.getBola().getPosZ() < (interfaz.escena.getPlat_posZ() + interfaz.escena.getPlataformaClank().getRadio() + 0.1) && !tocaPlataformaClank_baja) {
		interfaz.escena.getBola().setVelocidad(-interfaz.escena.getBola().getVelocidad()/2);
		interfaz.tiempo = interfaz.tiempo / 2;
		interfaz.dirX = -1;
		interfaz.bolaChocadaMovX = interfaz.dirX * 0.1;
		tocaPlataformaClank_baja = true;
	}
	/*PARTE DERECHA ABAJO*/
	else if (interfaz.escena.getBola().getPosX() >= interfaz.escena.getPlat_posX() 
		&& interfaz.escena.getBola().getPosX() < interfaz.escena.getPlat_posX() + interfaz.escena.getPlataformaClank().getRadio() 
		&& interfaz.escena.getBola().getPosZ() > interfaz.escena.getPlat_posZ() 
		&& interfaz.escena.getBola().getPosZ() < (interfaz.escena.getPlat_posZ() + interfaz.escena.getPlataformaClank().getRadio() + 0.1) && !tocaPlataformaClank_baja) {
		interfaz.escena.getBola().setVelocidad(-interfaz.escena.getBola().getVelocidad() / 2);
		interfaz.tiempo = interfaz.tiempo / 2;
		interfaz.dirX = 1;
		interfaz.bolaChocadaMovX = interfaz.dirX * 0.1;
		tocaPlataformaClank_baja = true;
	}
	/*REESTABLECER EL CHOQUE EN LA PARTE DE ABAJO*/
	else if (interfaz.escena.getBola().getPosZ() > (interfaz.escena.getPlat_posZ() + interfaz.escena.getPlataformaClank().getRadio() + 0.101))
		tocaPlataformaClank_baja = false;
	
	
	
	/*PARTE IZQUIERDA ARRIBA*/
	if (interfaz.escena.getBola().getPosX() < interfaz.escena.getPlat_posX() && interfaz.escena.getBola().getPosX() > interfaz.escena.getPlat_posX() - interfaz.escena.getPlataformaClank().getRadio() && interfaz.escena.getBola().getPosZ() < interfaz.escena.getPlat_posZ() && interfaz.escena.getBola().getPosZ() >= (interfaz.escena.getPlat_posZ() - interfaz.escena.getPlataformaClank().getRadio() + 0.1) && !tocaPlataformaClank_alta) {
		interfaz.escena.getBola().setVelocidad(-interfaz.escena.getBola().getVelocidad() / 2);
		interfaz.tiempo = interfaz.tiempo / 2;
		interfaz.dirX = -1;
		interfaz.bolaChocadaMovX = interfaz.dirX * 0.1;
		tocaPlataformaClank_alta = true;
	}
	/*PARTE DERECHA ARRIBA*/
	else if (interfaz.escena.getBola().getPosX() >= interfaz.escena.getPlat_posX() && interfaz.escena.getBola().getPosX() < (interfaz.escena.getPlat_posX() + interfaz.escena.getPlataformaClank().getRadio()) && interfaz.escena.getBola().getPosZ() < interfaz.escena.getPlat_posZ() && interfaz.escena.getBola().getPosZ() > (interfaz.escena.getPlat_posZ() - interfaz.escena.getPlataformaClank().getRadio() + 0.1) && !tocaPlataformaClank_alta) {
		interfaz.escena.getBola().setVelocidad(-interfaz.escena.getBola().getVelocidad() / 2);
		interfaz.tiempo = interfaz.tiempo / 2;
		interfaz.dirX = 1;
		interfaz.bolaChocadaMovX = interfaz.dirX * 0.1;
		tocaPlataformaClank_alta = true;
	}
	/*REESTABLECER EL CHOQUE EN LA PARTE DE ARRIBA*/
	else if (interfaz.escena.getBola().getPosZ() > interfaz.escena.getPlat_posZ() || interfaz.escena.getBola().getPosZ() < (interfaz.escena.getPlat_posZ() - interfaz.escena.getPlataformaClank().getRadio() ))
		tocaPlataformaClank_alta = false;
	





	/*CAÍDA EN EJES X,Z -> SIMULACIÓN DE GRAVEDAD E INCREMENTO DE SU VELOCIDAD HACIA ABAJO*/
	if (interfaz.escena.getBola().getPosZ() < interfaz.escena.getLongitud()) {
		/*ACTUALIZACIÓN DE LA POSICIÓN Z*/
		interfaz.escena.getBola().setPosZ(interfaz.escena.getBola().getPosZ() + interfaz.escena.getBola().getVelocidad()*interfaz.tiempo + (interfaz.escena.getBola().getAceleracion()*pow(interfaz.tiempo,2)/2));
		
		/*ACTUALIZACIÓN DE LA POSICIÓN X
		*Aparentemente mejor quitar la velocidad -> es variable respecto al tiempo entonces provoca movimiento extraño*/
		interfaz.escena.getBola().setPosX((interfaz.escena.getBola().getPosX() + interfaz.dirX * ( interfaz.escena.getBola().getAceleracion() * pow(interfaz.tiempo, 2) / 2) + interfaz.bolaChocadaMovX ));
		
		
		if (interfaz.escena.getBola().getVelocidad() < 0 && (modificadoPalDer || modificadoPalIzq || modificado)) {
			interfaz.tiempo = 0.03; //Reseteo el tiempo cuando pierde la velocidad solo si ha sido pulsada una de las palancas o las 2.
			modificadoPalDer = false;
			modificadoPalIzq = false;
			modificado = false;
		}

		/*ACTUALIZACIÓN DE LA VELOCIDAD*/
		interfaz.escena.getBola().setVelocidad(interfaz.escena.getBola().getVelocidad() + interfaz.escena.getBola().getAceleracion() * interfaz.tiempo);
		
		/*INCREMENTO DEL "TIEMPO" PARA AUMENTAR POR CADA ANIMACIÓN LA VELOCIDAD CON LA QUE DESCIENDE*/
		interfaz.tiempo += 0.0003;
	}

	/*FIN DEL JUEGO*/
	else if (interfaz.escena.getBola().getPosZ() >= interfaz.escena.getLongitud()) {
		std::cout << "HAS PERDIDO :: REINICIANDO PARTIDA " << std::endl;
		interfaz.tiempo = 0.0;
		interfaz.bolaChocadaMovX = 0.0;
		interfaz.escena.getBola().setVelocidad(0.0);
		interfaz.dirX = 0;
		interfaz.escena.getBola().setPosX((rand()% ((int)interfaz.escena.getAnchura()*2 -1) ) - 4.5);
		interfaz.escena.getBola().setPosZ(-interfaz.escena.getLongitud() + 1);
		tocaTecho = tocaPlataformaClank_baja = tocaPlataformaClank_alta = false;
	}

}

void igvInterfaz::animacionClank() {
		
		/*ANIMACIÓN DE ANDAR DE CLANK*/
		if (interfaz.escena.getClank().get_limitIntervalo()) {
			interfaz.escena.getClank().set_actualValor(interfaz.escena.getClank().get_actualValor() + 20);

			interfaz.escena.getClank().setMovBrazoSupDer(3);
			interfaz.escena.getClank().setMovBrazoSupIzq(3);
			interfaz.escena.getClank().setMovBrazoInfDer(1.5);
			interfaz.escena.getClank().setMovBrazoInfIzq(1.5);

			interfaz.escena.getClank().setMovCuello(0.04);

			interfaz.escena.getClank().setMovPiernaSupDer(3);
			interfaz.escena.getClank().setMovPiernaSupIzq(-3);
			interfaz.escena.getClank().setMovPiernaInfDer(1.5);
			interfaz.escena.getClank().setMovPiernaInfIzq(-1.5);

		}
		else {
			interfaz.escena.getClank().set_actualValor(interfaz.escena.getClank().get_actualValor() - 20);
			interfaz.escena.getClank().setMovBrazoSupDer(-3);
			interfaz.escena.getClank().setMovBrazoSupIzq(-3);
			interfaz.escena.getClank().setMovBrazoInfDer(-1.5);
			interfaz.escena.getClank().setMovBrazoInfIzq(-1.5);

			interfaz.escena.getClank().setMovCuello(-0.04);

			interfaz.escena.getClank().setMovPiernaSupDer(-3);
			interfaz.escena.getClank().setMovPiernaSupIzq(3);
			interfaz.escena.getClank().setMovPiernaInfDer(-1.5);
			interfaz.escena.getClank().setMovPiernaInfIzq(1.5);
		}
		if (interfaz.escena.getClank().get_actualValor() >= 500)
			interfaz.escena.getClank().set_limitIntervalo(false);
		else if (interfaz.escena.getClank().get_actualValor() <= -200)
			interfaz.escena.getClank().set_limitIntervalo(true);

		/*ANIMACIÓN MOVIMIENTO DE LA "RUEDA"*/
		interfaz.escena.getRueda().setGradRotY(interfaz.escena.getRueda().getGradRotY() - 1);



	}

void igvInterfaz::subirPalancaIzq()
{
	//TODO: MODULAR EN UNA CLASE LAS PALANCAS Y AÑADIR LIMITACIONES DE SUBIDAS Y BAJADAS EN EL EJE X CON ROTACIONES
	if (!interfaz.escena.getPalIzq().getPalancaLimitMAX()) { //SI NO HA LLEGADO AL LIMITE MAXIMO DE SUBIR LA PALANCA (SE TRUNCA UNA VEZ VUELVE A BAJAR POR COMPLETO)
		interfaz.escena.getPalIzq().setPalancaLimitMIN(false);
		if (interfaz.escena.getPalIzq().getPalancaRot() < interfaz.escena.getPalIzq().getPalancaMAXrot()) // SI NO HA LLEGADO AL VALOR DE ROTACION MAXIMO PERMITIDO
			interfaz.escena.getPalIzq().setPalancaRot(interfaz.escena.getPalIzq().getPalancaRot() + 3); //AUMENTA GRADOS A LA ROTACION
		else {
			interfaz.escena.getPalIzq().setPalancaLimitMAX(true); //PONE COMO TRUE QUE HA LLEGADO AL MAXIMO DE LA PALANCA 
			interfaz.escena.getPalIzq().setBajando_Palanca(true); //ACTIVA QUE PUEDE BAJAR LA PALANCA
		}
	}
	
	else if (interfaz.escena.getPalIzq().getBajando_Palanca() && interfaz.escena.getPalIzq().getPalancaRot() > interfaz.escena.getPalIzq().getPalancaMINrot()) //SI ESTÁ ACTIVO PODER BAJAR Y ES MAYOR AL MINIMO DE GRADOS POSIBLES A BAJAR
		interfaz.escena.getPalIzq().setPalancaRot(interfaz.escena.getPalIzq().getPalancaRot() - 3); //SE DECREMENTAN GRADOS A LA ROTACION
	
	else if (interfaz.escena.getPalIzq().getSubiendo_Palanca() && interfaz.escena.getPalIzq().getPalancaRot() < interfaz.escena.getPalIzq().getPalancaMINrot()) { // SI TAMBIÉN HA TERMINADO DE BAJAR
		interfaz.escena.getPalIzq().setPalancaLimitMAX(false);
		interfaz.escena.getPalIzq().setSubiendo_Palanca(false);
		interfaz.escena.getPalIzq().setBajando_Palanca(false);
	}
}

void igvInterfaz::subirPalancaDer()
{
	if (!interfaz.escena.getPalDer().getPalancaLimitMAX()) { //SI NO HA LLEGADO AL LIMITE MAXIMO DE SUBIR LA PALANCA (SE TRUNCA UNA VEZ VUELVE A BAJAR POR COMPLETO)
		interfaz.escena.getPalDer().setPalancaLimitMIN(false);
		if (interfaz.escena.getPalDer().getPalancaRot() > interfaz.escena.getPalDer().getPalancaMAXrot()) // SI NO HA LLEGADO AL VALOR DE ROTACION MAXIMO PERMITIDO
			interfaz.escena.getPalDer().setPalancaRot(interfaz.escena.getPalDer().getPalancaRot() - 3); //AUMENTA GRADOS A LA ROTACION
		else {
			interfaz.escena.getPalDer().setPalancaLimitMAX(true); //PONE COMO TRUE QUE HA LLEGADO AL MAXIMO DE LA PALANCA 
			interfaz.escena.getPalDer().setBajando_Palanca(true); //ACTIVA QUE PUEDE BAJAR LA PALANCA
		}
	}

	else if (interfaz.escena.getPalDer().getBajando_Palanca() && interfaz.escena.getPalDer().getPalancaRot() < interfaz.escena.getPalDer().getPalancaMINrot()) //SI ESTÁ ACTIVO PODER BAJAR Y ES MAYOR AL MINIMO DE GRADOS POSIBLES A BAJAR
		interfaz.escena.getPalDer().setPalancaRot(interfaz.escena.getPalDer().getPalancaRot() + 3); //SE DECREMENTAN GRADOS A LA ROTACION

	else if (interfaz.escena.getPalDer().getSubiendo_Palanca() && interfaz.escena.getPalDer().getPalancaRot() > interfaz.escena.getPalDer().getPalancaMINrot()) { // SI TAMBIÉN HA TERMINADO DE BAJAR
		interfaz.escena.getPalDer().setPalancaLimitMAX(false);
		interfaz.escena.getPalDer().setSubiendo_Palanca(false);
		interfaz.escena.getPalDer().setBajando_Palanca(false);
	}

}




