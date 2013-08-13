#include <stdio.h>
#include <qpainter.h>
#include <qlayout.h>
#include <qcolor.h>
#include <qcolordialog.h>

#include <math.h>

#include "cmundo3d.h"
#include "cinterfaz.h"

#include "cobjeto3d.h"
#include "ccamara.h"
#include "cluz.h"

#include "cvertice3d.h"

CMundo3d::CMundo3d (QFont *fuente, QWidget *padre, const char *nombre)
	: QWidget (padre, nombre)
{
	framebuffer = new CFrameBuffer(MIN_ANCHO_PANTALLA, MIN_ALTO_PANTALLA, fuente, Qt::white, -1, QPixmap::BestOptim);

	zbuffer = new CZBuffer(MIN_ANCHO_PANTALLA, MIN_ALTO_PANTALLA);
	
	pantalla = new CLienzo(MIN_ANCHO_PANTALLA, MIN_ALTO_PANTALLA, framebuffer, zbuffer, this);
	
	interfaz = new CInterfaz(this, pantalla);
	interfaz->CrearInterfaz();

	entidades[0] = new CCamara("Camara Principal", 500);
	camaraactiva = (CCamara *)entidades[0];
	interfaz->InsertarEntidad(entidades[0]->nombre, 0);
	camaraactiva->matriztrasladado.Trasladar(0,500,0);
	nentidades = 1;
	
	revolucionando = 0;
}

CVertice3d CMundo3d::CambioCoordenadasCamaraAMundo(double x, double y, double z)
{
	CMatriz4x4 t;
	CVertice3d p, v;
	
	p.Establecer(x,y,z);
	t.Traspuesta(camaraactiva->matrizcambiocoordenadas);
	
	v.VerticePorMatriz(&p, &t);
//	v.Mostrar();
	
	return v;
}

void CMundo3d::RatonMovidoIzq(int x, int y)
{
	if (revolucionando) return;
	
	CMatriz4x4 m;
	
	m.TrasladarV(CambioCoordenadasCamaraAMundo(x,y,0));
	
//	m.Trasladar((double)x, (double)y, 0.0);
	entidadactiva->matriztrasladado *= m;
	DibujarMundo3d();
//	printf("Raton Movido Izquierdo: %d, %d\n", x, y);
}

void CMundo3d::RatonMovidoIzqCtrl(int z)
{
	if (revolucionando) return;
	
	CMatriz4x4 m;
	
	m.TrasladarV(CambioCoordenadasCamaraAMundo(0,0,z));
	//m.Trasladar(0.0, 0.0, (double)z);
	
	entidadactiva->matriztrasladado *= m;
	DibujarMundo3d();
//	printf("Raton Movido Izquierdo + Control: %d\n", z);
}

void CMundo3d::RatonMovidoDer(int x, int y)
{
	if (revolucionando) return;
	
	CMatriz4x4 mx, my;
	
	mx.RotarX((double)y / 100.0);
	my.RotarZ((double)x / 100.0);
	entidadactiva->matrizrotado *= mx;
	entidadactiva->matrizrotado *= my;
	DibujarMundo3d();
//	printf("Raton Movido Derecho: %d, %d\n", x, y);
}

void CMundo3d::RatonMovidoDerCtrl(int z)
{
	if (revolucionando) return;
	
	CMatriz4x4 m;
	
	m.RotarY((double)z / 100.0);
	entidadactiva->matrizrotado *= m;
	DibujarMundo3d();
//	printf("Raton Movido Derecho + Control: %d\n", z);
}

void CMundo3d::RatonMovidoCen(int x, int y)
{
	if (revolucionando) return;
	
	CMatriz4x4 m;
	m.EscalarV(CambioCoordenadasCamaraAMundo(-(double)x/100.0,(double)y/100.0,0));
//	m.Escalar((double)x, (double)y, 1.0);

	entidadactiva->matrizescalado += m;
	DibujarMundo3d();
//	printf("Raton Movido Central: %d, %d\n", x, y);
}

void CMundo3d::RatonMovidoCenCtrl(int z)
{
	if (revolucionando) return;
	
	CMatriz4x4 m;

	m.EscalarV(CambioCoordenadasCamaraAMundo(0,0,(double)z/100.0));
//	m.Escalar(1.0, 1.0, (double)z);
	
	entidadactiva->matrizescalado += m;
	DibujarMundo3d();
//	printf("Raton Movido Central + Control: %d\n", z);
}

