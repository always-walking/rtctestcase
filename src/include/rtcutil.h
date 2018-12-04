/*
 * utility functions
 * 
 * powered by sepwind@gmail.com
 * http://sepwind.blogspot.com
 *
 *
 */

#ifndef RTCUTIL_H
#define RTCUTIL_H

#include <windows.h>

namespace sepwind
{

typedef struct
{
	double e[9];
	///////////
	// 0 1 2 //
	// 3 4 5 //
	// 6 7 8 //
	///////////
}MATRIX3D;

void __stdcall MAT_IDENT(MATRIX3D* pMatrix3D);	/// identity matrix
MATRIX3D __stdcall MAT_ROTATE(double angle);	/// rotate matrix
MATRIX3D __stdcall MAT_TRANSIT(double dx, double dy);	/// transit matrix
MATRIX3D __stdcall MAT_MULTI(const MATRIX3D* pLeftMat, const MATRIX3D* pRightMat);	/// M=A*B

}//namespace


#endif