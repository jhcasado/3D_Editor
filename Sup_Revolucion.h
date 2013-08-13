#ifndef SUP_REVOLUCION_H
#define SUP_REVOLUCION_H

#include <stdio.h>
#include <math.h>

#include "cvertice3d.h"

#define	TRUE	1
#define	FALSE	0



double RotacionTotalDUPLICADA[4][4];

#define	R00	N1*N1 +(1-N1*N1)*COS
#define	R01	N1*N2*(1-COS) +N3*SIN
#define	R02	N1*N3*(1-COS) -N2*SIN
#define	R03	0

#define	R10	N1*N2*(1-COS) - N3*SIN
#define	R11	N2*N2 +(1 -N2*N2)*COS
#define	R12	N2*N3*(1-COS) +N1*SIN
#define	R13	0

#define	R20	N1*N3*(1-COS) +N2*SIN
#define	R21	N2*N3*(1-COS) -N1*SIN
#define	R22	N3*N3 +(1-N3*N3)*COS
#define	R23	0

#define	R30	E0x -E0x*(N1*N1 +(1-N1*N1)*COS) -E0z*(N1*N3*(1-COS) +N2*SIN) -E0y*(N1*N2*(1-COS) -N3*SIN)
#define	R31	E0y -E0y*(N2*N2 +(1-N2*N2)*COS) -E0z*(N2*N3*(1-COS) -N1*SIN) -E0x*(N1*N2*(1-COS) +N3*SIN)
#define	R32	E0z -E0z*(N3*N3 +(1-N3*N3)*COS) -E0x*(N1*N3*(1-COS) -N2*SIN) -E0y*(N2*N3*(1-COS) +N1*SIN)
#define	R33	1


void CalcMatriz_RotacionTotalDUPLICADA(double Alfa, CVertice3d *e0,CVertice3d *e1)
{
register	double	COS, SIN;
register	int	E0x,E0y,E0z;
register	double	N1,N2,N3; 

    /* Inicializacion o calculo de cantidades */
    COS =	cos(Alfa);
    SIN =	sin(Alfa);
    E0x =	(int)e0->x;
    E0y =	(int)e0->y;
    E0z =	(int)e0->z;
    N1 =	e1->x -e0->x;
    N2 =	e1->y -e0->y;
    N3 =	e1->z -e0->z;
    {	register double	Modulo;
	Modulo= sqrt(N1*N1 +N2*N2 +N3*N3);
	N1 =	N1 / Modulo;
	N2 =	N2 / Modulo;
	N3 =	N3 / Modulo;
    }
    RotacionTotalDUPLICADA[0][0]= R00;  RotacionTotalDUPLICADA[0][1]= R01;  RotacionTotalDUPLICADA[0][2]= R02;  RotacionTotalDUPLICADA[0][3]= R03;
    RotacionTotalDUPLICADA[1][0]= R10;  RotacionTotalDUPLICADA[1][1]= R11;  RotacionTotalDUPLICADA[1][2]= R12;  RotacionTotalDUPLICADA[1][3]= R13;
    RotacionTotalDUPLICADA[2][0]= R20;  RotacionTotalDUPLICADA[2][1]= R21;  RotacionTotalDUPLICADA[2][2]= R22;  RotacionTotalDUPLICADA[2][3]= R23;
    RotacionTotalDUPLICADA[3][0]= R30;  RotacionTotalDUPLICADA[3][1]= R31;  RotacionTotalDUPLICADA[3][2]= R32;  RotacionTotalDUPLICADA[3][3]= R33;
}



void VectorPorMatrizDUPLICADA(CVertice3d *Punto, double Matriz[4][4])
{
    register double	x,y,z, h;


	x = Punto->x * Matriz[0][0]   +   Punto->y * Matriz[1][0]   +   Punto->z * Matriz[2][0]   +   1 * Matriz[3][0];
	y = Punto->x * Matriz[0][1]   +   Punto->y * Matriz[1][1]   +   Punto->z * Matriz[2][1]   +   1 * Matriz[3][1];
	z = Punto->x * Matriz[0][2]   +   Punto->y * Matriz[1][2]   +   Punto->z * Matriz[2][2]   +   1 * Matriz[3][2];
	h = Punto->x * Matriz[0][3]   +   Punto->y * Matriz[1][3]   +   Punto->z * Matriz[2][3]   +   1 * Matriz[3][3];	/* Dejamos esta ultimo producto por si aplicamos un SOBREescalado */

	if( h!=1 ) {	/* Para las proyecciones si HAY QUE TENER EN CUENTA que varia la 'h': cuarta componente de un punto3d */
		x /= h;
		y /= h;
		z /= h;
	}
	Punto->x=x;
	Punto->y=y;
	Punto->z=z;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */



#define	MEMO_ERR						\
{								\
	sprintf(error,"No hay memoria disponible.");		\
	return(NULL);						\
}								\


CVertice3d *Sup_Revolucion(int nptos,CVertice3d *ptos, int nMeridianos,CVertice3d *e0, CVertice3d *e1, char *error)
{
CVertice3d  *Matriz;
int		i,ii, N;
double		AlfaTotal;



    if( (e0->x == e1->x)  &&  (e0->y == e1->y)  &&  (e0->z == e1->z) ){
	sprintf(error, " Las tres coordenadas que definen el eje de rotacion son iguales, definen infinitas rectas y no solo una.");
	return(NULL);
    }

    AlfaTotal=   ( 2*M_PI / (nMeridianos/*-1*/) )*1;
    CalcMatriz_RotacionTotalDUPLICADA( AlfaTotal, e0,e1 );

    N = (nMeridianos+1) * nptos;	/* Se ha incluido un meridiano mas para enlazar la Malla de rotacion */
    if( (Matriz=(CVertice3d*)calloc( N, sizeof(CVertice3d )))==NULL )   MEMO_ERR


    memcpy( Matriz, ptos, nptos*sizeof(CVertice3d) );

	for( i=1; i<=nMeridianos-1; i++){
	    memcpy( &(Matriz[nptos*i]), &(Matriz[nptos*(i-1)]), nptos*sizeof(CVertice3d) );

	    for( ii=0; ii<nptos; ii++)
		VectorPorMatrizDUPLICADA( &(Matriz[nptos*i +ii]), RotacionTotalDUPLICADA );
	}
    memcpy( &(Matriz[nptos*nMeridianos]), ptos, nptos*sizeof(CVertice3d) );

return(Matriz);
}

#endif
