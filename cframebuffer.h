#ifndef CFRAMEBUFFER_H
#define CFRAMEBUFFER_H

#include <qpixmap.h>
#include <qcolor.h>
#include <qpainter.h>
#include <qfont.h>


class CFrameBuffer : public QPixmap 
{
	public:
	
	CFrameBuffer (int ancho, int alto, QFont *fuente, QColor fondo = Qt::white, int bitsporpixel = -1, Optimization optimizacion = QPixmap::BestOptim);
	~CFrameBuffer () {delete pintor;}
	
	QPainter *pintor;
	QColor fondo, borde;
	QFont *fuente;
	int centroX, centroY;

	void CalcularCentros() {centroX = width() / 2;centroY = height() / 2;}
	int CoorX(int x) {return (x + centroX);}
	int CoorY(int y) {return (-y + centroY);}
	
	void PintarPixel(int x, int y, int r, int g, int b) {CambiarColor(r,g,b);PintarPixel(x,y);}
	void PintarPixel(int x, int y, QColor color) {CambiarColor(color);PintarPixel(x,y);}
	void PintarPixel(int x, int y) {pintor->drawPoint(CoorX(x), CoorY(y));}
	
	void PintarLinea(int xi, int yi, int xf, int yf, int r, int g, int b) {CambiarColor(r,g,b);PintarLinea(xi,yi,xf,yf);}
	void PintarLinea(int xi, int yi, int xf, int yf, QColor color) {CambiarColor(color);PintarLinea(xi,yi,xf,yf);}
	void PintarLinea(int xi, int yi, int xf, int yf) {pintor->drawLine(CoorX(xi), CoorY(yi),CoorX(xf), CoorY(yf));}
	
	void CambiarColor(int r, int g, int b) {pintor->setPen(QColor(r,g,b));}
	void CambiarColor(QColor color) {pintor->setPen(color);}

	void ModoXor() {pintor->setRasterOp(Qt::XorROP);}
	void ModoCopiar() {pintor->setRasterOp(Qt::CopyROP);}

	void CambiarTamano(int ancho, int alto);
	void Limpiar() {fill(fondo);}
	void PintarBorde() {pintor->setPen(borde);pintor->drawRect(rect());}
	
	void ComenzarPintar() {Limpiar();pintor->begin(this);}
	void TerminarPintar() {PintarBorde();pintor->end();}
	
	void Escribir(int x, int y, char *texto) {pintor->setFont(*fuente);pintor->drawText(x, y, texto);}
};

#endif
