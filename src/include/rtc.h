/*
 * rtc interface for scanner controller
 * 
 * powered by sepwind@gmail.com
 * http://sepwind.blogspot.com
 * scanlab and rtc is a trademark of SCANLAB.
 *
 *
 */

#ifndef RTC_H
#define RTC_H

#include <windows.h>
#include "rtcutil.h"


namespace sepwind
{

class Rtc
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ctbFileName)=0;	/// bit/mm, ctb(rtc3,4) or ct5(rtc5,6)

	/// control commands
	virtual	bool	__stdcall	ctrlGetGatherSize(unsigned int* pReturnSize)=0;
	virtual bool	__stdcall	ctrlGetGatherData(int channel, long* pReturnData, unsigned int size)=0;
	virtual bool	__stdcall	ctrlGetEncoder(int* encX, int* encY, double* mmX, double* mmY)=0;
	virtual bool	__stdcall	ctrlEncoderReset()=0;
	
	/// list handling
	virtual bool	__stdcall	listBegin()=0;	
	virtual bool	__stdcall	listEnd() = 0;	
	virtual bool	__stdcall	listExecute(bool wait) = 0;	/// list execute (optional. wait until finish)

	/// laser/scanner parameters
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth)=0;	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon)=0; ///usec
	virtual bool	__stdcall	listSpeed(double jump, double mark)=0; /// mm/ec
	virtual bool	__stdcall	listOn(double msec) = 0; ///msec
	virtual bool	__stdcall	listOff() = 0;

	/// matrix for transformation 
	virtual bool	__stdcall	listMatrixLoadIdent()=0;	///3*3 identity matrix
	virtual bool	__stdcall	listMatrixPush(const MATRIX3D& m)=0;	///3*3 push to right
	virtual bool	__stdcall	listMatrixPop()=0;	///3*3 pop from right

	/// x,y,z coordinate
	virtual bool	__stdcall	listJump(double x, double y, double z=0.0)=0; /// mm
	virtual bool	__stdcall	listMark(double x, double y, double z=0.0)=0;	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle, double z=0.0)=0; /// mm, mm, positive angle is ccw, mm

	/// measurement data for plot
	virtual bool	__stdcall	listGatherBegin(double usec, int channel1, int channel2) = 0;
	virtual bool	__stdcall	listGatherEnd() = 0;

	/// marking on the fly process
	virtual bool	__stdcall	listOnTheFlyBegin(bool encoderReset) = 0;
	virtual bool	__stdcall	listOnTheFlyPosWait(bool xORy, double xyPos, int condition)=0;	//
	virtual bool	__stdcall	listOnTheFlyRangeWait(double x, double rangeX, double y, double rangeY)=0;	
	virtual bool	__stdcall	listOnTheFlyEnd(double jumpTox, double jumpToy)=0;

	virtual ~Rtc();
};

Rtc*	__stdcall	CreateRtc3();
Rtc*	__stdcall	CreateRtc4();
Rtc*	__stdcall	CreateRtc5();
Rtc*	__stdcall	CreateRtc6();
Rtc*	__stdcall	CreateRtc6Ethernet(const char* ipaddress);
void	__stdcall	DestroyRtc(Rtc** ppRtc);

}//namespace


#endif