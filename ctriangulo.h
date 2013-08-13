#ifndef CTRIANGULO_H
#define CTRIANGULO_H


#include "cvertice3d.h"
#include "mate.h"

typedef struct{
	int a, b, c;
} TT3D;


class CTriangulo : public TT3D
{
	public:
	
	CTriangulo () {}
	~CTriangulo () {}
	
	//int a, b, c;
	CVertice3d normal;
	CVertice3d centro;
	
	void CalcularNormal(CVertice3d *vertices)
	{
		CVertice3d ba, bc;
	
		ba.Vector(&(vertices[b]), &(vertices[a]));
		bc.Vector(&(vertices[b]), &(vertices[c]));

		normal.x = (ba.y * bc.z) - (ba.z * bc.y);
		normal.y = (ba.z * bc.x) - (ba.x * bc.z);
		normal.z = (ba.x * bc.y) - (ba.y * bc.x);
	}
	
	void CalcularCentro(CVertice3d *vertices)
	{
		centro.x = (vertices[a].x + vertices[b].x + vertices[c].x) / 3.0;
		centro.y = (vertices[a].y + vertices[b].y + vertices[c].y) / 3.0;
		centro.z = (vertices[a].z + vertices[b].z + vertices[c].z) / 3.0;
	}
	
	double ProductoEscalarNormalCentro()
	{
		return normal.ProductoEscalar(&centro);
	}
	
	int Oculto(CVertice3d *vertices)
	{
//		CalcularNormal(vertices);
		// LAS CAMARAS ESTARAN SIEMPRE CENTRADAS EN 0,0,0 CON VISTA HACIA 0,0,1
		// POR ESTO AL HACER EL PRODUCTO ESCALAR VENDRA DADO UNICAMENTE POR LA
		// COMPONENTE Z DE LA NORMAL DEL TRIANGULO
//		if (normal.z > 0.0)
//			return 0;
//		return 1;
		if (((vertices[a].x - vertices[b].x) * (vertices[c].y - vertices[b].y)) > ((vertices[a].y - vertices[b].y) * (vertices[c].x - vertices[b].x)))
			return 0;
		return 1;
	}

	int Oculto(TV2D *vertices)
	{
		// LAS CAMARAS ESTARAN SIEMPRE CENTRADAS EN 0,0,0 CON VISTA HACIA 0,0,1
		// POR ESTO AL HACER EL PRODUCTO ESCALAR VENDRA DADO UNICAMENTE POR LA
		// COMPONENTE Z DE LA NORMAL DEL TRIANGULO
		if (((vertices[a].x - vertices[b].x) * (vertices[c].y - vertices[b].y)) > ((vertices[a].y - vertices[b].y) * (vertices[c].x - vertices[b].x)))
			return 0;
		return 1;
	}
};

#endif
