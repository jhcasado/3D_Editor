#ifndef MATE_H
#define MATE_H

#include <math.h>

#include "cpuntofijo.h"

typedef struct{
	int x, y;
	double z;
} TV2D;

inline CPuntoFijo SENO(CPuntoFijo a)
{
	return sin(a);
} 

inline CPuntoFijo COSENO(CPuntoFijo a)
{
	return cos(a);
} 

#endif
