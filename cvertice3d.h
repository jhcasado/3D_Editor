#ifndef CVERTICE3D_H
#define CVERTICE3D_H

#include <stdio.h>
#include <math.h>

#include "cpuntofijo.h"

class CMatriz4x4;
class CTriangulo;

typedef struct{
	CPuntoFijo x, y, z, w;
} TV3D;

class CVertice3d : public TV3D
{
	public:
	
	CVertice3d () {}
	CVertice3d (CPuntoFijo a, CPuntoFijo b, CPuntoFijo c, CPuntoFijo d = 1.0) 
		{x = a; y = b; z = c; w = d;}
	~CVertice3d () {}
	
	//CPuntoFijo x, y, z, w;
	
	void Establecer(CPuntoFijo a, CPuntoFijo b, CPuntoFijo c, CPuntoFijo d = 1.0)
	{x = a; y = b; z = c; w = d;}
	void Establecer(int a, int b, int c, int d = 1)
	{x = (CPuntoFijo) a; y = (CPuntoFijo) b; z = (CPuntoFijo) c; w = (CPuntoFijo) d;}
	void Establecer(const CVertice3d &v)
	{x = v.x; y = v.y; z = v.z; w = v.w;}
	
	void Normalizar()
	{
		CPuntoFijo raiz;
		
		raiz = (x*x) + (y*y) + (z*z);
		
		if (raiz > 0)
		{
			raiz = 1 / sqrt(raiz);
			x *= raiz;
			y *= raiz;
			z *= raiz;
		}
	}
	
	double Distancia(CVertice3d *v)
	{
		CPuntoFijo dx, dy, dz, raiz;
		
		dx = v->x - x;
		dy = v->y - y;
		dz = v->z - z;
		
		raiz = (dx*dx) + (dy*dy) + (dz*dz);
		
		return (sqrt(raiz));
	}
	
	double ProductoEscalar(CVertice3d *v)
	{return ((x * v->x) + (y * v->y) + (z * v->z));}
	
	//void NormalTriangulo(CTriangulo *t, CVertice3d *vertices);
	
	void Vector(CVertice3d *ini, CVertice3d *fin)
	{x = fin->x - ini->x; y = fin->y - ini->y; z = fin->z - ini->z; w = 1.0;}
	
	
	CVertice3d *operator -()
	{
		CVertice3d *neg = new CVertice3d;
	
		neg->x = -x; neg->y = -y; neg->z = -z; neg->w = -w;
		return neg;
	}
	
	CVertice3d *operator =(CVertice3d v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
		return this;
	}
	
	CVertice3d *operator *=(int v)
	{
		x *= v; y *= v; z *= v; w *= v;
		return this;
	}
	
	CVertice3d *operator *=(CMatriz4x4 m);
	
	void VerticePorMatriz(CVertice3d *v, CMatriz4x4 *m);
	
	void Mostrar()
	{
		printf("(%2.6f, %2.6f, %2.6f, %2.6f)\n)",x, y, z, w);
	}
};

#endif
