#include "rtc3.h"
#include "rtc3expl.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace sepwind
{

using namespace rtc3;


Rtc3::Rtc3()
{
	_kfactor = 0.0;
	_x = _y = 0.0;
}

Rtc3::~Rtc3()
{

}

bool	__stdcall	Rtc3::initialize(double kfactor, char* lpszCtbFileName)
{
	int error = RTC3open();
	if ( 0 != error)
	{
		fprintf( stderr, "fail to initialize the rtc3 library. error code = %d", error);
		return false;
	}
	_kfactor = kfactor;

    // program file load
    error = load_program_file("rtc3d2.hex");	
    if(0 != error)
    {
		fprintf(stderr, "fail to load the rtc3 program file :  error code = %d", error);
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
	set_standby( 0, 0);
	return true;
}

bool __stdcall	Rtc3::listBegin()
{
	set_start_list(1);//list 1
	return true;
}

bool __stdcall	Rtc3::listTiming(double frequency, double pulsewidth)
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

bool __stdcall	Rtc3::listDelay(double on, double off, double jump, double mark, double polygon)
{
	set_scanner_delays(
		(jump /10.0f),			
		(mark /10.0f),			
		(polygon / 10.0f)
		);   
	// unit: 10 usec

	return true;
}

bool __stdcall	Rtc3::listSpeed(double jump, double mark)
{
    double jump_bitpermsec = (double)(jump / 1.0e3 * _kfactor);
    double mark_bitpermsec = (double)(mark / 1.0e3 * _kfactor);

	set_jump_speed(jump_bitpermsec);
	set_mark_speed(mark_bitpermsec);
	return true;
}

bool __stdcall	Rtc3::listJump(double x, double y)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	jump_abs( xbits, ybits);
	_x = x;
	_y = y;
	return true;
}

bool __stdcall	Rtc3::listMark(double x, double y)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	mark_abs( xbits, ybits);
	_x = x;
	_y = y;
	return true;
}

bool __stdcall	Rtc3::listArc(double cx, double cy, double sweepAngle)
{
	// rtc3 는 arc_abs 명령이 없으므로
	// 해당 원호를 직선으로 짤게 쪼개어 mark 하는 방식으로 처리가 필요	
	// 그러기 위해서는 이전 스캐너 위치(_x,  _y) 가 필요
	
	int steps = sweepAngle / 1;	// 매 1도 단위로 쪼개어 직선으로 보간한다

	double degInRad = 0;
	if (_y != cy || _x != cx)
		degInRad = atan2(_y - cy, _x - cx);
	double startAngle = degInRad * 180.0 / M_PI;
	double deltaAngle = sweepAngle / (double)steps;
	double deltaRad = deltaAngle / 180.0 * M_PI;
	double r = sqrt((cx - _x)*(cx - _x) + (cy - _y)*(cy - _y));
	double radian = degInRad;
	for (int i = 0; i < steps; i++)
	{
		radian += deltaRad;
		double x = r * cos(radian) + cx;
		double y = r * sin(radian) + cy;
		if (!listMark(x, y))
			return false;
	}
	return true;
}

bool	__stdcall Rtc3::listOn(double msec)
{
	double remind_msec = msec;
	while (remind_msec > 1000)
	{
		laser_on_list(1000 * 1000 / 10);
		remind_msec -= 1000;
	}

	laser_on_list(remind_msec * 1000 / 10);
	return TRUE;

}

bool	__stdcall	Rtc3::listOff()
{
	laser_signal_off_list();
	return true;
}

bool __stdcall	Rtc3::listEnd()
{
	set_end_of_list();	
	return TRUE;
}

bool __stdcall Rtc3::listExecute(bool wait)
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