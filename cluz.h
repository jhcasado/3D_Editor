#ifndef CLUZ_H
#define CLUZ_H


#include "centidad3d.h"

class CLuz : public CEntidad3d
{
	public:
	
	CLuz (char *nombre) : CEntidad3d(nombre, LUZ) {}
	~CLuz () {}
};

#endif
