#ifndef CLIENZO_H
#define CLIENZO_H

#include <qwidget.h>
#include <qpixmap.h>

#include "cframebuffer.h"
#include "czbuffer.h"

#define ANCHO 400
#define ALTO 300

class CLienzo : public QWidget
{
	Q_OBJECT
	
	public:
	
	CLienzo (int ancho, int alto, CFrameBuffer *framebuffer, CZBuffer *zbuffer, QWidget *padre = 0, const char *nombre = 0);
	~CLienzo () {}
	
	CFrameBuffer *framebuffer;
	CZBuffer *zbuffer;
	int x, y, xm, ym;
	int centroX, centroY;
	
	void CapturarRaton() {setMouseTracking(TRUE);grabMouse();}
	void SoltarRaton() {releaseMouse();setMouseTracking(FALSE);}
	
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);

	signals:
	void RatonMovido(int, int);
	void RatonMovidoIzq(int, int);
	void RatonMovidoDer(int, int);
	void RatonMovidoCen(int, int);
	void RatonMovidoIzqCtrl(int);
	void RatonMovidoDerCtrl(int);
	void RatonMovidoCenCtrl(int);
	void RatonPulsadoIzq(int, int);
	void RatonPulsadoDer(int, int);
};

#endif
