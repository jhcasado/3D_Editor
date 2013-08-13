#include <stdio.h>

#include "csuperficierevolucion.h"
#include "Sup_Revolucion.h"

	void CSuperficieRevolucion::InsertarPunto2d(int x, int y) 
	{
		puntos2d[npuntos2d].x = x;
		puntos2d[npuntos2d].y = y;
		npuntos2d++;
		puntos2d[npuntos2d].x = x;
		puntos2d[npuntos2d].y = y;
		if (npuntos2d == 1)
		{
			xmax = x;
			ymin = y;
			ymax = y;
			npuntos2d++;
			puntos2d[npuntos2d].x = x;
			puntos2d[npuntos2d].y = y;
		}
		else
		if (xmax < puntos2d[npuntos2d].x)
		{
			xmax = puntos2d[npuntos2d].x;
			puntos2d[0].x = xmax;
		}
		else
			puntos2d[npuntos2d].x = xmax;
		
		if (y > ymax)
			ymax = y;
		
		if (y < ymin)
			ymin = y;
	}
	
	
	void CSuperficieRevolucion::PintarRevolucion2d(CFrameBuffer *framebuffer, int x, int y)
	{
		framebuffer->ComenzarPintar();

		framebuffer->CambiarColor(Qt::red);
		framebuffer->Escribir(10,20,"MODO REVOLUCION:");
		framebuffer->CambiarColor(Qt::black);
				
		if (xmax <= x)
		{
			framebuffer->PintarLinea(x, puntos2d[0].y, puntos2d[1].x, puntos2d[1].y);
			
			framebuffer->PintarLinea(x, puntos2d[0].y, x, y);
		}
		else
		{
			framebuffer->PintarLinea(x, y, xmax, y);
			framebuffer->PintarLinea(puntos2d[0].x, puntos2d[0].y, xmax, y);
			
			framebuffer->PintarLinea(puntos2d[0].x, puntos2d[0].y, puntos2d[1].x, puntos2d[1].y);
		}
			
		for (int i = 1; i < npuntos2d - 1; i++)
			framebuffer->PintarLinea(puntos2d[i].x, puntos2d[i].y, puntos2d[i+1].x, puntos2d[i+1].y);
		
		framebuffer->PintarLinea(puntos2d[npuntos2d-1].x, puntos2d[npuntos2d-1].y, x, y);
	
		framebuffer->TerminarPintar();
	}
	
	
	void CSuperficieRevolucion::PintarRevolucion2d(CFrameBuffer *framebuffer)
	{
		for (int i = 0; i < npuntos2d; i++)
			framebuffer->PintarLinea(puntos2d[i].x, puntos2d[i].y, puntos2d[i+1].x, puntos2d[i+1].y);
		framebuffer->PintarLinea(puntos2d[0].x, puntos2d[0].y, puntos2d[npuntos2d].x, puntos2d[npuntos2d].y);
	}
	
	
	void CSuperficieRevolucion::VolcarPuntos2dEn3d(int radio)
	{
		int ini, fin, ymed, temp;
		
		ymed = (ymax + ymin) / 2;
		
		if ((puntos2d[0].x == puntos2d[1].x) && (puntos2d[0].y == puntos2d[1].y))
			ini = 1;
		else
			ini = 0;
		
		if ((puntos2d[npuntos2d - 1].x == puntos2d[npuntos2d].x) && (puntos2d[npuntos2d - 1].y == puntos2d[npuntos2d].y))
			fin = npuntos2d - 1;
		else
			fin = npuntos2d;
		
		if (puntos2d[0].y < puntos2d[npuntos2d].y)
			temp = 1;
		else
		{
			temp = ini;
			ini = fin;
			fin = temp;
			temp = -1;
		}
			
		npuntos3d = 0;
		for (int i = ini; i != (fin + temp); i+=temp)
		{
			puntos3d[npuntos3d].Establecer(puntos2d[i].x - xmax - radio, 0, puntos2d[i].y - ymed);
			npuntos3d++;
		}
	}
	
	
	void CSuperficieRevolucion::CrearSuperficieRevolucion(CObjeto3d *obj, int meridianos, int radio) 
	{
		char error[250];
		int triangulospormeridiano;
		CVertice3d e1(0.0, 0.0, 1.0), e2(0.0,0.0,0.0);
		
		printf("CREACION SUPERFICIE REVOLUCION 1\n");
		
		VolcarPuntos2dEn3d(radio);
		if (radio != 0)
		{
			puntos3d[npuntos3d].Establecer(puntos3d[0].x, 0.0, puntos3d[0].z);
			npuntos3d++;
		}
		//vertices = Sup_Revolucion(npuntos3d, puntos3d, meridianos, &(puntos3d[0]), &(puntos3d[npuntos3d-1]), error );
		vertices = Sup_Revolucion(npuntos3d, puntos3d, meridianos, &e1, &e2, error );
		nvertices = npuntos3d * (meridianos + 1);
		triangulospormeridiano = (npuntos3d - 2) * 2;
		//triangulos = new CTriangulo[triangulospormeridiano * meridianos];
		triangulos = new CTriangulo[(npuntos3d - 1) * 2 * meridianos];
		ntriangulos = 0;
		
		printf("CREACION SUPERFICIE REVOLUCION 2: np(%d) nv(%d) ntm(%d)\n",npuntos3d,nvertices,triangulospormeridiano);
		for (int i = 0; i < meridianos; i++)
		{
			for (int v = 0; v < (npuntos3d - 1)/*((triangulospormeridiano - 2) / 2)*/; v++)
			{
/*				triangulos[ntriangulos].a = (npuntos3d * i) + v + 2;
				triangulos[ntriangulos].b = (npuntos3d * i) + v + 1;
				triangulos[ntriangulos].c = (npuntos3d * (i+1)) + v + 1;
				triangulos[ntriangulos].normal.NormalTriangulo(&(triangulos[ntriangulos]), vertices);
				ntriangulos++;
			
				triangulos[ntriangulos].a = (npuntos3d * (i+1)) + v + 1;
				triangulos[ntriangulos].b = (npuntos3d * (i+1)) + v + 2;
				triangulos[ntriangulos].c = (npuntos3d * i) + v + 2;
				triangulos[ntriangulos].normal.NormalTriangulo(&(triangulos[ntriangulos]), vertices);
				ntriangulos++;
*/
				triangulos[ntriangulos].a = (npuntos3d * i) + v + 1;
				triangulos[ntriangulos].b = (npuntos3d * i) + v + 0;
				triangulos[ntriangulos].c = (npuntos3d * (i+1)) + v + 0;
				triangulos[ntriangulos].CalcularNormal(vertices);
				ntriangulos++;
			
				triangulos[ntriangulos].a = (npuntos3d * i) + v + 1;
				triangulos[ntriangulos].b = (npuntos3d * (i+1)) + v + 0;
				triangulos[ntriangulos].c = (npuntos3d * (i+1)) + v + 1;
				triangulos[ntriangulos].CalcularNormal(vertices);
				ntriangulos++;
				
/*				triangulos[ntriangulos].a = (npuntos3d * (i+1)) + v + 0;
				triangulos[ntriangulos].b = (npuntos3d * (i+1)) + v + 1;
				triangulos[ntriangulos].c = (npuntos3d * i) + v + 1;
				triangulos[ntriangulos].CalcularNormal(vertices);
				ntriangulos++;*/
			}
/*			triangulos[ntriangulos].a = (npuntos3d * i) + 1;
			triangulos[ntriangulos].b = (npuntos3d * i);
			triangulos[ntriangulos].c = (npuntos3d * (i+1)) + 1;
			triangulos[ntriangulos].normal.NormalTriangulo(&(triangulos[ntriangulos]), vertices);
			ntriangulos++;
			
			triangulos[ntriangulos].a = (npuntos3d * (i+1)) + npuntos3d - 2;
			triangulos[ntriangulos].b = (npuntos3d * (i+1)) + npuntos3d - 1;
			triangulos[ntriangulos].c = (npuntos3d * i) + npuntos3d - 2;
			triangulos[ntriangulos].normal.NormalTriangulo(&(triangulos[ntriangulos]), vertices);
			ntriangulos++;
*/		}
	printf("CREACION SUPERFICIE REVOLUCION 3\n");
	
	obj->vertices = vertices;
	obj->verticesmod = new CVertice3d[nvertices];
	obj->verticesmod2 = new CVertice3d[nvertices];
	obj->triangulos = triangulos;
	obj->nvertices = nvertices;
	obj->ntriangulos = ntriangulos;
	if (ntriangulos == triangulospormeridiano * meridianos)
		printf("NUMERO DE TRIANGULOS ENCONTRADOS CORRECTO\n");
	//FALTAN CALCULAR NORMALES DE LOS VERTICES PROMEDIANDO SUS TRIANGULOS ADYACENTES
	}

