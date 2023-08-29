//**************************************************************************
// Práctica 2 
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"



//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  ambiente_difusa = _vertex4f(0.2,0.4,0.9,1.0);
  especular = _vertex4f(0.5,0.5,0.5,1.0);
  brillo = 80;

  ambiente_difusa1 = _vertex4f(0.780392f, 0.568627f, 0.113725f, 1.0f );
  especular1 = _vertex4f(0.992157f, 0.941176f, 0.807843f, 1.0f );
  brillo1 =  27.8974f;

  ambiente_difusa2 = _vertex4f(0.5f,0.4f,0.4f,1.0f);
  especular2 = _vertex4f( 0.7f,0.04f,0.04f,1.0f);
  brillo2 =  10.0f;

  ambiente_difusa3 = _vertex4f(0.427451f, 0.470588f, 0.541176f, 1.0f);
  especular3 = _vertex4f(0.333333f, 0.333333f, 0.521569f, 1.0f);
  brillo3 = 9.84615f;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r,g,b);

  glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
	    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	  }
  glEnd();


}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

    glBegin(GL_TRIANGLES);
      for (int i=0;i<caras.size();i++){
	      //glColor3f(rand()%1000/1000.0,rand()%1000/1000.0,rand()%1000/1000.0);  --> modod discoteca
	      glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	    }

glEnd();

}

//*************************************************************************
// Parte parctica 4 dibujar plano
//*************************************************************************

void _triangulos3D::draw_plano(int tipo)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable (GL_LIGHTING);
  glEnable (GL_NORMALIZE);
  glShadeModel(GL_FLAT);  //GL_SMOOTH para suave o GL_FLAT para plana


  if(tipo == 0){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  }else if(tipo == 1){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular1);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo1);

  }else if (tipo == 2){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular2);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo2);

  }else if (tipo == 3){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa3);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular3);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo3);
  }


    glBegin(GL_TRIANGLES);
      for (int i=0;i<caras.size();i++){
	      glNormal3f(normales_caras[i].x, normales_caras[i].y, normales_caras[i].z);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	    }
    glEnd();

glDisable(GL_LIGHTING);

}




//*************************************************************************
// Parte parctica 4 dibujar suave
//*************************************************************************

void _triangulos3D::draw_suave()
{

	glEnable (GL_LIGHTING);
  glShadeModel(GL_SMOOTH);  //GL_SMOOTH para suave o GL_FLAT para plana

glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

    glBegin(GL_TRIANGLES);
      for (int i=0;i<caras.size();i++){
	      glNormal3f(normales_vertices[caras[i]._0].x, 
                    normales_vertices[caras[i]._0].y, 
                    normales_vertices[caras[i]._0].z);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

	      glNormal3f(normales_vertices[caras[i]._1].x, 
                    normales_vertices[caras[i]._1].y, 
                    normales_vertices[caras[i]._1].z);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

	      glNormal3f(normales_vertices[caras[i]._2].x, 
                    normales_vertices[caras[i]._2].y, 
                    normales_vertices[caras[i]._2].z);
	      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	    }
    glEnd();

glDisable(GL_LIGHTING);

}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor, int tipo)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
	case SOLID_FLAT:draw_plano(tipo);break;
	case SOLID_SMOOTH:draw_suave();break;


	}
}



//*************************************************************************
// asignación NORMALES CARAS
//*************************************************************************

void _triangulos3D::calcular_normales_caras(){

int i, n_c;
n_c=caras.size();
normales_caras.resize(n_c);
_vertex3f v_a, v_b;
float norma;

for(i=0;i<n_c;i++){
  v_a = vertices[caras[i]._1] - vertices[caras[i]._0];
  v_b = vertices[caras[i]._2] - vertices[caras[i]._0];

  normales_caras[i].x = v_a.y*v_b.z - v_a.z*v_b.y;
  normales_caras[i].y = v_a.z*v_b.x - v_a.x*v_b.z;
  normales_caras[i].z = v_a.x*v_b.y - v_a.y*v_b.x;

  norma = sqrt (normales_caras[i].x * normales_caras[i].x +
                normales_caras[i].y * normales_caras[i].y +
                normales_caras[i].z * normales_caras[i].z );

  normales_caras[i].x = normales_caras[i].x/norma;
  normales_caras[i].y = normales_caras[i].y/norma;
  normales_caras[i].z = normales_caras[i].z/norma;


}


}


//*************************************************************************
// asignación VERTICES
//*************************************************************************

