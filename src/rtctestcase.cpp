/**********************************************************************************
 *
 *
 * testcase for scanlabs' rtc3/4/5 controller
 * powered by sepwind@gmail.com
 * http://sepwind.blogspot.com
 *
 *
 * history
 * 2017.4.12  v0.1 first release
 * 2018.11.   v0.2 added) rtc6 / rtc6 for ethernet	
 *                  added) double buffered by automatically for massive data
 * 2018.11.6  v0.3	added) 3d option (varioscan)
 *
 *
 **********************************************************************************/

#include "include\rtc.h"
#include <math.h>
#include <stdio.h>
using namespace sepwind;

int main()
{
	printf("(c)SCANLAB testcase program by sepwind@gmail.com.  http://sepwind.blogspot.com\r\n");

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

	printf("press any key to terminate ... ");
	getchar();

	DestroyRtc(&pRtc);
    return 0;
}

