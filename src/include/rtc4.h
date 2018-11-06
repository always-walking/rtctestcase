#ifndef RTC4_H
#define RTC4_H


#include "rtc.h"


namespace sepwind
{

class Rtc4 : public Rtc
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ctbFileName);	/// bit/mm , ctb or ct5(rtc5)
	virtual bool	__stdcall	listBegin();	/// opening internal buffers
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth);	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon); //usec
	virtual bool	__stdcall	listSpeed(double jump, double mark); /// mm /sec
	virtual bool	__stdcall	listJump(double x, double y); /// mm
	virtual bool	__stdcall	listMark(double x, double y);	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle); /// mm, mm, positive angle is ccw, 
	virtual bool	__stdcall	listOn(double msec);
	virtual bool	__stdcall	listOff();
	virtual bool	__stdcall	listEnd();	/// closing internal buffers
	virtual bool	__stdcall	listExecute(bool wait);	/// blocking until finish

protected:
	double	_kfactor;
	UINT _list;
	UINT _listcnt;
	bool isBufferReady(UINT count);

public:
	Rtc4();
	virtual ~Rtc4();
};

}//namespace

#endif