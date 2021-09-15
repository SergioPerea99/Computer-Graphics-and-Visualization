#include "igvTextura.h"


static unsigned int SECUENCIA_TEXTURAS = 1;

// Metodos constructores y destructor
igvTextura::igvTextura(char *fichero) {
	ancho = 0;
	alto = 0;

	SDL_Surface* imagen = NULL;

	glEnable(GL_TEXTURE_2D);
	if (!glIsTexture(idTextura)) {

		imagen = IMG_Load(fichero);
		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Error al cargar la imagen: %s\n", IMG_GetError());
			return;

		}
		/* Muestra alguna información sobre la imagen */
		printf("Cargando %s: %dx%d %dbpp\n", fichero,
			imagen->w, imagen->h, imagen->format->BitsPerPixel);

		// Apartado G: Añadir aquí el código para cargar como textura OpenGL la imagen */
		glGenTextures(SECUENCIA_TEXTURAS++, &idTextura);//	- Generar el identificador de textura y asignarlo al atributo idTextura (glGenTextures)

		//TODO: PARAMETRIZAR LOS ID DE LAS TEXTURAS

		glBindTexture(GL_TEXTURE_2D, idTextura);//	- Enlazar el identificador creado a GL_TEXTURE_2D (glBindTexture)

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen->w, imagen->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->pixels);//  - Especificar la textura, asignádole como textura el array imagen (glTexImage2D)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//  - Modo de aplicación de la textura (glTexEnvf)


		//	- Parámetros de la textura: repetición y filtros (glTexParameteri)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		


		SDL_FreeSurface(imagen);
		
		
	}
	
}

void igvTextura::aplicar(unsigned int modo) {
	switch (modo) {
	case 0:
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//  - Modo de aplicación de la textura (glTexEnvf)
		break;
	case 1:
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);//  - Modo de aplicación de la textura (glTexEnvf)
		break;
	case 2:
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//  - Modo de aplicación de la textura (glTexEnvf)
		break;
	default:
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//  - Modo de aplicación de la textura (glTexEnvf)
		break;

	}
	
	glBindTexture(GL_TEXTURE_2D, idTextura);
}

igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura); 
}