void CMundo3d::RatonPulsadoIzq(int x, int y)
{
	if (revolucionando)
	{
		pantalla->CapturarRaton();
		
		superficierevolucion.InsertarPunto2d(x, y);
		
		superficierevolucion.PintarRevolucion2d(framebuffer);
		pantalla->update();
		
		printf("Inicio Captura de Raton\n");
	}
	
	printf("Raton Pulsado Izquierdo: %d, %d - %d\n", x, y, interfaz->EntidadSeleccionada());
}

void CMundo3d::RatonPulsadoDer(int x, int y)
{
	if (revolucionando)
	{
		pantalla->SoltarRaton();
		revolucionando = 0;
		
		superficierevolucion.InsertarPunto2d(x, y);
		
		superficierevolucion.PintarRevolucion2d(framebuffer);
		pantalla->update();
		framebuffer->borde = black;
		
		char temp[50];
		sprintf(temp, "Objeto %d", nentidades);
		
		entidades[nentidades] = new CObjeto3d(temp);
		superficierevolucion.CrearSuperficieRevolucion((CObjeto3d *)entidades[nentidades], interfaz->meridianos, interfaz->radio);
		interfaz->InsertarEntidad(temp, nentidades);
		nentidades++;
		
		DibujarMundo3d();
		
		printf("Termino Captura de Raton para Revolucion: %d meris, %d radio\n",interfaz->meridianos, interfaz->radio);
	}
	
	printf("Raton Pulsado Derecho: %d, %d\n", x, y);
}

void CMundo3d::IniciarSuperficieRevolucion()
{
	revolucionando = 1;
	
	interfaz->MostrarBotonesTipo(ENTIDAD);
	superficierevolucion.Inicializar();
	
	framebuffer->ComenzarPintar();
	framebuffer->CambiarColor(red);
	framebuffer->Escribir(10,20,"MODO REVOLUCION:");
	framebuffer->CambiarColor(black);
	framebuffer->borde = red;
	framebuffer->TerminarPintar();
	pantalla->update();
//	framebuffer->ModoXor();
	
	printf("IniciarSuperficieRevolucion\n");
}

void CMundo3d::RatonMovido(int x, int y)
{
	if (revolucionando)
	{
		superficierevolucion.PintarRevolucion2d(framebuffer, x, y);
		pantalla->update();
//		printf("Raton Movido para Revolucion: %d, %d\n", x, y);
	}
	else
		printf("ERRORRaton Movido sin Revolucion: %d, %d\n", x, y);
}

void CMundo3d::CrearCamara()
{
	CObjeto3d *actual;
	CVertice3d *vertices;
	CTriangulo *triangulos;
	CVertice3d derecha, arriba, direccionvista;
	int nv, nt;
	
		actual = (CObjeto3d *) entidadactiva;
			vertices = actual->vertices;
			triangulos = actual->triangulos;
			direccionvista = actual->direccionvista;
			derecha = actual->derecha;
			arriba = actual->arriba;
			nv = actual->nvertices;
			nt = actual->ntriangulos;
	
	printf("Vertices{\n");
	for (int i = 0; i < nv; i++)
 		printf("{%.10f, %.10f, %.10f},\n", vertices[i].x, vertices[i].y, vertices[i].z);
	printf("}\n");
	
	printf("Triangulos{\n");
	for (int i = 0; i < nt; i++)
 		printf("{%d, %d, %d},\n", triangulos[i].a, triangulos[i].b, triangulos[i].c);
	printf("}\n");
	
	printf("NormalesTriangulos{\n");
	for (int i = 0; i < nv; i++)
 		printf("{%.10f, %.10f, %.10f},\n", triangulos[i].normal.x, triangulos[i].normal.y, triangulos[i].normal.z);
	printf("}\n");
}