void _triangulos3D::calcular_normales_vertices(){

int i, n_c;
float norma;
n_c=vertices.size();
normales_vertices.resize(n_c);
_vertex3f v_a, v_b;

for(i=0;i<n_c;i++){
  normales_vertices[i] = _vertex3f(0.0,0.0,0.0);
}

for(i=0; i<caras.size(); i++){
  normales_vertices[caras[i]._0] += normales_caras[i];
  normales_vertices[caras[i]._1] += normales_caras[i];
  normales_vertices[caras[i]._2] += normales_caras[i];

}

 
for(i=0;i<n_c;i++){
    norma = sqrt (normales_vertices[i].x * normales_vertices[i].x +
                normales_vertices[i].y * normales_vertices[i].y +
                normales_vertices[i].z * normales_vertices[i].z );

  normales_vertices[i].x = normales_vertices[i].x/norma;
  normales_vertices[i].y = normales_vertices[i].y/norma;
  normales_vertices[i].z = normales_vertices[i].z/norma;
}


}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     } 
  }
}


//*************************************************************************


void _triangulos3D::colors_plano(float r, float g, float b, float l_x, float l_y, float l_z){

int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
_vertex3f v_l;
float norma, escalar;

for(i=0;i<n_c;i++){

  v_l.x = l_x - vertices[caras[i]._0].x;
  v_l.y = l_y - vertices[caras[i]._0].y;
  v_l.z = l_z - vertices[caras[i]._0].z;

  norma = sqrt ( v_l.x * v_l.x +  v_l.y * v_l.y +  v_l.z * v_l.z);
  v_l.x=v_l.x/norma;
  v_l.y=v_l.y/norma;
  v_l.z=v_l.z/norma;

  escalar = v_l.x * normales_caras[i].x + v_l.y * normales_caras[i].y + v_l.z * normales_caras[i].z;

  colores_caras[i].r = r*0.1;
  colores_caras[i].g = g*0.1;
  colores_caras[i].b = b*0.1;

  if(escalar >= 0){
    colores_caras[i].r += r*escalar;
    colores_caras[i].g += g*escalar;
    colores_caras[i].b += b*escalar;
  }

}


}

//*************************************************************************


void _triangulos3D::colors_suave(float r, float g, float b, float l_x, float l_y, float l_z){

int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
_vertex3f v_l;
float norma, escalar;


calcular_normales_vertices();

for(i=0;i<n_c;i++){

  v_l.x = l_x - vertices[caras[i]._0].x;
  v_l.y = l_y - vertices[caras[i]._0].y;
  v_l.z = l_z - vertices[caras[i]._0].z;

  norma = sqrt ( v_l.x * v_l.x +  v_l.y * v_l.y +  v_l.z * v_l.z);
  v_l.x=v_l.x/norma;
  v_l.y=v_l.y/norma;
  v_l.z=v_l.z/norma;

  escalar = v_l.x * normales_vertices[i].x + v_l.y * normales_vertices[i].y + v_l.z * normales_vertices[i].z;

  colores_caras[i].r = r*0.1;
  colores_caras[i].g = g*0.1;
  colores_caras[i].b = b*0.1;

  if(escalar >= 0){
    colores_caras[i].r += r*escalar;
    colores_caras[i].g += g*escalar;
    colores_caras[i].b += b*escalar;
  }

}


}


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices 
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;

vertices[4].x=tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=-tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// caras (triangulos)
caras.resize(12);
caras[0]._0=2;caras[0]._1=3;caras[0]._2=0;
caras[1]._0=2;caras[1]._1=0;caras[1]._2=1;
caras[2]._0=2;caras[2]._1=1;caras[2]._2=4;

caras[3]._0=6;caras[3]._1=2;caras[3]._2=4;
caras[4]._0=6;caras[4]._1=7;caras[4]._2=3;
caras[5]._0=6;caras[5]._1=3;caras[5]._2=2;

caras[6]._0=5;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=7;caras[7]._1=6;caras[7]._2=4;
caras[8]._0=3;caras[8]._1=7;caras[8]._2=0;

caras[9]._0=0;caras[9]._1=7;caras[9]._2=5;
caras[10]._0=0;caras[10]._1=5;caras[10]._2=4;
caras[11]._0=0;caras[11]._1=4;caras[11]._2=1;


//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores de las caras
colors_random();


}





//*************************************************************************
// clase cabeza
//*************************************************************************

_crear_cabeza::_crear_cabeza(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam/2;vertices[0].y=-0.1;vertices[0].z=tam;
vertices[1].x=tam/2;vertices[1].y=-0.1;vertices[1].z=tam;
vertices[2].x=tam/2;vertices[2].y=0.1;vertices[2].z=tam;
vertices[3].x=-tam/2;vertices[3].y=0.1;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores
colors_plano(0.8, 0.7, 0, -20, 20, 10);
}


