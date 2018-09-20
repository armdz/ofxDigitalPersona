/*
	http://armdz.com
*/

#pragma once

#include "ofMain.h"
#include "ofxDigitalPersonaEvent.h"
#include "dpDefs.h"
#include "dpRCodes.h"
#include "DPDevClt.h"
#include "dpFtrEx.h"

enum { WMUS_FP_NOTIFY = WM_USER + 1 };

class ofxDigitalPersona
{
public:
	ofxDigitalPersona();
	~ofxDigitalPersona();

	void		setup(int _imgSize = 512);
	void		open(int	_deviceIndex);
	void		open(GUID	_guid);
	void		printLog(bool	_val);
	void		processMessage(UINT _msg, WPARAM _wParam, LPARAM _lParam);
	void		listDevices();
	int			getDeviceCount();

private:
	void		log(string	_val);
	void		dispatchEvent(int	_status, GUID	_guid);
	void		dispatchImageEvent(int	_status, GUID	_guid,ofImage _img);
	void		initFX();

	unsigned	long					devicesCount;
	vector<GUID>						devicesGUID;
	GUID		currentGuid;
	bool		doLog;
	std::map<unsigned long,int>	deviceMap;
	int		imgSize;

	//	Feature extraction
	FT_HANDLE	fxContext;

};

