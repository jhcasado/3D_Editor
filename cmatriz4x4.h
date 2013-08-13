#ifndef CMATRIZ4X4_H
#define CMATRIZ4X4_H

#include <stdio.h>

#include "cpuntofijo.h"
#include "mate.h"

class CVertice3d;
//#include "cvertice3d.h"

class CMatriz4x4
{
	public:
	
	CMatriz4x4 () {}
	~CMatriz4x4 () {}
	
	CPuntoFijo m11, m12, m13, m14;
	CPuntoFijo m21, m22, m23, m24;
	CPuntoFijo m31, m32, m33, m34;
	CPuntoFijo m41, m42, m43, m44;

	void Identidad()
	{
	m11 = 1.0; m12 = 0.0; m13 = 0.0; m14 = 0.0;
	m21 = 0.0; m22 = 1.0; m23 = 0.0; m24 = 0.0;
	m31 = 0.0; m32 = 0.0; m33 = 1.0; m34 = 0.0;
	m41 = 0.0; m42 = 0.0; m43 = 0.0; m44 = 1.0;
	}
	
	void Establecer(CMatriz4x4 b)
	{
	m11 = b.m11; m12 = b.m12; m13 = b.m13; m14 = b.m14;
	m21 = b.m21; m22 = b.m22; m23 = b.m23; m24 = b.m24;
	m31 = b.m31; m32 = b.m32; m33 = b.m33; m34 = b.m34;
	m41 = b.m41; m42 = b.m42; m43 = b.m43; m44 = b.m44;
	}
	
	void Traspuesta(CMatriz4x4 b)
	{
	m11 = b.m11; m12 = b.m21; m13 = b.m31; m14 = b.m41;
	m21 = b.m12; m22 = b.m22; m23 = b.m32; m24 = b.m42;
	m31 = b.m13; m32 = b.m23; m33 = b.m33; m34 = b.m43;
	m41 = b.m14; m42 = b.m24; m43 = b.m34; m44 = b.m44;
	}

	CMatriz4x4 *operator +=(CMatriz4x4 b)
	{
	m11 += b.m11; m22 += b.m22; m33 += b.m33; return this;
	}
	
	CMatriz4x4 *operator *=(CMatriz4x4 b)
	{
	CPuntoFijo t1, t2, t3, t4;
	
	t1 = m11 * b.m11 + m12 * b.m21 + m13 * b.m31 + m14 * b.m41; 
	t2 = m11 * b.m12 + m12 * b.m22 + m13 * b.m32 + m14 * b.m42;
	t3 = m11 * b.m13 + m12 * b.m23 + m13 * b.m33 + m14 * b.m43;
	t4 = m11 * b.m14 + m12 * b.m24 + m13 * b.m34 + m14 * b.m44;
	m11 = t1; 
	m12 = t2;
	m13 = t3;
	m14 = t4;
	
	t1 = m21 * b.m11 + m22 * b.m21 + m23 * b.m31 + m24 * b.m41; 
	t2 = m21 * b.m12 + m22 * b.m22 + m23 * b.m32 + m24 * b.m42; 
	t3 = m21 * b.m13 + m22 * b.m23 + m23 * b.m33 + m24 * b.m43;
	t4 = m21 * b.m14 + m22 * b.m24 + m23 * b.m34 + m24 * b.m44;
	m21 = t1; 
	m22 = t2; 
	m23 = t3;
	m24 = t4;
	
	t1 = m31 * b.m11 + m32 * b.m21 + m33 * b.m31 + m34 * b.m41;
	t2 = m31 * b.m12 + m32 * b.m22 + m33 * b.m32 + m34 * b.m42;
	t3 = m31 * b.m13 + m32 * b.m23 + m33 * b.m33 + m34 * b.m43;
	t4 = m31 * b.m14 + m32 * b.m24 + m33 * b.m34 + m34 * b.m44;
	m31 = t1;
	m32 = t2;
	m33 = t3;
	m34 = t4;
	
	t1 = m41 * b.m11 + m42 * b.m21 + m43 * b.m31 + m44 * b.m41;
	t2 = m41 * b.m12 + m42 * b.m22 + m43 * b.m32 + m44 * b.m42;
	t3 = m41 * b.m13 + m42 * b.m23 + m43 * b.m33 + m44 * b.m43;
	t4 = m41 * b.m14 + m42 * b.m24 + m43 * b.m34 + m44 * b.m44;
	m41 = t1;
	m42 = t2;
	m43 = t3;
	m44 = t4;
	
	return this;
	}

