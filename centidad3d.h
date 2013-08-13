#ifndef CENTIDAD3D_H
#define CENTIDAD3D_H

//#include <qstring.h>
#include <qcolor.h>

#include "cvertice3d.h"
#include "cmatriz4x4.h"
//#include "ccaja.h"

//class CMatriz4x4;

#define PUNTOS		0
#define LINEAS		1
#define RELLENO	2

#define SINSOM		0
#define FLAT		1
#define GOURAUD	2
#define PHONG		3

#define ENTIDAD	0
#define OBJETO3D	1
#define CAMARA		2
#define LUZ			3

class CEntidad3d
{
	public:
	
	CEntidad3d(char *nombre,int tipo = ENTIDAD);
	~CEntidad3d() {}

	char nombre[50];
	CVertice3d posicion;
	CVertice3d direccionvista;
	CVertice3d arriba;
	CVertice3d derecha;
	CMatriz4x4 matrizrotado;
	CMatriz4x4 matrizescalado;
	CMatriz4x4 matriztrasladado;
	//CMatriz4x4 matrizmundo;
	QColor color;
	bool ocultarcaras;
	bool ocultarentidad;
	int modopintar;
	int modosombreado;
	int tipo;
//	CCaja caja;
};

#endif
