#include "rtcutil.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace sepwind
{

void __stdcall MAT_IDENT(MATRIX3D* pMatrix3D)
{
	pMatrix3D->e[0] = 1.0; pMatrix3D->e[1] = 0.0; pMatrix3D->e[2] = 0.0;
	pMatrix3D->e[3] = 0.0; pMatrix3D->e[4] = 1.0; pMatrix3D->e[5] = 0.0;
	pMatrix3D->e[6] = 0.0; pMatrix3D->e[7] = 0.0; pMatrix3D->e[8] = 1.0;
}

MATRIX3D __stdcall MAT_ROTATE(double angle)
{
	MATRIX3D m;
	MAT_IDENT(&m);
	double rad = angle * 180.0 / M_PI;
	m.e[0] = m.e[4]= cos(rad);
	m.e[1] = -sin(rad);
	m.e[3] = -m.e[1];	
	return m;
}

MATRIX3D __stdcall MAT_TRANSIT(double dx, double dy)
{
	MATRIX3D m;
	MAT_IDENT(&m);
	m.e[2] = dx;
	m.e[5] = dy;	
	return m;
}

MATRIX3D __stdcall MAT_MULTI(const MATRIX3D* pLeftMat, const MATRIX3D* pRightMat)
{
	MATRIX3D m = *pLeftMat;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				m.e[i * 3 + j] += m.e[i * 3 + k] * pRightMat->e[j + k * 3];

	return m;
}


}//namespace