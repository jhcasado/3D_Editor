#include <qapplication.h>

#include <stdlib.h>
#include <stdio.h>
#include <qfont.h>
#include <qstring.h>

#include "cmundo3d.h"

int main (int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QFont fuente = app.font(0);
	fuente.setPointSize(fuente.pointSize() - 1);
	app.setFont(fuente, TRUE);
	if (argc > 1)
		if (strcmp(argv[1],"-fuente") == 0)
		{
			QString nombre = fuente.family();
			printf("Fuente por defecto: %s, %d\n", nombre.ascii(), fuente.pointSize());
	
			int puntos = atoi(argv[2]);
			
			if (argc > 3)
				if (strcmp(argv[3],"-familia") == 0)
					fuente.setFamily(argv[4]);
			
			fuente.setPointSize(puntos);
			app.setFont(fuente, TRUE);
	
			fuente = app.font(0);
			nombre = fuente.family();
			printf("Fuente Seleccionada: %s, %d\n", nombre.ascii(), fuente.pointSize());
		}

	CMundo3d mundo3d(&fuente, 0, "Mundo3d");
	app.setMainWidget(&mundo3d);
	mundo3d.setCaption("QT::Motor3d");
	mundo3d.show();
	
	return(app.exec());
}