//*************************************************************************
// clase cola
//*************************************************************************

_crear_cola::_crear_cola(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam / 2;vertices[0].y=-0.1;vertices[0].z=tam;
vertices[1].x=tam / 2;vertices[1].y=-0.1;vertices[1].z=tam;
vertices[2].x=tam / 2;vertices[2].y=0.1;vertices[2].z=tam;
vertices[3].x=-tam / 2;vertices[3].y=0.1;vertices[3].z=tam;
vertices[4].x=-0.05;vertices[4].y=-tam*1.5;vertices[4].z=-tam;
vertices[5].x=0.05;vertices[5].y=-tam*1.5;vertices[5].z=-tam;
vertices[6].x=0.05;vertices[6].y=tam*1.5;vertices[6].z=-tam;
vertices[7].x=-0.05;vertices[7].y=tam*1.5;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 




//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores

colors_plano(0.8, 0.7, 0, -20, 20, 10);


}



//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

//caras
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores de las caras
colors_random();


}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
}



void _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;
int i;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

//vertices
  for(i=0; i<vertices.size();i++){
    vertices[i].x=ver_ply[3*i];
    vertices[i].y=ver_ply[3*i+1];
    vertices[i].z=ver_ply[3*i+2];
  }



//caras
  for(i=0; i<caras.size();i++){
    caras[i]._0=car_ply[3*i];
    caras[i]._1=car_ply[3*i+1];
    caras[i]._2=car_ply[3*i+2];
  }


//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores
colors_plano(0.8, 0.7, 0, -20, 20, 10);


//colores de las caras
//colors_random();





}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa_i, int tapa_s, int tipo) //tipo=1 esfero =0 el resto
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++){
  for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

caras.resize(2*(num_aux-1)*num);
int c=0;

for(j=0;j<num;j++){
  for(i=0;i<num_aux-1;i++){
    caras[c]._1=j*num_aux+i;
    caras[c]._0=j*num_aux+i+1;
    caras[c]._2=((j+1)%num)*num_aux+i+1;

    c=c+1;
    caras[c]._1=((j+1)%num)*num_aux+i+1;
    caras[c]._0=((j+1)%num)*num_aux+i;
    caras[c]._2=j*num_aux+i;

    c=c+1;

  }
}


// tapa inferior

vertices.resize(num_aux*num+2);   //esta bien así? se desperdicia un poco de espacio..

if(tapa_i == 1){
  vertices[num_aux*num].x=0;
  vertices[num_aux*num].z=vertices[0].z;
  vertices[num_aux*num].y=vertices[0].y;


  caras.resize((2*(num_aux-1)*num) + (num*2) );   

  c=2*(num_aux-1)*num;

  for(i=0; i<num-1; i++){
    caras[c]._0= i * num_aux ;
    caras[c]._1= num_aux*num;    
    caras[c]._2= (i * num_aux) + num_aux;                //vertice del centro

    c+=1;

  }

  caras[c]._0= (num-1) * num_aux ;
  caras[c]._1= num_aux*num;          
  caras[c]._2= 0 * num_aux; 

  c+=1;

}

// tapa superior
if(tapa_s == 1){
  vertices[num_aux*num+1].x=0;
  vertices[num_aux*num+1].z=vertices[num_aux-1].z;
  vertices[num_aux*num+1].y=vertices[num_aux-1].y;



  for(i=0; i<num-1; i++){
    caras[c]._0= i * num_aux + num_aux -1;
    caras[c]._1= (i * num_aux + num_aux -1) + num_aux;
    caras[c]._2= num_aux*num+1;                           //vertice del medio

  c+=1;

  }

  caras[c]._0= (num-1) * num_aux + num_aux -1;
  caras[c]._1= num_aux-1;
  caras[c]._2= num_aux*num+1;

}



//normales
calcular_normales_caras();

if(tipo == 1 || tipo== 0){   //esfera o el resto (pinta bien la cara de abajo para revolucion)
    float norma;
    int n_v;

    n_v = vertices.size();
    normales_vertices.resize(n_v);

    for(i=0;i<vertices.size(); i++){
      norma = sqrt(vertices[i].x * vertices[i].x + vertices[i].y * vertices[i].y + vertices[i].z * vertices[i].z);
      normales_vertices[i].x=vertices[i].x/norma;
      normales_vertices[i].y=vertices[i].y/norma;
      normales_vertices[i].z=vertices[i].z/norma;

    }

  }else calcular_normales_vertices();

//colores de las caras
colors_random();


}

