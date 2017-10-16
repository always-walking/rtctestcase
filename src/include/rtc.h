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
	virtual bool	__stdcall	initialize(double kfactor, char* lpszCtbFileName)=0;	/// bit/mm , ctb or ct5(rtc5)
	virtual bool	__stdcall	listBegin()=0;	/// opening internal buffer
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth)=0;	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon)=0; //usec
	virtual bool	__stdcall	listSpeed(double jump, double mark)=0; /// mm /sec
	virtual bool	__stdcall	listJump(double x, double y)=0; /// mm
	virtual bool	__stdcall	listMark(double x, double y)=0;	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle)=0; /// mm, mm, positive angle is ccw, 
	virtual bool	__stdcall	listOn(double msec)=0;
	virtual bool	__stdcall	listOff()=0;
	virtual bool	__stdcall	listEnd()=0;	/// closing internal buffer
	virtual bool	__stdcall	listExecute(bool wait)=0;	/// blocking until finish

	virtual ~Rtc();
};


Rtc*	__stdcall	CreateRtc3();
Rtc*	__stdcall	CreateRtc4();
Rtc*	__stdcall	CreateRtc5();
void	__stdcall	DestroyRtc(Rtc** ppRtc);


}//namespace


#endif