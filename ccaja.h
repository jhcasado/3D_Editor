#ifndef CCAJA_H
#define CCAJA_H

#include "cvertice3d.h"

class CCaja
{
	public:
	
	CCaja () : min(0,0,0), max(0,0,0) {}
	~CCaja () {}
	
	CVertice3d min, max;
	
	void IntroducirVertice3d(const CVertice3d& n)
	{
		if (min.x > n.x)
			min.x = n.x;
		if (min.y > n.y)
			min.y = n.y;
		if (min.z > n.z)
			min.z = n.z;

		if (max.x < n.x)
			max.x = n.x;
		if (max.y < n.y)
			max.y = n.y;
		if (max.z < n.z)
			max.z = n.z;
	}

	CVertice3d Centro()
	{
		return CVertice3d((max.x - min.x) / 2, (max.y - min.y) / 2, (max.z - min.z) / 2);
	}
	
};

#endif
