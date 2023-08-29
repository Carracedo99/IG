//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>



const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS, SOLID_FLAT, SOLID_SMOOTH} _modo;

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
void	draw_plano(int tipo=0);
void	draw_suave();
void 	draw(_modo modo, float r, float g, float b, float grosor, int tipo = 0);

//calcular normales
void calcular_normales_caras();
void calcular_normales_vertices();



/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
void	colors_plano(float r, float g, float b, float l_x, float l_y, float l_z);
void	colors_suave(float r, float g, float b, float l_x, float l_y, float l_z);



vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;

//iluminacion
vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

//material

_vertex4f ambiente_difusa;	//coeficientes ambiente y difusion
_vertex4f especular;		//coeficientes epecular
float brillo;				//exponente del brillo

_vertex4f ambiente_difusa1;
_vertex4f especular1;
float brillo1;

_vertex4f ambiente_difusa2;
_vertex4f especular2;
float brillo2;

_vertex4f ambiente_difusa3;
_vertex4f especular3;
float brillo3;



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
// clase cubo1
//*************************************************************************

class _cubo1: public _triangulos3D
{
public:

	_cubo1(float tam=0.5);
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
// clase piramide1
//*************************************************************************

class _piramide1: public _triangulos3D
{
public:

	_piramide1(float tam=0.5, float al=1.0);
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
       
void  parametros(vector<_vertex3f> perfil, int num, int tapa_i, int tapa_s, int tipo);
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

_cubo1 cubo1;

};


//************************************************************************
// aletas
//************************************************************************

class _aletas: public _triangulos3D
{
public:

_aletas();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:

_piramide1 piramide1;

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

float giro_cola;
float giro_aleta1;
float giro_aleta2;


float giro_cabeza_max;
float giro_cabeza_min;

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
_aletas aletas;


};
