#include "cframebuffer.h"

#include <stdio.h>

CFrameBuffer::CFrameBuffer(int ancho, int alto, QFont *fuente, QColor fondo, int bitsporpixel, Optimization optimizacion) 
	: QPixmap(ancho, alto, bitsporpixel, optimizacion)
{
	pintor = new QPainter();
//	pintor->begin(this);
	
	CFrameBuffer::fondo = fondo;
	borde = Qt::black;
	CFrameBuffer::fuente = fuente;
	
	CalcularCentros();
	
	Limpiar();
}

void CFrameBuffer::CambiarTamano(int ancho, int alto)
{
//	pintor->end();
	resize(ancho, alto);
	
	CalcularCentros();
	
	printf("Se ha cambiado el tamaño al framebuffer: %d x %d\n", ancho, alto);
//	pintor->begin(this);
}
