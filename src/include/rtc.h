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

namespace sepwind
{

class Rtc
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ctbFileName)=0;	/// bit/mm, ctb(rtc3,4) or ct5(rtc5,6)

	virtual bool	__stdcall	listBegin()=0;	/// list begin
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth)=0;	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon)=0; ///usec
	virtual bool	__stdcall	listSpeed(double jump, double mark)=0; /// mm/ec
	virtual bool	__stdcall	listOn(double msec) = 0; ///msec
	virtual bool	__stdcall	listOff() = 0;

	virtual bool	__stdcall	listJump(double x, double y, double z=0.0)=0; /// mm
	virtual bool	__stdcall	listMark(double x, double y, double z=0.0)=0;	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle, double cz=0.0)=0; /// mm, mm, positive angle is ccw, mm

	virtual bool	__stdcall	listEnd()=0;	/// list ended
	virtual bool	__stdcall	listExecute(bool wait)=0;	/// list execute (optional. wait until finish)

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