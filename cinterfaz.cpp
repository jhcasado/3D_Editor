#include <stdio.h>

#include <qlayout.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qvbuttongroup.h>
#include <qgroupbox.h>
#include <qvgroupbox.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qcursor.h>
#include <qlabel.h>
#include <qslider.h>
#include <qstring.h>

#include "cinterfaz.h"
#include "centidad3d.h"

CInterfaz::CInterfaz(QWidget *padre, CLienzo *pantalla)
	: QObject(padre, "Interfaz")
{
	CInterfaz::padre = padre;
	CInterfaz::pantalla = pantalla;
	
	radio = 0;
	meridianos = 50;
	
	ninterfazobjeto3d = 0;
	ninterfazrevolucion = 0;
}

void CInterfaz::CrearInterfaz()
{printf("%d x %d\n", padre->width(), padre->height());
	QGridLayout *malla = new QGridLayout(padre, 2, 2, 2, 5, "malla");
	//malla->setResizeMode(QLayout::Minimum);
		malla->addWidget(pantalla, 0, 0);
		malla->setRowStretch(0, 1000);
		malla->setColStretch(0, 1000);
		QObject::connect(pantalla, SIGNAL(RatonMovidoIzq(int, int)), padre, SLOT(RatonMovidoIzq(int, int)));
		QObject::connect(pantalla, SIGNAL(RatonMovidoDer(int, int)), padre, SLOT(RatonMovidoDer(int, int)));
		QObject::connect(pantalla, SIGNAL(RatonMovidoCen(int, int)), padre, SLOT(RatonMovidoCen(int, int)));
		QObject::connect(pantalla, SIGNAL(RatonMovidoIzqCtrl(int)), padre, SLOT(RatonMovidoIzqCtrl(int)));
		QObject::connect(pantalla, SIGNAL(RatonMovidoDerCtrl(int)), padre, SLOT(RatonMovidoDerCtrl(int)));
		QObject::connect(pantalla, SIGNAL(RatonMovidoCenCtrl(int)), padre, SLOT(RatonMovidoCenCtrl(int)));
		QObject::connect(pantalla, SIGNAL(RatonPulsadoIzq(int, int)), padre, SLOT(RatonPulsadoIzq(int, int)));
		QObject::connect(pantalla, SIGNAL(RatonPulsadoDer(int, int)), padre, SLOT(RatonPulsadoDer(int, int)));
		QObject::connect(pantalla, SIGNAL(RatonMovido(int, int)), padre, SLOT(RatonMovido(int, int)));

		QVBoxLayout *tablabotonesder = new QVBoxLayout(0, 0, 0, "tablabotonesder");
			lista = new QListBox(padre);
			lista->setSelectionMode(QListBox::Single);
			lista->setMinimumHeight(115);
			lista->setMaximumHeight(115);
			lista->setMinimumWidth(120);
			QObject::connect(lista, SIGNAL(highlighted(int)), this, SLOT(CambioSeleccion(int)));
			tablabotonesder->addWidget(lista, 0, Qt::AlignTop);
			
			QHBoxLayout *tablacolor = new QHBoxLayout(0, 0, 0, "tablacolor");
				QPushButton *bcolor = new QPushButton("Cambiar",padre);
					bcolor->setFixedSize(bcolor->sizeHint());
					QObject::connect(bcolor, SIGNAL(clicked()), padre, SLOT(CambiarColor()));
				tablacolor->addWidget(bcolor);
				
				colorentidad = new QWidget(padre);
					colorentidad->setBackgroundColor(black);
					colorentidad->setFixedSize(50,25);
				tablacolor->addWidget(colorentidad);
			tablabotonesder->addLayout(tablacolor);
		
			cbocultarentidad = new QCheckBox("Ocultar Entidad", padre);
				cbocultarentidad->setChecked(TRUE);
				QObject::connect(cbocultarentidad, SIGNAL(toggled(bool)), padre, SLOT(OcultarEntidad(bool)));
			tablabotonesder->addWidget(cbocultarentidad, 0, Qt::AlignTop);
			
			cbocultarcaras = new QCheckBox("Ocultar Caras", padre);
				cbocultarcaras->setChecked(TRUE);
				QObject::connect(cbocultarcaras, SIGNAL(toggled(bool)), padre, SLOT(OcultarCaras(bool)));
			tablabotonesder->addWidget(cbocultarcaras, 0, Qt::AlignTop);
			interfazobjeto3d[ninterfazobjeto3d] = cbocultarcaras;
			ninterfazobjeto3d++;
			
			bgmodopintar = new QVButtonGroup("Pintar:",padre);
				bgmodopintar->setInsideSpacing(0);
				QRadioButton *puntos = new QRadioButton("Puntos",bgmodopintar);
				puntos->state();
				QRadioButton *lineas = new QRadioButton("Lineas",bgmodopintar);
				lineas->state();
				QRadioButton *relleno = new QRadioButton("Relleno",bgmodopintar);
				relleno->state();
				bgmodopintar->setButton(1);
				QObject::connect(bgmodopintar, SIGNAL(clicked(int)), padre, SLOT(CambiarModoPintar(int)));
			tablabotonesder->addWidget(bgmodopintar, 0, Qt::AlignTop);
			interfazobjeto3d[ninterfazobjeto3d] = bgmodopintar;
			ninterfazobjeto3d++;
				
			bgmodosombreado = new QVButtonGroup("Sombreado:",padre);
				bgmodosombreado->setInsideSpacing(0);
				QRadioButton *sinsombreado = new QRadioButton("Sin Sombreado",bgmodosombreado);
				sinsombreado->state();
				QRadioButton *flat = new QRadioButton("Flat",bgmodosombreado);
				flat->state();
				QRadioButton *gouraud = new QRadioButton("Gouraud",bgmodosombreado);
				gouraud->state();
				gouraud->setEnabled(false);
//				QRadioButton *phong = new QRadioButton("Phong",bgmodosombreado);
				bgmodosombreado->setButton(0);
				QObject::connect(bgmodosombreado, SIGNAL(clicked(int)), padre, SLOT(CambiarModoSombreado(int)));
			tablabotonesder->addWidget(bgmodosombreado, 0, Qt::AlignTop);
			interfazobjeto3d[ninterfazobjeto3d] = bgmodosombreado;
			ninterfazobjeto3d++;
/*				
			QVGroupBox *gbnormal = new QVGroupBox("Pintar Normales:",padre);
				gbnormal->setInsideSpacing(0);
				QCheckBox *normalestriangulos = new QCheckBox("Triangulos", gbnormal);
				QCheckBox *normalesvertices = new QCheckBox("Vertices", gbnormal);
			tablabotonesder->addWidget(gbnormal, 0, Qt::AlignTop);
			interfazobjeto3d[ninterfazobjeto3d] = gbnormal;
			ninterfazobjeto3d++;

			QVGroupBox *gbcajaobjeto = new QVGroupBox("Caja Limite:",padre);
				gbcajaobjeto->setInsideSpacing(0);
				QCheckBox *pintarcaja = new QCheckBox("Pintar Caja", gbcajaobjeto);
				QCheckBox *normalcaja = new QCheckBox("Pintar Normal", gbcajaobjeto);
				QCheckBox *direccioncaja = new QCheckBox("Dir. de Vista", gbcajaobjeto);
			tablabotonesder->addWidget(gbcajaobjeto, 0, Qt::AlignTop);
			interfazobjeto3d[ninterfazobjeto3d] = gbcajaobjeto;
			ninterfazobjeto3d++;
*/			
			QLabel *lsuprev = new QLabel("\nPARAMETROS\nSUPERFICIE\nDE\nREVOLUCION\n ", padre);
				lsuprev->setAlignment(Qt::AlignCenter);
			tablabotonesder->addWidget(lsuprev, 0, Qt::AlignTop);
			interfazrevolucion[ninterfazrevolucion] = lsuprev;
			ninterfazrevolucion++;
			
			lradio = new QLabel(" \nRadio: \n ", padre);
			CambioRadio(radio);
			tablabotonesder->addWidget(lradio, 0, Qt::AlignTop);
			interfazrevolucion[ninterfazrevolucion] = lradio;
			ninterfazrevolucion++;
			
			QSlider * sradio = new QSlider(0, 100, 1, radio, Qt::Horizontal, padre);
				sradio->setStyle("platinum");
				QObject::connect(sradio, SIGNAL(valueChanged(int)), this, SLOT(CambioRadio(int)));
			tablabotonesder->addWidget(sradio, 0, Qt::AlignTop);
			interfazrevolucion[ninterfazrevolucion] = sradio;
			ninterfazrevolucion++;
		
			lmeridianos = new QLabel(" \n \n \n \nMeridianos: \n ", padre);
			CambioMeridianos(meridianos);
			tablabotonesder->addWidget(lmeridianos, 0, Qt::AlignTop);
			interfazrevolucion[ninterfazrevolucion] = lmeridianos;
			ninterfazrevolucion++;
			
			QSlider * smeridianos = new QSlider(3, 100, 1, meridianos, Qt::Horizontal, padre);
				smeridianos->setStyle("platinum");
				QObject::connect(smeridianos, SIGNAL(valueChanged(int)), this, SLOT(CambioMeridianos(int)));
			tablabotonesder->addWidget(smeridianos, 0, Qt::AlignTop);
			interfazrevolucion[ninterfazrevolucion] = smeridianos;
			ninterfazrevolucion++;
		
		malla->addMultiCellLayout(tablabotonesder, 0, 0, 1, 1, Qt::AlignTop);//Qt::AlignHCenter | );
	
		QHBoxLayout *tablabotonesinf = new QHBoxLayout(0, 0, 10, "tablabotonesinf");
			QPushButton *bsalir = new QPushButton("Salir",padre);
			bsalir->setFixedSize(bsalir->sizeHint());
			QObject::connect(bsalir, SIGNAL(clicked()), padre, SLOT(close()));
			tablabotonesinf->addWidget(bsalir);
/*			
			QPushButton *bcargar3ds = new QPushButton("Cargar .3ds",padre);
			bcargar3ds->setFixedSize(bcargar3ds->sizeHint());
			bcargar3ds->setMaximumWidth(3000);
//			QObject::connect(bcargar3ds, SIGNAL(clicked()), padre, SLOT(close()));
			tablabotonesinf->addWidget(bcargar3ds);
*/			
			QPushButton *bcrearobjrev = new QPushButton("Crear Revolucion",padre);
			bcrearobjrev->setFixedSize(bcrearobjrev->sizeHint());
			bcrearobjrev->setMaximumWidth(3000);
			QObject::connect(bcrearobjrev, SIGNAL(clicked()), padre, SLOT(IniciarSuperficieRevolucion()));
			tablabotonesinf->addWidget(bcrearobjrev);
/*		
			QPushButton *bcrearobjpro = new QPushButton("Crear Profundidad",padre);
			bcrearobjpro->setFixedSize(bcrearobjpro->sizeHint());
			bcrearobjpro->setMaximumWidth(3000);
//			QObject::connect(bcrearobjpro, SIGNAL(clicked()), padre, SLOT(close()));
			tablabotonesinf->addWidget(bcrearobjpro);
		
			QPushButton *bcrearcamara = new QPushButton("Crear Camara",padre);
			bcrearcamara->setFixedSize(bcrearcamara->sizeHint());
			bcrearcamara->setMaximumWidth(3000);
			QObject::connect(bcrearcamara, SIGNAL(clicked()), padre, SLOT(CrearCamara()));
			tablabotonesinf->addWidget(bcrearcamara);
		
			QPushButton *bcrearluz = new QPushButton("Crear Luz",padre);
			bcrearluz->setFixedSize(bcrearluz->sizeHint());
			bcrearluz->setMaximumWidth(3000);
//			QObject::connect(bcrearluz, SIGNAL(clicked()), padre, SLOT(close()));
			tablabotonesinf->addWidget(bcrearluz);	
*/			
		malla->addMultiCellLayout(tablabotonesinf, 1, 1, 0, 1, Qt::AlignTop);//, Qt::AlignLeft | );
		
	QObject::connect(this, SIGNAL(EntidadCambiada(int)), padre, SLOT(CambiarEntidadActiva(int)));
	MostrarBotonesTipo(-1);
printf("%d x %d\n", padre->width(), padre->height());}

