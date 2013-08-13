#ifndef CZBUFFER_H
#define CZBUFFER_H

#include "cpuntofijo.h"

class CZBuffer
{
	public:
	
	CZBuffer () {zbuffer = 0;}
	CZBuffer (int ancho, int alto)
	{
		width = ancho; 
		height = alto; 
		zbuffer = new CPuntoFijo[ancho * alto];
		CalcularCentros();
	}
	~CZBuffer () {if (zbuffer) delete zbuffer;}
	
	CPuntoFijo *zbuffer;
	int width, height;
	int centroX, centroY;

	void CalcularCentros() {centroX = width / 2;centroY = height / 2;}
	int CoorX(int x) {return (x + centroX);}
	int CoorY(int y) {return (-y + centroY);}
	
	CPuntoFijo *Z(int xm, int ym)
	{
		int x, y;
		
		x = CoorX(xm);
		y = CoorY(ym);
		
		if ((x < 0) || (y < 0) || (x >= width) || (y >= height))
			return 0;
	
		return &(zbuffer[(width * y) + x]);
	}
	
	void CambiarTamano(int ancho, int alto)
	{
		if (zbuffer) delete zbuffer;
		width = ancho;
		height = alto; 
		zbuffer = new CPuntoFijo[width * height];
		CalcularCentros();
		Limpiar();
	}
	
	void Limpiar()
	{
		for (int i = 0; i < (width * height); i++)
			zbuffer[i] = 10000000000000.0;
	}
};

#endif
