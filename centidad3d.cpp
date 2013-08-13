#include <stdio.h>

#include "centidad3d.h"

CEntidad3d::CEntidad3d(char *nombre, int tipo)
{
	strncpy(CEntidad3d::nombre, nombre, 50);
	posicion.Establecer(0,0,0);
	derecha.Establecer(1,0,0);
	arriba.Establecer(0,0,1);
	direccionvista.Establecer(0,1,0);
	//matrizmundo.Identidad();
	matrizrotado.Identidad();
	matrizescalado.Identidad();
	matriztrasladado.Identidad();
	color.setRgb(0,0,0);
	ocultarcaras = TRUE;
	ocultarentidad = FALSE;
	modopintar = LINEAS;
	modosombreado = SINSOM;
	CEntidad3d::tipo = tipo;
}