void CMundo3d::CambiarEntidadActiva(int i)
{
	entidadactiva = entidades[i];
	interfaz->colorentidad->setBackgroundColor(entidadactiva->color);
	interfaz->colorentidad->update();
	interfaz->cbocultarentidad->setChecked(entidadactiva->ocultarentidad);
	interfaz->cbocultarcaras->setChecked(entidadactiva->ocultarcaras);
	interfaz->bgmodopintar->setButton(entidadactiva->modopintar);
	interfaz->bgmodosombreado->setButton(entidadactiva->modosombreado);
	interfaz->MostrarBotonesTipo(entidadactiva->tipo);
	printf("Entidad Cambiada: %d -> %s\n", i, entidadactiva->nombre);
}

void CMundo3d::OcultarEntidad(bool estado)
{
	entidadactiva->ocultarentidad = estado;
	printf("Ocultar Entidad: %d", estado);
	DibujarMundo3d();
}

void CMundo3d::OcultarCaras(bool estado)
{
	entidadactiva->ocultarcaras = estado;
	printf("Ocultar Caras: %d", estado);
	DibujarMundo3d();
}

void CMundo3d::CambiarModoPintar(int modopintar)
{
	entidadactiva->modopintar = modopintar;
	printf("Modo Pintar: %d\n", modopintar);
	DibujarMundo3d();
}

void CMundo3d::CambiarModoSombreado(int modosombreado)
{
	entidadactiva->modosombreado = modosombreado;
	printf("Modo Sombreado: %d\n", modosombreado);
	DibujarMundo3d();
}

void CMundo3d::CambiarColor()
{
	QColor temp(QColorDialog::getColor(entidadactiva->color, this, "Dialogo Color"));
	if (temp.isValid())
	{
		entidadactiva->color = temp;
		interfaz->colorentidad->setBackgroundColor(temp);
		interfaz->colorentidad->update();
		printf("Se cambio el color\n");

	}
	printf("Se llamo al dialogo color\n");
	DibujarMundo3d();
}

inline void OrdenarVerticesTriangulo(CTriangulo *triangulo, CVertice3d *vertices, int &sup, int &med, int &inf)
{
	if (vertices[triangulo->a].y >= vertices[triangulo->b].y)
	{
		sup = triangulo->a;
		med = triangulo->b;
	}
	else
	{
		sup = triangulo->b;
		med = triangulo->a;
	}
	
	if (vertices[med].y >= vertices[triangulo->c].y)
	{
		inf = triangulo->c;
	}
	else
	{
		if (vertices[sup].y >= vertices[triangulo->c].y)
		{
			inf = med;
			med = triangulo->c;
		}
		else
		{
			inf = med;
			med = sup;
			sup = triangulo->c;
		}
	}
}

void CMundo3d::PintarPixel(int x, int y, double z)
{
	double *zzbuffer;
	
	zzbuffer = zbuffer->Z(x, y);
	
	if (zzbuffer == 0) return;
	
	if (z >= *zzbuffer) return;

	*zzbuffer = z;
	framebuffer->PintarPixel(x, y);
}

