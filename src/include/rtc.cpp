#include "rtc.h"
#include "rtc3.h"
#include "rtc4.h"
#include "rtc5.h"


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