	void RotarX(CPuntoFijo rx)
	{
	m11 = 1.0; m12 = 0.0       ; m13 = 0.0        ; m14 = 0.0;
	m21 = 0.0; m22 = COSENO(rx); m23 = SENO(rx)  ; m24 = 0.0;
	m31 = 0.0; m32 = -SENO(rx) ; m33 = COSENO(rx); m34 = 0.0;
	m41 = 0.0; m42 = 0.0       ; m43 = 0.0        ; m44 = 1.0;
	}

	void RotarY(CPuntoFijo ry)
	{
	m11 = COSENO(ry); m12 = 0.0; m13 = -SENO(ry) ; m14 = 0.0;
	m21 = 0.0       ; m22 = 1.0; m23 = 0.0       ; m24 = 0.0;
	m31 = SENO(ry)  ; m32 = 0.0; m33 = COSENO(ry); m34 = 0.0;
	m41 = 0.0       ; m42 = 0.0; m43 = 0.0       ; m44 = 1.0;
	}

	void RotarZ(CPuntoFijo rz)
	{
	m11 = COSENO(rz); m12 = SENO(rz)  ; m13 = 0.0; m14 = 0.0;
	m21 = -SENO(rz) ; m22 = COSENO(rz); m23 = 0.0; m24 = 0.0;
	m31 = 0.0       ; m32 = 0.0       ; m33 = 1.0; m34 = 0.0;
	m41 = 0.0       ; m42 = 0.0       ; m43 = 0.0; m44 = 1.0;
	}

	void Escalar(CPuntoFijo ex, CPuntoFijo ey, CPuntoFijo ez)
	{
	m11 = ex ; m12 = 0.0; m13 = 0.0; m14 = 0.0;
	m21 = 0.0; m22 = ey ; m23 = 0.0; m24 = 0.0;
	m31 = 0.0; m32 = 0.0; m33 = ez ; m34 = 0.0;
	m41 = 0.0; m42 = 0.0; m43 = 0.0; m44 = 1.0;
	}

	void EscalarV(CVertice3d e);
	
	void Trasladar(CPuntoFijo tx, CPuntoFijo ty, CPuntoFijo tz)
	{
	m11 = 1.0; m12 = 0.0; m13 = 0.0; m14 = 0.0;
	m21 = 0.0; m22 = 1.0; m23 = 0.0; m24 = 0.0;
	m31 = 0.0; m32 = 0.0; m33 = 1.0; m34 = 0.0;
	m41 = tx ; m42 = ty ; m43 = tz ; m44 = 1.0;
	}

	void TrasladarV(CVertice3d t);
	
	void CambioSistemaCoordenadas(CVertice3d u, CVertice3d v, CVertice3d w);
		
	void Perspectiva(CPuntoFijo d)
	{
	m11 = 1.0; m12 = 0.0; m13 = 0.0; m14 = 0.0;
	m21 = 0.0; m22 = 1.0; m23 = 0.0; m24 = 0.0;
	m31 = 0.0; m32 = 0.0; m33 = 1.0; m34 = 1 / d;
	m41 = 0.0; m42 = 0.0; m43 = 0.0; m44 = 0.0;
	}
	
	void Mostrar()
	{
	printf("%2.6f, %2.6f, %2.6f, %2.6f\n"  ,m11, m12, m13, m14);
	printf("%2.6f, %2.6f, %2.6f, %2.6f\n"  ,m21, m22, m23, m24);
	printf("%2.6f, %2.6f, %2.6f, %2.6f\n"  ,m31, m32, m33, m34);
	printf("%2.6f, %2.6f, %2.6f, %2.6f\n\n",m41, m42, m43, m44);
	}
/*	
	operator *=(CPuntoFijo f)
	{
	m11 *= f; m12 *= f; m13 *= f; m14 *= f;
	m21 *= f; m22 *= f; m23 *= f; m24 *= f;
	m31 *= f; m32 *= f; m33 *= f; m34 *= f;
	m41 *= f; m42 *= f; m43 *= f; m44 *= f;
	}
*/
};

#endif
