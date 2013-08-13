#include "cmatriz4x4.h"
#include "cvertice3d.h"

void CMatriz4x4::EscalarV(CVertice3d e)
{
	m11 = e.x ; m12 = 0.0 ; m13 = 0.0 ; m14 = 0.0;
	m21 = 0.0 ; m22 = e.y ; m23 = 0.0 ; m24 = 0.0;
	m31 = 0.0 ; m32 = 0.0 ; m33 = e.z ; m34 = 0.0;
	m41 = 0.0 ; m42 = 0.0 ; m43 = 0.0 ; m44 = 1.0;
}
	
void CMatriz4x4::TrasladarV(CVertice3d t)
{
	m11 = 1.0 ; m12 = 0.0 ; m13 = 0.0 ; m14 = 0.0;
	m21 = 0.0 ; m22 = 1.0 ; m23 = 0.0 ; m24 = 0.0;
	m31 = 0.0 ; m32 = 0.0 ; m33 = 1.0 ; m34 = 0.0;
	m41 = t.x ; m42 = t.y ; m43 = t.z ; m44 = 1.0;
}

void CMatriz4x4::CambioSistemaCoordenadas(CVertice3d u, CVertice3d v, CVertice3d w)
{
	m11 = u.x ; m12 = v.x ; m13 = w.x ; m14 = 0.0;
	m21 = u.y ; m22 = v.y ; m23 = w.y ; m24 = 0.0;
	m31 = u.z ; m32 = v.z ; m33 = w.z ; m34 = 0.0;
	m41 = 0.0 ; m42 = 0.0 ; m43 = 0.0 ; m44 = 1.0;
}
