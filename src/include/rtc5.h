#ifndef RTC5_H
#define RTC5_H


#include "rtc.h"


namespace sepwind
{

class Rtc5 : public Rtc
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ctbFileName);	/// bit/mm, ctb(rtc3,4) or ct5(rtc5,6)

	virtual bool	__stdcall	listBegin();	/// list begin
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth);	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon); ///usec
	virtual bool	__stdcall	listSpeed(double jump, double mark); /// mm/ec
	virtual bool	__stdcall	listOn(double msec); ///msec
	virtual bool	__stdcall	listOff();

	virtual bool	__stdcall	listJump(double x, double y, double z = 0.0); /// mm
	virtual bool	__stdcall	listMark(double x, double y, double z = 0.0);	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle, double cz = 0.0); /// mm, mm, positive angle is ccw, mm

	virtual bool	__stdcall	listEnd();	/// list ended
	virtual bool	__stdcall	listExecute(bool wait);	/// list execute (optional. wait until finish)

protected:
	BOOL _3d;
	double	_kfactor;
	UINT _list;
	UINT _listcnt;
	bool isBufferReady(UINT count);

public:
	Rtc5();
	virtual ~Rtc5();
};

}//namespace

#endif