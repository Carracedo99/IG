//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, EXTRUSION, CONO, CILINDRO, ESFERA, ROTACION_PLY, PEZ, AUTOMATICO, OBJETO_EX1, OBJETO_EX2, OBJETO_EX3} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_cilindro cilindro(1.0,1,7);		//pasarle los paremto que queremos
_cono cono(1.0,1,6);
_esfera esfera(3,20,50);
_objeto_ply  ply; 
_rotacion rotacion; 
_extrusion *extrusion;
_rotacion_PLY rotacion_ply("archivo1", 6);
_pez pez;
_crear_cabeza crear_cabeza;
_crear_cola crear_cola;

_objeto_examen1 objeto_examen1;
_objeto_examen2 objeto_examen2(0.5,0.4,20,10);
_objeto_examen3 objeto_examen3;


int pulsar = 0;
int giro1 = 0;

bool creciendo1 = true;
bool creciendo2 = true;
bool creciendo3 = true;
bool creciendo4 = true;


// _objeto_ply *ply;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
		case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,5);break;

    case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
    case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
		
		case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,5);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,5);break;
		case ROTACION_PLY: rotacion_ply.draw(modo,1.0,0.0,0.0,5);break;
    case PEZ: pez.draw(modo,1.0,0.0,0.0,5);break;

    case OBJETO_EX1: objeto_examen1.draw(modo,1.0,0.0,0.0,5);break;
    case OBJETO_EX2: objeto_examen2.draw(modo,1.0,0.0,0.0,5);break;
    case OBJETO_EX3: objeto_examen3.draw(modo,1.0,0.0,0.0,5);break;



	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_COLORS;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'X':t_objeto=EXTRUSION;break;
		case 'N':t_objeto=CONO;break;
		case 'I':t_objeto=CILINDRO;break;
		case 'E':t_objeto=ESFERA;break;
		case 'L':t_objeto=ROTACION_PLY;break;
        case 'A':t_objeto=PEZ;break;
        case 'S':t_objeto=PEZ;
            if(pulsar==0){
                giro1=1;
                pulsar=1;
            }else{
                giro1=0;
                pulsar=0;
            }
            break;

		case 'M':t_objeto=OBJETO_EX1;break;
    case 'B':t_objeto=OBJETO_EX2;break;
    case 'V':t_objeto=OBJETO_EX3;break;



	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;


/*
   case GLUT_KEY_F1:pez.giro_cabeza+=1;
        if (pez.giro_cabeza > pez.giro_cabeza_max)
            pez.giro_cabeza= pez.giro_cabeza_max;break;
    
   case GLUT_KEY_F2:pez.giro_cabeza-=1;
        if (pez.giro_cabeza < pez.giro_cabeza_min)
            pez.giro_cabeza= pez.giro_cabeza_min;break;

   case GLUT_KEY_F3:pez.giro_cola+=1;
        if ( pez.giro_cola > pez.giro_cola_max)
            pez.giro_cola= pez.giro_cola_max;break;

   case GLUT_KEY_F4:pez.giro_cola-=1;
        if (pez.giro_cola < pez.giro_cola_min)
            pez.giro_cola = pez.giro_cola_min;break;

   case GLUT_KEY_F5:pez.giro_aleta1+=1;
        if (pez.giro_aleta1 > pez.giro_aleta1_max)
            pez.giro_aleta1 = pez.giro_aleta1_max;break;

   case GLUT_KEY_F6:pez.giro_aleta1-=1;
        if (pez.giro_aleta1 < pez.giro_aleta1_min) 
            pez.giro_aleta1 = pez.giro_aleta1_min;break;

   case GLUT_KEY_F7:pez.giro_aleta2+=1;
        if (pez.giro_aleta2 > pez.giro_aleta2_max)
            pez.giro_aleta2 = pez.giro_aleta2_max;break;

   case GLUT_KEY_F8:pez.giro_aleta2-=1;
        if (pez.giro_aleta2 < pez.giro_aleta2_min) 
            pez.giro_aleta2 = pez.giro_aleta2_min;break;

*/
   case GLUT_KEY_F1:objeto_examen3.escalado1+=0.05;
        if (objeto_examen3.escalado1 > objeto_examen3.escalado1_max)
            objeto_examen3.escalado1= objeto_examen3.escalado1_max;break;
    
   case GLUT_KEY_F2:objeto_examen3.escalado1-=0.05;
        if (objeto_examen3.escalado1 < objeto_examen3.escalado1_min)
            objeto_examen3.escalado1= objeto_examen3.escalado1_min;break;


   case GLUT_KEY_F3:objeto_examen3.giro1+=1;
        if (objeto_examen3.giro1 > objeto_examen3.escalado1_max)
            objeto_examen3.giro1= objeto_examen3.escalado1_max;break;
    
   case GLUT_KEY_F4:objeto_examen3.giro1-=1;
        if (objeto_examen3.giro1 < objeto_examen3.giro1_min)
            objeto_examen3.giro1= objeto_examen3.giro1_min;break;





	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;


//-----------------------------------------------------------------------------------------------------------
// se incia la posicion del observador, en el eje z
//cambiar 10 por 4 u otro numero para el ZOOM
Observer_distance=10*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;
//--------------------------------------------------------------------------------------------------------------


// se indica el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


void automatico(){
    
    //CABEZA

    if (pez.giro_cabeza==pez.giro_cabeza_min){
      creciendo1=true;
    }else if (pez.giro_cabeza==pez.giro_cabeza_max){
      creciendo1=false;
    }

    if(creciendo1==true){
      pez.giro_cabeza+=giro1;
    }else{
      pez.giro_cabeza-=giro1;
    }

    //COLA
    
    if (pez.giro_cola==pez.giro_cola_min){
      creciendo2=true;
    }else if (pez.giro_cola==pez.giro_cola_max){
      creciendo2=false;
    }

    if(creciendo2==true){
      pez.giro_cola+=giro1;
    }else{
      pez.giro_cola-=giro1;
    }

    //ALETA1
    
    if (pez.giro_aleta1==pez.giro_aleta1_min){
      creciendo3=true;
    }else if (pez.giro_aleta1==pez.giro_aleta1_max){
      creciendo3=false;
    }

    if(creciendo3==true){
      pez.giro_aleta1+=giro1;
    }else{
      pez.giro_aleta1-=giro1;
    }

    //ALETA2
    
    if (pez.giro_aleta2==pez.giro_aleta2_min){
      creciendo4=true;
    }else if (pez.giro_aleta2==pez.giro_aleta2_max){
      creciendo4=false;
    }

    if(creciendo4==true){
      pez.giro_aleta2+=giro1;
    }else{
      pez.giro_aleta2-=giro1;
    }

    glutPostRedisplay();

}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
// perfil 

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);

rotacion.parametros(perfil,6,1,1);


//--------------------------------------------------

aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply = new _objeto_ply(argv[1]);


glutIdleFunc(automatico);


// inicio del bucle de eventos
glutMainLoop();

return 0;

}
