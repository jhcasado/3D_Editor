#include "clienzo.h"

#include <stdio.h>
#include <qcursor.h>
//#include <qpaintdevice.h>
#include <qpainter.h>

#include "cmundo3d.h"

CLienzo::CLienzo (int ancho, int alto, CFrameBuffer *framebuffer, CZBuffer *zbuffer, QWidget *padre, const char *nombre)
	: QWidget (padre, nombre, Qt::WResizeNoErase | Qt::WRepaintNoErase)//Qt::WNoAutoErase)
{
	setMinimumSize(ancho, alto);
	//setMaximumSize(ancho, alto);
	resize(ancho, alto);
	setBackgroundMode(Qt::NoBackground);
	setCursor(QCursor(Qt::CrossCursor));
	
	centroX = ancho / 2;
	centroY = alto / 2;
	
	CLienzo::framebuffer = framebuffer;
	CLienzo::zbuffer = zbuffer;
	framebuffer->CambiarTamano(ancho, alto);
	zbuffer->CambiarTamano(ancho, alto);

}

void CLienzo::mousePressEvent(QMouseEvent *e)
{
	ButtonState b;
	
	x = e->x();
	y = e->y();
	
	b = e->button();
	if (b & Qt::LeftButton)
	{
		printf("raton Izquierdo presionado\n");
		emit RatonPulsadoIzq(x - centroX, -y + centroY);
	}
	else
	if (b & Qt::RightButton)
	{
		printf("raton Derecho presionado\n");
		emit RatonPulsadoDer(x - centroX, -y + centroY);
	}
	
	printf("raton presionado\n");
	
	grabMouse();
}

void CLienzo::mouseReleaseEvent(QMouseEvent *e)
{
	x = e->x();
	y = e->y();
	
	releaseMouse();
}

void CLienzo::mouseMoveEvent(QMouseEvent *e)
{
	ButtonState b;
	
	xm = e->x() - x;
	ym = y - e->y();

	b = e->state();
	
	if (b & Qt::LeftButton)
		if (b & Qt::ControlButton)
			emit RatonMovidoIzqCtrl(ym);
		else
			emit RatonMovidoIzq(xm, ym);
	else
	if (b & Qt::RightButton)
		if (b & Qt::ControlButton)
			emit RatonMovidoDerCtrl(ym);
		else
			emit RatonMovidoDer(xm, ym);
	else
	if (b & Qt::MidButton)
		if (b & Qt::ControlButton)
			emit RatonMovidoCenCtrl(ym);
		else
			emit RatonMovidoCen(xm, ym);
	else
		emit RatonMovido(e->x() - centroX, - e->y() + centroY);

	x = e->x();
	y = e->y();
}

void CLienzo::paintEvent(QPaintEvent *)
{
	//QWidget::paintEvent(e);
	//printf("pintado1: %d, %d\n", width(), height());
	//framebuffer->TerminarPintar();
	bitBlt(this, 0, 0, framebuffer, 0, 0, width(), height(), Qt::CopyROP);
//	if (e->erased())
//		printf("ERROR: Se hizo un BORRADO\n");
	//printf("pintado2: %d, %d\n", e->rect().width(), e->rect().height());
}

void CLienzo::resizeEvent(QResizeEvent *)
{
	//const QSize tamano = e->size();
	//printf("resize1 %d x %d\n", tamano.width(), tamano.height());
	centroX = width() / 2;
	centroY = height() / 2;
	framebuffer->CambiarTamano(width(), height());
	zbuffer->CambiarTamano(width(), height());
	((CMundo3d *)parentWidget())->DibujarMundo3d();
//	repaint(0, 0, width(), height(), FALSE);
	//update(0, 0, width(), height());
	printf("Resize Event: %d, %d\n", width(), height());
}