//*************************************************************************
// clase que llaman a revolucion
//*************************************************************************


_cilindro::_cilindro(float radio, int altura, int lados){


  vector<_vertex3f> perfil;
  _vertex3f aux;
  int num = 6;
 
			aux.x=radio; aux.y=-altura; aux.z=0.0;
			perfil.push_back(aux);
			aux.x=radio; aux.y=altura; aux.z=0.0;
			perfil.push_back(aux);

      parametros(perfil,lados,1,1,0);  //activamos las dos tapas

}


_cono::_cono(float radio, int altura, int lados){

  vector<_vertex3f> perfil;
  _vertex3f aux;

			aux.x=radio; aux.y=-altura; aux.z=0.0;
			perfil.push_back(aux);
			aux.x=0.0; aux.y=altura; aux.z=0.0;
			perfil.push_back(aux);
			
    parametros(perfil,lados,1,0,0);   //activamos solo la tapa inferior


}


_esfera::_esfera(int radio, int num1, int lados){

  vector<_vertex3f> perfil;
  _vertex3f aux;

  int i;

for (i=1;i<num1;i++)
  { aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);
    aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);
    aux.z=0.0;
    perfil.push_back(aux);
  }

     parametros(perfil,lados,1,1,1);     //activamos las 2 tapas

}



//************************************************************************
// leer un archivo PLY
//************************************************************************


_rotacion_PLY::_rotacion_PLY(char *archivo, int num){

int i, n_ver, n_car;

vector<float> ver_ply;
vector<int> car_ply;
vector<_vertex3f> perfil;
_vertex3f aux;


_file_ply::read(archivo, ver_ply, car_ply);


n_ver = ver_ply.size()/3;
n_car = car_ply.size()/3;

printf ("Numero de vertices= %d\n Numero de caras= %d\n", n_ver, n_car);


//vertices

for(int i=0; i<n_ver; i++){
  aux.x = ver_ply[3*i];
  aux.y = ver_ply[3*i+1];
  aux.z = ver_ply[3*i+2];
  perfil.push_back(aux);

}

parametros(perfil,num,1,1,0);



}




//************************************************************************
// objeto por extrusión
//************************************************************************


_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int ce=0;
for (i=0;i<num_aux;i++)         
  {
   caras[ce]._0=i*2;
   caras[ce]._1=(i*2+2)%(num_aux*2);
   caras[ce]._2=i*2+1;    
   ce=ce+1;
   caras[ce]._0=(i*2+2)%(num_aux*2);
   caras[ce]._1=(i*2+2)%(num_aux*2)+1;
   caras[ce]._2=i*2+1;    
   ce=ce+1;    
      
   }   

//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores de las caras
colors_random();


}



//************************************************************************
// práctica 3, PEZ
//************************************************************************

//************************************************************************
// cara
//************************************************************************

_cabeza::_cabeza(){

ancho=0.4;
alto=0.6;
fondo=0.6;

};


void _cabeza::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
crear_cabeza.draw(modo, r, g, b, grosor, 1);
glPopMatrix();
};

//************************************************************************
// cuerpo
//************************************************************************
_cubo1::_cubo1(float tam){

//vertices 
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;

vertices[4].x=tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=-tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// caras (triangulos)
caras.resize(12);
caras[0]._0=2;caras[0]._1=3;caras[0]._2=0;
caras[1]._0=2;caras[1]._1=0;caras[1]._2=1;
caras[2]._0=2;caras[2]._1=1;caras[2]._2=4;

caras[3]._0=6;caras[3]._1=2;caras[3]._2=4;
caras[4]._0=6;caras[4]._1=7;caras[4]._2=3;
caras[5]._0=6;caras[5]._1=3;caras[5]._2=2;

caras[6]._0=5;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=7;caras[7]._1=6;caras[7]._2=4;
caras[8]._0=3;caras[8]._1=7;caras[8]._2=0;

caras[9]._0=0;caras[9]._1=7;caras[9]._2=5;
caras[10]._0=0;caras[10]._1=5;caras[10]._2=4;
caras[11]._0=0;caras[11]._1=4;caras[11]._2=1;


//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores de las caras
colors_plano(0.8, 0.7, 0, -20, 20, 10);

};

_cuerpo::_cuerpo()
{
ancho=0.4;
alto=0.6;
fondo=0.4;

};

void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor)
{

glPushMatrix();
glScalef(ancho, alto, fondo);
cubo1.draw(modo, r, g, b, grosor, 2);
glPopMatrix();


};



//************************************************************************
// aletas
//************************************************************************
_piramide1::_piramide1(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

//caras
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//normales
calcular_normales_caras();
calcular_normales_vertices();

//colores de las caras
colors_plano(0.8, 0.7, 0, -20, 20, 10);

};

