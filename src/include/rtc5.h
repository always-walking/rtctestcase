#ifndef RTC5_H
#define RTC5_H


#include "rtc.h"
#include <vector>

namespace sepwind
{

class Rtc5 : public Rtc
{

public:
	virtual bool	__stdcall	initialize(double kfactor, char* ct5FileName);	/// bit/mm, ctb(rtc3,4) or ct5(rtc5,6)

	/// control commands
	virtual	bool	__stdcall	ctrlGetGatherSize(unsigned int* pReturnSize);
	virtual bool	__stdcall	ctrlGetGatherData(int channel, long* pReturnData, unsigned int size) ;
	virtual bool	__stdcall	ctrlGetEncoder(int* encX, int* encY, double* mmX, double* mmY) ;
	virtual bool	__stdcall	ctrlEncoderReset() ;

	/// list handling
	virtual bool	__stdcall	listBegin() ;
	virtual bool	__stdcall	listEnd() ;
	virtual bool	__stdcall	listExecute(bool wait) ;	/// list execute (optional. wait until finish)

	/// laser/scanner parameters
	virtual bool	__stdcall	listTiming(double frequency, double pulseWidth) ;	/// hz, usec
	virtual bool	__stdcall	listDelay(double on, double off, double jump, double mark, double polygon) ; ///usec
	virtual bool	__stdcall	listSpeed(double jump, double mark) ; /// mm/ec
	virtual bool	__stdcall	listOn(double msec) ; ///msec
	virtual bool	__stdcall	listOff() ;

	/// matrix for transformation 
	virtual bool	__stdcall	listMatrixLoadIdent();	///3*3 identity matrix
	virtual bool	__stdcall	listMatrixPush(const MATRIX3D& m);	///3*3 push to right
	virtual bool	__stdcall	listMatrixPop();	///3*3 pop from right

	/// x,y,z coordinate
	virtual bool	__stdcall	listJump(double x, double y, double z = 0.0) ; /// mm
	virtual bool	__stdcall	listMark(double x, double y, double z = 0.0) ;	/// mm
	virtual bool	__stdcall	listArc(double cx, double cy, double sweepAngle, double z = 0.0) ; /// mm, mm, positive angle is ccw, mm

	/// measurement data for plot
	virtual bool	__stdcall	listGatherBegin(double usec, int channel1, int channel2) ;
	virtual bool	__stdcall	listGatherEnd() ;

	/// marking on the fly process
	virtual bool	__stdcall	listOnTheFlyBegin(bool encoderReset) ;
	virtual bool	__stdcall	listOnTheFlyPosWait(bool xORy, double xyPos, int condition) ;	//
	virtual bool	__stdcall	listOnTheFlyRangeWait(double x, double rangeX, double y, double rangeY) ;
	virtual bool	__stdcall	listOnTheFlyEnd(double jumpTox, double jumpToy) ;

protected:
	BOOL _3d;
	double	_kfactor;
	double _xCntPerMm;
	double _yCntPerMm;
	UINT _list;
	UINT _listcnt;
	std::vector<MATRIX3D> _matrices;
	bool isBufferReady(UINT count);

public:
	Rtc5(double xCntPerMm=0.0, double yCntPerMm=0.0);
	virtual ~Rtc5();
};

}//namespace

#endif