void CMundo3d::DibujarMundo3d()
{
	CMatriz4x4 matrizmundo, mc, msc;
	CObjeto3d *actual;
	CVertice3d *vertices, *verticesmod, *verticesmod2, posicioncamara;
	CTriangulo *triangulos;
	CVertice3d derecha, arriba, profundidad, posicion;
	QColor color;
	double perspectiva;
	int sup, inf, med;
	
	zbuffer->Limpiar();
	framebuffer->ComenzarPintar();
	
	posicioncamara.VerticePorMatriz(&(camaraactiva->posicion), &(camaraactiva->matriztrasladado));
	posicioncamara *= -1;
	mc.Identidad();
	mc.TrasladarV(posicioncamara);
	mc *= camaraactiva->matrizrotado;
	mc *= camaraactiva->matrizcambiocoordenadas;
	//mc *= camaraactiva->matrizperspectiva;
	
	
	for (int i = 0; i < nentidades; i++)
	{
		if (entidades[i] == camaraactiva) continue;
		if (entidades[i]->ocultarentidad) continue;
		
		actual = (CObjeto3d *) entidades[i];
			vertices = actual->vertices;
			verticesmod = actual->verticesmod;
			verticesmod2 = actual->verticesmod2;
			triangulos = actual->triangulos;
			color = actual->color;

		// Color FLAT por defecto
		framebuffer->CambiarColor(color);
		
		// Calculamos la matriz de posicionamiento respecto a la camara del objeto
		matrizmundo.Identidad();
			// Respecto al mundo
			matrizmundo *= actual->matrizescalado;
			matrizmundo *= actual->matrizrotado;
			matrizmundo *= actual->matriztrasladado;
			// Respecto a la camara
			matrizmundo *= mc;

		// Si el objeto esta por detras de la camara no se pinta
		posicion.VerticePorMatriz(&actual->posicion, &matrizmundo);
		if (posicion.z <= 0.0) continue;
		
		// Multiplicamos los vertices del objeto por la matriz de vista
		for (int v = 0; v < actual->nvertices; v++)
		{
			verticesmod[v].VerticePorMatriz(&(actual->vertices[v]), &matrizmundo);
			
			verticesmod2[v].x = verticesmod[v].x;
			verticesmod2[v].y = verticesmod[v].y;
			verticesmod2[v].z = verticesmod[v].z;
			
			perspectiva = verticesmod[v].z == 0.0? 10000000000000.0 : (camaraactiva->d / verticesmod[v].z);
			verticesmod[v].x = verticesmod[v].x * perspectiva;
			verticesmod[v].y = verticesmod[v].y * perspectiva;
		}
		
		// Para cada triangulo del objeto
		for (int t = 0; t < actual->ntriangulos; t++)
		{
			//SI (OCULTARCARAS) CALCULAR PRODUCO ESCALAR <= 0 CONTINUE;
			if (actual->ocultarcaras == TRUE)
				if (triangulos[t].Oculto(verticesmod)) 
//				if (triangulos[t].Oculto(verticesmod)) 
					continue;
			
			//SI (FLAT) COLOR = CALCULAMOS COLOR PARA EL TRIANGULO ENTERO
			if (actual->modosombreado == FLAT)
			{
				//int zmedia = 700 - int(round((verticesmod[triangulos[t].a].z + verticesmod[triangulos[t].b].z + verticesmod[triangulos[t].c].z) / 3.0));
				//framebuffer->CambiarColor(actual->color.light(zmedia));

				triangulos[t].CalcularNormal(verticesmod2);
				triangulos[t].normal.Normalizar();
				
				CVertice3d luz, cero;
				cero.Establecer(0.0f, 0.0f, 0.0f);
				luz.Vector(&verticesmod2[triangulos[t].a], &cero);
				luz.Normalizar();
				
				double distancia = cero.Distancia(&verticesmod2[triangulos[t].a]);
				distancia = 1 / distancia;
				
				double coefdifuso = 500;
				double intensidad = distancia * coefdifuso * luz.ProductoEscalar(&(triangulos[t].normal));
				//printf("intensidad: %f\n", intensidad);
				if (intensidad < 0.0) intensidad *= -1.0;
				
				double r, g, b;
				r = actual->color.red();
				g = actual->color.green();
				b = actual->color.blue();
				
				r *= intensidad;
				if (r > 255.0) r = 255.0;
				if (r < 0.0) r = 0.0;
				g *= intensidad;
				if (g > 255.0) g = 255.0;
				if (g < 0.0) g = 0.0;
				b *= intensidad;
				if (b > 255.0) b = 255.0;
				if (b < 0.0) b = 0.0;
				
				framebuffer->CambiarColor(QColor(int(round(r)), int(round(g)),int(round(b))));

			}
			
			// Pintar los puntos
			if (actual->modopintar == PUNTOS)
			{
				PintarPixel(int(round(verticesmod[triangulos[t].a].x)), int(round(verticesmod[triangulos[t].a].y)), verticesmod[triangulos[t].a].z);
				PintarPixel(int(round(verticesmod[triangulos[t].b].x)), int(round(verticesmod[triangulos[t].b].y)), verticesmod[triangulos[t].b].z);
				PintarPixel(int(round(verticesmod[triangulos[t].c].x)), int(round(verticesmod[triangulos[t].c].y)), verticesmod[triangulos[t].c].z);
				continue;
			}
			
			//ORDENAMOS LOS TRIANGULOS EN EJEy SUPERIOR > MEDIO > INFERIOR
			OrdenarVerticesTriangulo(&(triangulos[t]), verticesmod, sup, med, inf);
			
			//CALCULAMOS PENDIENTES DE TODO LO NECESARIO:
				//VARIACION DE LAS X RESPECTO A BAJAR POR Y
				//VARIACION DE LAS Z RESPECTO A BAJAR POR Y
				//VARIACION DE LAS N RESPECTO A BAJAR POR Y

			int ysup, ymed, yinf, temp;
			ysup = (int)round(verticesmod[sup].y);
			ymed = (int)round(verticesmod[med].y);
			yinf = (int)round(verticesmod[inf].y);
			
			// Lado del vertice superior con el del medio
			double xsum1, zsum1, x1, z1;
			int x1i;
			xsum1 = (verticesmod[sup].x - verticesmod[med].x);
			zsum1 = (verticesmod[sup].z - verticesmod[med].z);
			temp = ysup - ymed;
			if (temp == 0) 
			{
				x1 = verticesmod[med].x;
				z1 = verticesmod[med].z;
			}
			else
			{
				xsum1 /= (double)temp;
				zsum1 /= (double)temp;
				x1 = verticesmod[sup].x;
				z1 = verticesmod[sup].z;
			}
			
			// Lado del vertice superior con el inferior
			double xsum2, zsum2, x2, z2;
			int x2i;
			xsum2 = (verticesmod[sup].x - verticesmod[inf].x);
			zsum2 = (verticesmod[sup].z - verticesmod[inf].z);
			temp = ysup - yinf;
			if (temp == 0) 
			{
				x2 = verticesmod[inf].x;
				z2 = verticesmod[inf].z;
			}
			else
			{
				xsum2 /= (double)temp;
				zsum2 /= (double)temp;
				x2 = verticesmod[sup].x;
				z2 = verticesmod[sup].z;
			}

			// Para cada linea del triangulo
			int xizqant = 16000;
			int xderant = -16000;
			do
			{
				x1i = (int)round(x1);
				x2i = (int)round(x2);
				
/*				// Pintar con lineas
				if (actual->modopintar == LINEAS)
				{
					PintarPixel(x1i, ysup, z1);
					PintarPixel(x2i, ysup, z2);
				}
				// Pintar con relleno
				else
				{*/
					double zsum, zizq, zder;
					int xizq, xder;
					
					// Ordenamos los puntos de la linea del triangulo
					if (x1i <= x2i)
					{
						xizq = x1i;
						xder = x2i;
						
						zizq = z1;
						zder = z2;
					}
					else
					{
						xizq = x2i;
						xder = x1i;
						
						zizq = z2;
						zder = z1;
					}
					
					// Calculamos la variacion de Z en la linea
					zsum = zder - zizq;
					temp = xder - xizq;
					if (temp != 0)
						zsum /= (double)temp;
					
					// Para cada linea del triangulo
					for (int i = xizq; i <= xder; i++)
					{
						if (actual->modosombreado == GOURAUD)
						{
//							int zmedia = 1000 - int(round(zizq));
//							framebuffer->CambiarColor(actual->color.light(zmedia));
						}
						
						if (actual->modopintar == LINEAS)
						{
//							if (ysup >= ymed)
							if ((i <= xizqant) || (i >= xderant))
								PintarPixel(i, ysup, zizq);
//							else
//							if ((i >= xizqant) || (i <= xderant))
//								PintarPixel(i, ysup, zizq);
						}
						else
							PintarPixel(i, ysup, zizq);
						
						zizq += zsum;
					}
					
					xizqant = xizq;
					xderant = xder;
//				}
				
				// Llegamos a la mitad del triangulo
				if (ysup == ymed)
				{
					temp = ymed - yinf;
					if (temp == 0) 
					{
						xsum1 = (verticesmod[med].x - verticesmod[inf].x);
						zsum1 = (verticesmod[med].z - verticesmod[inf].z);
					}
					else
					{
						xsum1 = (verticesmod[med].x - verticesmod[inf].x) / double(temp);
						zsum1 = (verticesmod[med].z - verticesmod[inf].z) / double(temp);
					}
				}
				
				x1 -= xsum1;
				z1 -= zsum1;
				x2 -= xsum2;
				z2 -= zsum2;
				ysup--;
			} while (ysup >= yinf);
		}
	}

	framebuffer->borde = black;
	framebuffer->TerminarPintar();
	pantalla->update();
//	printf("MUNDO PINTADO\n");
}