_aletas::_aletas()
{
ancho=1;
alto=1;
fondo=1;

};

void _aletas::draw(_modo modo, float r, float g, float b, float grosor)
{

glPushMatrix();
glScalef(ancho, alto, fondo);
piramide1.draw(modo, r, g, b, grosor, 3);
glPopMatrix();


};

//************************************************************************
// cola
//************************************************************************

_cola::_cola(){

ancho=0.4;
alto=0.6;
fondo=0.6;


};


void _cola::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
crear_cola.draw(modo, r, g, b, grosor, 3);
glPopMatrix();
};



//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_pez::_pez()
{

 giro_cabeza = 0.0;
 giro_cola = 0.0;
 giro_aleta1 = -35.0;
 giro_aleta2 = -35.0;


 giro_cabeza_max = 5.0;
 giro_cabeza_min = -5.0;
 giro_cola_max = 3.0;
 giro_cola_min = -3.0;
 giro_aleta1_max = -30.0;
 giro_aleta1_min = -65.0;
 giro_aleta2_max = -30.0;
 giro_aleta2_min = -65.0;



};





//PRIMERO ESCALADO, ROTACION, TRANSLACION
//se le pasan los grados directamentamente en glrotate

void _pez::draw(_modo modo, float r, float g, float b, float grosor)
{

  float x = 1.5;  //alargamos la cabeza para hacer el cuerpo trasero

  // TRONCO DEL PEZ Y CABEZA------------------------------------------------------------


  glPushMatrix();

  cuerpo.draw(modo, r, g, b, grosor);

  glTranslatef(0,0,cuerpo.fondo);
  cuerpo.draw(modo, r, g, b, grosor);

  glTranslatef(0,0,cuerpo.fondo);
  cuerpo.draw(modo, r, g, b, grosor);

  glTranslatef(0,0,-3*cuerpo.fondo);
  cuerpo.draw(modo, r, g, b, grosor);

  glTranslatef(0,0,-cuerpo.fondo);
  cuerpo.draw(modo, r, g, b, grosor);

  //cuello
  glPushMatrix();
  glTranslatef(0,0,4*cuerpo.fondo + cabeza.fondo -0.1 ); 
  cabeza.draw(modo, r, g, b, grosor);
  glPopMatrix();

  //cabeza
  glPushMatrix();
  glTranslatef(0,0,4*cuerpo.fondo + cabeza.fondo );
  glRotatef(giro_cabeza,0,1,0);
  glScalef(1.1,1.1,1.1);           
  cabeza.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // PARTE TRASERA ANTES DE LA COLA--------------------------------------------------------

  glPushMatrix();
  glTranslatef(0,0,-3*cuerpo.fondo + cabeza.fondo + 0.1); 
  glRotatef(180,0,1,0);
  glScalef(1.0,1.0,1.0);           
  cabeza.draw(modo, r, g, b, grosor);
  glPopMatrix();


  //union trasera
  glPushMatrix();
  glTranslatef(0,0,-3*cuerpo.fondo + cabeza.fondo -0.3);
  glRotatef(180,0,1,0);
  glScalef(0.55,0.25,0.5);           
  cabeza.draw(modo, r, g, b, grosor);
  glPopMatrix();


  //COLA DEL PEZ-----------------------------------------------------------------------------

  glPushMatrix();
  glTranslatef(0,0,-2*cuerpo.fondo - cabeza.fondo +0.2);
  glRotatef(giro_cola,0,1,0);
  cola.draw(modo, r, g, b, grosor);
  glPopMatrix();


  //ALETA DERECHA-----------------------------------------------------------------

  glPushMatrix();
  glTranslatef(-cuerpo.ancho/4,0,3*cuerpo.fondo );  
  glRotatef(90,0,0,1);
  glRotatef(90,0,1,0);
  glRotatef(giro_aleta1,0,0,1);
  glScalef(0.1,1.5,0.5);           
  aletas.draw(modo, r, g, b, grosor);
  glPopMatrix();


  //ALETA IZQUIERDA-----------------------------------------------------------------

  glPushMatrix();
  glTranslatef(cuerpo.ancho/4,0,3*cuerpo.fondo );    //te lo mete en pila y te lo lee al reves de como lo has metido
  glRotatef(-90,0,0,1);
  glRotatef(90,0,1,0);
  glRotatef(giro_aleta2,0,0,1);
  glScalef(0.1,1.5,0.5);           
  aletas.draw(modo, r, g, b, grosor);
  glPopMatrix();


  glPopMatrix();

  


};
