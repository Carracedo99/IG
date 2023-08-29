//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void 	draw(_modo modo, float r, float g, float b, float grosor);


/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};



//*************************************************************************
// clase cabeza
//*************************************************************************

class _crear_cabeza: public _triangulos3D
{
public:

	_crear_cabeza(float tam=0.5);
};

//*************************************************************************
// clase cola
//*************************************************************************

class _crear_cola: public _triangulos3D
{
public:

	_crear_cola(float tam=0.5);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************


//tapa_i = 0--> sin tapa, tapa_i = 1 --> con tapa

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num, int tapa_i, int tapa_s);
};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//*************************************************************************
// clase cilindro
//*************************************************************************

class _cilindro: public _rotacion
{
public:

	_cilindro(float radio, int altura, int lados);		//PARA QUE QUIERO EL TIPO??
};


//*************************************************************************
// clase cono
//*************************************************************************

class _cono: public _rotacion
{
public:

	_cono(float lado, int altura, int lados);
};


//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera: public _rotacion
{
public:

	_esfera(int radio, int num1, int lados);
};


//*************************************************************************
// clase archivo ply
//*************************************************************************

class _rotacion_PLY: public _rotacion
{
public:

	_rotacion_PLY(char *archivo, int num);

	//void  parametros_PLY(char *archivo, int num);	//leeremos el archivo ply
};





//----------------------------------------------------------------------------------------------------------------------------------
//************************************************************************
// cabeza del pez
//************************************************************************

class _cabeza: public _triangulos3D
{
public:
       _cabeza();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_crear_cabeza crear_cabeza;
};


//************************************************************************
// cuerpo (LLAMAR 4 VECES Y APLICARLE TRANSLACION)
//************************************************************************

class _cuerpo: public _triangulos3D
{
public:
       _cuerpo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};



//************************************************************************
// cola
//************************************************************************

class _cola: public _triangulos3D
{
public:
       _cola();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_crear_cola crear_cola;
;
};



//************************************************************************
// PEZ (montaje del objeto final)
//************************************************************************

class _pez: public _triangulos3D
{
public:
       _pez();
       
void  draw(_modo modo, float r, float g, float b, float grosor);


float giro_cabeza;
/*
float giro_cuerpo1;
float giro_cuerpo2;
float giro_cuerpo3;
float giro_cuerpo4;
float giro_cuerpo5;
float giro_cuerpo_trasero;
*/
float giro_cola;
float giro_aleta1;
float giro_aleta2;


float giro_cabeza_max;
float giro_cabeza_min;
/*
float giro_cuerpo_max;
float giro_cuerpo_min;
float giro_cuerpo_trasero_max;
float giro_cuerpo_trasero_min;
*/
float giro_cola_max;
float giro_cola_min;
float giro_aleta1_max;
float giro_aleta1_min;
float giro_aleta2_max;
float giro_aleta2_min;



protected:
_cabeza cabeza;
_cuerpo cuerpo;
_cola cola;
_piramide piramide;


};


