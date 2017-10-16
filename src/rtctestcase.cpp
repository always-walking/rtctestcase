/****************************************************************
 *
 * testcase for scanlabs' rtc3/4/5 controller
 * powered by sepwind@gmail.com
 * http://sepwind.blogspot.com
 *
 *
 * history
 * 2017.4.12	v0.1 first release
 *
 *
 ***************************************************************/


#include "include\rtc.h"
#include <math.h>
#include <stdio.h>

using namespace sepwind;

int main()
{
	//Rtc* pRtc = CreateRtc3();
	//Rtc* pRtc = CreateRtc4();	
	Rtc* pRtc = CreateRtc5();

	double fov = 50.0;	// 50mm
	//double kfactor = pow(2, 16) / fov;	// rtc3,4 = 2^16 bits
	double kfactor = pow(2, 20) / fov;		// rtc5 = 2^20 bits
	//pRtc->initialize(kfactor, "cor_1to1.ctb");
	pRtc->initialize(kfactor, "cor_1to1.ct5"); //rtc5 = .ct5

	pRtc->listBegin();
	pRtc->listTiming(50 * 1000, 2);	// 50khz, 2us
	pRtc->listDelay(10, 20, 100, 300, 0);	//delay usec

	pRtc->listEnd();
	pRtc->listExecute(true);


	::Sleep(100);
	pRtc->listBegin();
	pRtc->listOn(1000 * 10);
	pRtc->listOff();
	// line shape
	//pRtc->listSpeed(1000, 200);	// 1000mm/s, 200 mm/s
	//pRtc->listJump(10, 10);
	//pRtc->listMark(10, -10);
	//rectangle shape
	//pRtc->listSpeed(500, 500);	// 500mm/s, 500 mm/s
	//pRtc->listJump(10, 10);
	//pRtc->listMark(10, -10);
	//pRtc->listMark(-10, -10);
	//pRtc->listMark(-10, 10);
	//pRtc->listMark(10, 10);
	//circle shape
	//pRtc->listSpeed(500, 500);	// 1000/s, 1000 mm/s
	//pRtc->listJump(30, 0);
	//pRtc->listArc(0, 0, 360.0);

	pRtc->listEnd();
	//pRtc->listExecute(true);


	getchar();

	DestroyRtc(&pRtc);
    return 0;
}

