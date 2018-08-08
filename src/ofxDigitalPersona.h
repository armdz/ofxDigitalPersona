/*
	http://armdz.com
*/

#pragma once

#include "ofMain.h"
#include "ofxDigitalPersonaEvent.h"
#include "DPDevClt.h"

enum { WMUS_FP_NOTIFY = WM_USER + 1 };

class ofxDigitalPersona
{
public:
	ofxDigitalPersona();
	~ofxDigitalPersona();

	void		setup();
	void		open(int	_deviceIndex);
	void		open(GUID	_guid);
	void		processMessage(UINT _msg, WPARAM _wParam, LPARAM _lParam);
	void		listDevices();
	int			getDeviceCount();
private:
	void		dispatchEvent(int	_status, GUID	_guid);
	void		dispatchImageEvent(int	_status, GUID	_guid,ofImage _img);

	unsigned	long					devicesCount;
	vector<GUID>						devicesGUID;
	GUID		currentGuid;

};

