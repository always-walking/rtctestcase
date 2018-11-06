#ifndef RTC6_ETHERNET_H
#define RTC6_ETHERNET_H

#include "rtc6.h"

namespace sepwind
{

class Rtc6Ethernet : public Rtc6
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ct5FileName);
	
private:
	char	_ipaddress[32];

public:
	Rtc6Ethernet(const char* ipaddress);
	virtual ~Rtc6Ethernet();
};

}//namespace

#endif