#include "ccamara.h"

CCamara::CCamara(char *nombre, int d)
	 : CEntidad3d(nombre, CAMARA)
{
	CCamara::d = d;
	matrizperspectiva.Perspectiva(d);

	derecha.Establecer(-1,0,0);
	arriba.Establecer(0,0,1);
	direccionvista.Establecer(0,-1,0);
	posicion.Establecer(0,0,0);
	EstablecerCambioCoordenadas();
}

void CCamara::EstablecerCambioCoordenadas()
{
	matrizcambiocoordenadas.CambioSistemaCoordenadas(derecha, arriba, direccionvista);
}
