#ifndef CINTERFAZ_H
#define CINTERFAZ_H

#include <qobject.h>
#include <qwidget.h>

#include <qlistbox.h>
#include <qcheckbox.h>
#include <qvbuttongroup.h>
#include <qlabel.h>

#include "clienzo.h"

#define MAX_ENTIDADES 20

class CInterfaz : public QObject
{
	Q_OBJECT

	public:
	
	CInterfaz (QWidget *padre, CLienzo *pantalla);
	~CInterfaz () {}
	
	QWidget *padre;
	CLienzo *pantalla;
	int posiciones[MAX_ENTIDADES];
	
	QListBox *lista;
	QWidget *colorentidad;
	QCheckBox *cbocultarentidad;
	QCheckBox *cbocultarcaras;
	QVButtonGroup *bgmodopintar;
	QVButtonGroup *bgmodosombreado;
	QLabel *lradio, *lmeridianos;
	int radio, meridianos;
	
	QWidget *interfazobjeto3d[20];
	int ninterfazobjeto3d;
	QWidget *interfazrevolucion[20];
	int ninterfazrevolucion;
	void MostrarBotonesTipo(int tipo);
	
	void CrearInterfaz();
	void InsertarEntidad(char *nombre, int posicion);
	int EntidadSeleccionada();
	
	signals:
	void EntidadCambiada(int);
	
	public slots:
	void CambioSeleccion(int i);
	void CambioRadio(int r);
	void CambioMeridianos(int m);
};

#endif
