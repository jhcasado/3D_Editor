#ifndef MUNDO3D_H
#define MUNDO3D_H

#include <qwidget.h>
#include <qpixmap.h>
#include <qfont.h>

#include "clienzo.h"
#include "centidad3d.h"
#include "cframebuffer.h"
#include "czbuffer.h"
#include "cinterfaz.h"
#include "csuperficierevolucion.h"
#include "ctriangulo.h"
#include "cvertice3d.h"
#include "mate.h"

#include "ccamara.h"

#define MAX_ENTIDADES 20

#define MIN_ANCHO_PANTALLA 640
#define MIN_ALTO_PANTALLA 480

typedef struct {
	int x;
	double z, n;
	double zsum, nsum;
} TExtremoLineaBarrido;

class CMundo3d : public QWidget
{
	Q_OBJECT

	public:
	
	CMundo3d (QFont *fuente, QWidget *padre = 0, const char *nombre = 0);
	~CMundo3d () {delete framebuffer;delete zbuffer;}

	CInterfaz *interfaz;
	CEntidad3d *entidades[MAX_ENTIDADES];
	CEntidad3d *entidadactiva;
	CCamara *camaraactiva;
	int nentidades;
	CLienzo *pantalla;
	CFrameBuffer *framebuffer;
	CZBuffer *zbuffer;
	CSuperficieRevolucion superficierevolucion;
	int revolucionando;

	void DibujarMundo3d();
	CVertice3d CambioCoordenadasCamaraAMundo(double x, double y, double z);
	inline void PintarPixel(int x, int y, double z);
	
	public slots:
	void RatonMovido(int x, int y);
	void RatonMovidoIzq(int x, int y);
	void RatonMovidoDer(int x, int y);
	void RatonMovidoCen(int x, int y);
	void RatonMovidoIzqCtrl(int z);
	void RatonMovidoDerCtrl(int z);
	void RatonMovidoCenCtrl(int z);
	void RatonPulsadoIzq(int x, int y);
	void RatonPulsadoDer(int x, int y);
	void CambiarEntidadActiva(int i);
	void IniciarSuperficieRevolucion();
	void CambiarColor();
	void CrearCamara();
	void OcultarEntidad(bool estado);
	void OcultarCaras(bool estado);
	void CambiarModoPintar(int modopintar);
	void CambiarModoSombreado(int modosombreado);
};

#endif
