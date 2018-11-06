#include "rtc.h"
#include "rtc3.h"
#include "rtc4.h"
#include "rtc5.h"
#include "rtc6.h"
#include "rtc6ethernet.h"

namespace sepwind
{


Rtc*	__stdcall	CreateRtc3()
{
	return new Rtc3();
}

Rtc*	__stdcall	CreateRtc4()
{
	return new Rtc4();
}

Rtc*	__stdcall	CreateRtc5()
{
	return new Rtc5();
}

Rtc*	__stdcall	CreateRtc6()
{
	return new Rtc6();
}

Rtc*	__stdcall	CreateRtc6Ethernet(const char* ipaddress)
{
	return new Rtc6Ethernet(ipaddress);
}


void	__stdcall	DestroyRtc(Rtc** pp)
{
	delete *pp;
	*pp = NULL;
}
	
// -------------------------------------------------------




Rtc::~Rtc()
{

}


}//namespace