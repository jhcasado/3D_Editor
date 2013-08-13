#ifndef CCAMARA_H
#define CCAMARA_H

#include "centidad3d.h"
#include "cmatriz4x4.h"

class CCamara : public CEntidad3d
{
	public:

	CCamara (char *nombre, int d);
	~CCamara () {}
	
	CMatriz4x4 matrizperspectiva;
	CMatriz4x4 matrizcambiocoordenadas;
	int d;
	
	void EstablecerCambioCoordenadas();
};

#endif
