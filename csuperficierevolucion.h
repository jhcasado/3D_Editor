#ifndef CSUPERFICIEREVOLUCION_H
#define CSUPERFICIEREVOLUCION_H

#include "cvertice3d.h"
#include "ctriangulo.h"
#include "cframebuffer.h"
#include "cobjeto3d.h"

#define MAX_PUNTOS_REVOLUCION 100

typedef struct
{
	int x, y;
} TPunto2d;

class CSuperficieRevolucion
{
//	Q_OBJECT

	public:
	
	CSuperficieRevolucion () {}
	~CSuperficieRevolucion () {}
	
	TPunto2d puntos2d[MAX_PUNTOS_REVOLUCION];
	int npuntos2d;
	int xmax, ymax, ymin;

	CVertice3d puntos3d[MAX_PUNTOS_REVOLUCION];
	int npuntos3d;
		
	CVertice3d *vertices;
	CVertice3d *normales;
	CTriangulo *triangulos;
	int nvertices;
	int ntriangulos;
	
	void Inicializar() {npuntos2d = 0;}
	void InsertarPunto2d(int x, int y);
	void PintarRevolucion2d(CFrameBuffer *framebuffer, int x, int y);
	void PintarRevolucion2d(CFrameBuffer *framebuffer);
	void VolcarPuntos2dEn3d(int radio);
	void CrearSuperficieRevolucion(CObjeto3d *obj, int meridianos = 30, int radio = 0);
};

#endif
