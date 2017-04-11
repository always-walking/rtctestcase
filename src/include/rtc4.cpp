#include "rtc4.h"
#include "rtc4expl.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace sepwind
{

using namespace rtc4;


Rtc4::Rtc4()
{
	_kfactor = 0.0;
}

Rtc4::~Rtc4()
{

}

bool	__stdcall	Rtc4::initialize(double kfactor, char* lpszCtbFileName)
{
	int error = RTC4open();
	if (0 != error)
	{
		fprintf(stderr, "fail to initialize the rtc4 library. error code = %d", error);
		return false;
	}
	_kfactor = kfactor;

	// program file load
	error = load_program_file("RTC4D2.hex");
	if (0 != error)
	{
		fprintf(stderr, "fail to load the Rtc4 program file :  error code = %d", error);
		return false;
	}

	error = load_correction_file(
		lpszCtbFileName,		// ctb
		1,	// table no (1 or 2)
		1, 1,	//scale
		0, //theta
		0, 0 //offset
	);
	if (0 != error)
	{
		fprintf(stderr, "fail to load the correction file :  error code = %d", error);
		return false;
	}

	select_cor_table(1, 0);	//1 correction file at primary head

							// stand by
	set_standby(0, 0);
	return true;
}

bool __stdcall	Rtc4::listBegin()
{
	set_start_list(1);//list 1
	return true;
}

bool __stdcall	Rtc4::listTiming(double frequency, double pulsewidth)
{
	double period = 1.0f / frequency * (double)1.0e6;	//usec
	double halfperiod = period / 2.0f;

	set_laser_timing(
		halfperiod,	//half period (us)
		pulsewidth,
		pulsewidth,
		0);	// timebase 1 usec	
	return true;
}

bool __stdcall	Rtc4::listDelay(double on, double off, double jump, double mark, double polygon)
{
	set_scanner_delays(
		(jump / 10.0f),
		(mark / 10.0f),
		(polygon / 10.0f)
	);
	// unit: 10 usec

	return true;
}

bool __stdcall	Rtc4::listSpeed(double jump, double mark)
{
	double jump_bitpermsec = (double)(jump / 1.0e3 * _kfactor);
	double mark_bitpermsec = (double)(mark / 1.0e3 * _kfactor);

	set_jump_speed(jump_bitpermsec);
	set_mark_speed(mark_bitpermsec);
	return true;
}

bool __stdcall	Rtc4::listJump(double x, double y)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	jump_abs(xbits, ybits);
	return true;
}

bool __stdcall	Rtc4::listMark(double x, double y)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	mark_abs(xbits, ybits);
	return true;
}

bool __stdcall	Rtc4::listArc(double cx, double cy, double sweepAngle)
{
	int cxbits = cx * _kfactor;
	int cybits = cy * _kfactor;
	arc_abs(cxbits, cybits, -sweepAngle);
	return true;
}

bool __stdcall	Rtc4::listEnd()
{
	set_end_of_list();
	return TRUE;
}

bool __stdcall Rtc4::listExecute(bool wait)
{
	execute_list(1);	//list 1

	if (wait)
	{
		unsigned short busy(0), position(0);
		do {
			::Sleep(50);
			get_status(&busy, &position);
		} while (busy);
	}
	return true;
}




}//namespace