void CInterfaz::InsertarEntidad(char *nombre, int posicion)
{
	int p;

	lista->insertItem(nombre);
	p = lista->count() - 1;

	posiciones[p] = posicion;
	//QListBoxItem *prueba = lista->firstItem();
	//QString nombrelista(prueba->text());
	//if (lista->itemVisible() == 0)
	//lista->selectAll();
	//printf("** lista %s %d\n",nombrelista.ascii(), lista->index(prueba));
	//lista->setCurrentItem(prueba);
	//if (p != 0) 
	lista->setCurrentItem(p);
	//lista->setSelected(prueba, true);
	printf("Entidad Insertada: %d->%d\n", p, posicion);
}

int CInterfaz::EntidadSeleccionada()
{
	printf("Entidad Seleccionada: %d -> %d\n", lista->currentItem(), posiciones[lista->currentItem()]);
	return posiciones[lista->currentItem()];
}

void CInterfaz::CambioSeleccion(int i)
{
	printf("Cambiar Seleccion: %d -> %d\n", i, posiciones[i]);
	emit EntidadCambiada(posiciones[i]);
	printf("Cambio de Seleccion: %d->%d\n", i, posiciones[i]);
}

void CInterfaz::MostrarBotonesTipo(int tipo)
{
	int i;

	for (i = 0; i < ninterfazobjeto3d; i++)
		interfazobjeto3d[i]->hide();
	
	for (i = 0; i < ninterfazrevolucion; i++)
		interfazrevolucion[i]->hide();
		
	if (tipo == OBJETO3D)
		for (i = 0; i < ninterfazobjeto3d; i++)
			interfazobjeto3d[i]->show();
	
	if (tipo == ENTIDAD)
		for (i = 0; i < ninterfazrevolucion; i++)
			interfazrevolucion[i]->show();
}

void CInterfaz::CambioRadio(int r)
{
	QString radio;
	
	radio.sprintf(" \nRadio: %d\n ", r);
	lradio->setText(radio);
	CInterfaz::radio = r;
}

void CInterfaz::CambioMeridianos(int m)
{
	QString meridianos;
	
	meridianos.sprintf(" \n \n \n \nMeridianos: %d\n ", m);
	lmeridianos->setText(meridianos);
	CInterfaz::meridianos = m;
}
