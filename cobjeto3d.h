#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "centidad3d.h"
#include "cvertice3d.h"
#include "ctriangulo.h"
#include "mate.h"

class CObjeto3d : public CEntidad3d
{
	public:

	CObjeto3d (char *nombre) : CEntidad3d(nombre, OBJETO3D) {vertices = 0; verticesmod = 0; normales = 0; triangulos = 0;}
	~CObjeto3d () 
	{
		if (vertices) delete vertices; 
		if (verticesmod) delete verticesmod; 
		if (verticesmod2) delete verticesmod2; 
		if (normales) delete normales; 
		if (triangulos) delete triangulos;
	}
	
	CVertice3d *vertices;
	CVertice3d *verticesmod, *verticesmod2;
	CVertice3d *normales;
	int nvertices;
	CTriangulo *triangulos;
	int ntriangulos;
};

#endif
