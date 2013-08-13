#include "cvertice3d.h"
#include "cmatriz4x4.h"
#include "ctriangulo.h"

CVertice3d *CVertice3d::operator *=(CMatriz4x4 m)
{
		CPuntoFijo t1, t2, t3, t4;
	
		t1 = x * m.m11 + y * m.m21 + z * m.m31 + w * m.m41;
		t2 = x * m.m12 + y * m.m22 + z * m.m32 + w * m.m42;
		t3 = x * m.m13 + y * m.m23 + z * m.m33 + w * m.m43;
		t4 = x * m.m14 + y * m.m24 + z * m.m34 + w * m.m44;
	
		if (t4 == 1.0)
		{
			x = t1; y = t2; z = t3;
		}
		else
		{
			t4 = 1 / t4;
			x = t1 * t4; y = t2 * t4; z = t3 * t4;
		}
		w = 1.0;
		return this;
}

void CVertice3d::VerticePorMatriz(CVertice3d *v, CMatriz4x4 *m)
{
		CPuntoFijo t;
	
		x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + v->w * m->m41;
		y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + v->w * m->m42;
		z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + v->w * m->m43;
		w = v->x * m->m14 + v->y * m->m24 + v->z * m->m34 + v->w * m->m44;
	
		if (w != 1.0)
		{
			t = w == 0? 10000000000000.0 : 1.0 / w;
			x *= t; y *= t; z *= t;
			w = 1.0;
		}
}
