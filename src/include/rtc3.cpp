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

bool	__stdcall	Rtc3::initialize(double kfactor, char* ctbFileName)
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

	UINT32 rtcVersion = get_rtc_version();
	fprintf(stdout, "card count : %d. dll, hex, firmware version : %d, %d, %d\r\n", \
		rtc3_count_cards(), get_dll_version(), get_hex_version(), rtcVersion & 0x0F);

	if (rtcVersion & 0x100)
		fprintf(stdout, "processing on the fly option enabled\r\n");

	if (rtcVersion & 0x200)
		fprintf(stdout, ("2nd scanhead option enabled\r\n"));

	if (rtcVersion & 0x400)
	{
		error = load_program_file("RTC3D3.hex");
		if (0 != error)
		{
			fprintf(stderr, "fail to load the rtc3d3.hex program file :  error code = %d\r\n", error);
			return false;
		}
		fprintf(stdout, ("3d option (varioscan) enabled\r\n"));
		_3d = TRUE;
	}
	else
		_3d = FALSE;

	_kfactor = kfactor;
	error = load_correction_file(
		ctbFileName,		// ctb
		1,	// table no (1 ~ 2)
		1, 1,//scale
		0, //theta
		0, 0//offset
	);

	if (0 != error)
	{
		fprintf(stderr, "fail to load the correction file :  error code = %d\r\n", error);
		return false;
	}

	if (_3d)
		select_cor_table(1, 1);	//1 correction file at primary / secondary head	
	else
		select_cor_table(1, 0);	//1 correction file at primary head

	set_standby(0, 0);
	return true;
}

bool __stdcall	Rtc3::listBegin()
{
	_list = 1;
	_listcnt = 0;
	set_start_list(1);
	return true;
}

bool __stdcall	Rtc3::listTiming(double frequency, double pulsewidth)
{
	double period = 1.0f / frequency * (double)1.0e6;	//usec
	double halfperiod = period / 2.0f;

	if (!this->isBufferReady(1))
		return false;

	if (halfperiod < 1.0)
	{
		set_laser_timing(
			(USHORT)(halfperiod * 8.0f),	//half period (us)
			(USHORT)(pulsewidth * 8.0f),
			(USHORT)(pulsewidth * 8.0f),
			1);	//timebase 1/8 usec
	}
	else
	{
		set_laser_timing(
			(USHORT)halfperiod,	//half period (us)
			(USHORT)pulsewidth,
			(USHORT)pulsewidth,
			0);	// timebase 1 usec
	}
	return true;
}

bool __stdcall	Rtc3::listDelay(double on, double off, double jump, double mark, double polygon)
{
	if (!this->isBufferReady(2))
		return false;
	set_laser_delays(
		(USHORT)on,
		(USHORT)off);
	set_scanner_delays(
		(jump / 10.0f),
		(mark / 10.0f),
		(polygon / 10.0f)
	);
	return true;
}

bool __stdcall	Rtc3::listSpeed(double jump, double mark)
{
    double jump_bitpermsec = (double)(jump / 1.0e3 * _kfactor);
    double mark_bitpermsec = (double)(mark / 1.0e3 * _kfactor);

	if (!this->isBufferReady(2))
		return false;
	set_jump_speed(jump_bitpermsec);
	set_mark_speed(mark_bitpermsec);
	return true;
}

bool __stdcall	Rtc3::listJump(double x, double y, double z)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	int zbits = z * _kfactor;
	if (!this->isBufferReady(1))
		return false;
	if (_3d)
		jump_abs_3d(xbits, ybits, zbits);
	else
		jump_abs(xbits, ybits);
	return true;
}

bool __stdcall	Rtc3::listMark(double x, double y, double z)
{
	int xbits = x * _kfactor;
	int ybits = y * _kfactor;
	int zbits = z * _kfactor;
	if (!this->isBufferReady(1))
		return false;
	if (_3d)
		mark_abs_3d(xbits, ybits, zbits);
	else
		mark_abs(xbits, ybits);
	return true;
}

bool __stdcall	Rtc3::listArc(double cx, double cy, double sweepAngle, double cz)
{
	if (_3d && cz != 0.0)
	{
		/// user defined code 
		fprintf(stderr, "unsupported list arc with 3d\r\n");
		return false;
	}	

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
		if (!this->isBufferReady(1))
			return false;
		laser_on_list(1000 * 1000 / 10);
		remind_msec -= 1000;
	}

	if (!this->isBufferReady(1))
		return false;
	laser_on_list(remind_msec * 1000 / 10);
	return TRUE;
}

bool	__stdcall	Rtc3::listOff()
{
	if (!this->isBufferReady(1))
		return false;
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
	execute_list(1);	
	
	if (wait)
	{
		unsigned short busy(0), position(0);
		do {
			::Sleep(10);
			get_status(&busy, &position);
		} while (busy);
	}    
	return true;
}

typedef union
{
	UINT16 value;
	struct
	{
		UINT16	load1 : 1;
		UINT16	load2 : 1;
		UINT16	ready1 : 1;
		UINT16	ready2 : 1;
		UINT16	busy1 : 1;
		UINT16	busy2 : 1;
		UINT16	used1 : 1;
		UINT16	reserved : 10;
	};
}READ_STATUS;

bool Rtc3::isBufferReady(UINT count)
{
	if ((_listcnt + count) >= 8000)
	{
		USHORT busy(0), position(0);
		get_status(&busy, &position);
		if (!busy)
		{
			set_end_of_list();
			execute_list(_list);
			_list = _list ^ 0x03;
			set_start_list(_list);
		}
		else
		{
			set_end_of_list();
			auto_change();
			READ_STATUS s;
			switch (_list)
			{
			case 1:
				do
				{
					s.value = read_status();
					::Sleep(10);
				} while (s.busy2);
				break;

			case 2:
				do
				{
					s.value = read_status();
					::Sleep(10);
				} while (s.busy1);
				break;
			}
			_list = _list ^ 0x03;
			set_start_list(_list);
		}

		_listcnt = count;
	}
	_listcnt += count;
	return TRUE;
}


}//namespace