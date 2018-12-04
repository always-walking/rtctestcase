/*********************************************************************************
*                                                                                *
*                       RTC3 / 4 / 5 / 6 TESTCASE PROGRAM                        *
*                                                                                *
*                                                                                *
*                                                                                *
* 1. Descriptions                                                                *
*  Simple way to use scanlab's rtc controller to control laser and               *
*  scanner(galvanometers) via sample demo programs                               *
*                                                                                *
*                                                                                *
* 2. Author                                                                      *
*  hong chan, choi(sepwind@gmail.com)                                            *
*  homepage : http://sepwind.blogspot.com                                        *
*  git hub : https://github.com/sepwind/rtctestcase                              *
*  git repository : https://github.com/sepwind/rtctestcase.git                   *
*                                                                                *
*                                                                                *
* 3. Copyrights                                                                  *
*  GNU General Public License version 3.0 (GPLv3)                                *
*                                                                                *
*                                                                                *
* 4. Version history                                                             *
*  v0.1 2017.4.11  first release                                                 *
*  v0.2 2018.11.added) rtc6 / rtc6 for ethernet                                  *
*                  added) double buffered by automatically for massive data      *
*  v0.3	2018.11.6  added) 3d option(varioscan)                                   *
*  v0.4 2018.11.13 added) marking on the fly interface / measurement             *
*  v0.5 2018.12.4  added) push/pop 3x3 matrix operations                         *
*                  fixed) get measurement data size bug                          *
*                                                                                *
**********************************************************************************/

#include "include\rtc.h"
#include <math.h>
#include <stdio.h>
using namespace sepwind;

int main()
{
	//Rtc* pRtc = CreateRtc3();
	//Rtc* pRtc = CreateRtc4();	
	//Rtc* pRtc = CreateRtc5();
	Rtc* pRtc = CreateRtc6();
	//Rtc* pRtc = CreateRtc6Ethernet("192.168.0.10");

	double fov = 50.0;	// 50mm
	//double kfactor = pow(2, 16) / fov;	// rtc3,4 = 2^16 bits
	double kfactor = pow(2, 20) / fov;		// rtc5,6 = 2^20 bits
	//pRtc->initialize(kfactor, "cor_1to1.ctb");
	pRtc->initialize(kfactor, "cor_1to1.ct5"); 

	// laser repetition rate : 50Khz , pulse width : 2usec
	// laser delays : on/off
	// scanner delays : jump/mark/polygon

	// fire during 1sec on center position (0,0)
	pRtc->listBegin();
	pRtc->listTiming(50 * 1000, 2);	
	pRtc->listDelay(10, 20, 100, 300, 0);	
	pRtc->listJump(0, 0);
	pRtc->listOn(1000 * 10);
	pRtc->listOff();

	// draw line figure
	pRtc->listSpeed(1000, 200);	// 1000mm/s, 200 mm/s
	pRtc->listJump(10, 10);
	pRtc->listMark(10, -10);

	//draw rectangle figure
	pRtc->listSpeed(500, 500);	
	pRtc->listJump(10, 10);
	pRtc->listMark(10, -10);
	pRtc->listMark(-10, -10);
	pRtc->listMark(-10, 10);
	pRtc->listMark(10, 10);

	//draw circle figure
	pRtc->listSpeed(500, 500);	
	pRtc->listJump(30, 0);
	pRtc->listArc(0, 0, 360.0);

	pRtc->listEnd();
	pRtc->listExecute(true);


	// matrix operation with rotate
	pRtc->listBegin();
	pRtc->listMatrixLoadIdent();
	for (int i = 0; i < 360; i = +5)
	{
		MATRIX3D m = MAT_ROTATE(i);
		pRtc->listMatrixPush(m);
		pRtc->listJump(-10, 0);
		pRtc->listMark(10, 0);
		pRtc->listMark(-10, 0);
		pRtc->listMatrixPop();
	}
	pRtc->listEnd();
	pRtc->listExecute(true);

	printf("press any key to terminate ... ");
	getchar();

	DestroyRtc(&pRtc);
    return 0;
}

