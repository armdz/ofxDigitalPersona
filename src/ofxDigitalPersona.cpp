#include "ofxDigitalPersona.h"
#include <wincrypt.h>

static WNDPROC windowProcess;
HWND	handle;
HDPOPERATION	operationEnroll(0);
ofxDigitalPersona	*_this = NULL;

/*	Catch the window process */
//	taked from ofxWin8Touch

LRESULT  ptrWindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	if (uMsg == WMUS_FP_NOTIFY)
	{
		_this->processMessage(uMsg, wParam,lParam);
	}
	return CallWindowProc(windowProcess, hwnd, uMsg, wParam, lParam);
}
DPFP_STDAPI DPFPConvertSampleToBitmap(const DATA_BLOB* pSample, PBYTE pBitmap, size_t* pSize);

ofxDigitalPersona::ofxDigitalPersona()
{
	doLog = false;
}


ofxDigitalPersona::~ofxDigitalPersona()
{
}

void	ofxDigitalPersona::setup()
{
	_this = this;
	handle = ofGetWin32Window();
	if (!handle)
		log("Error getting window handler");
	windowProcess = (WNDPROC)SetWindowLongPtr(handle, GWL_WNDPROC, (ULONG)(ptrWindowProcess));
	if (!windowProcess)
		log("Error setting window events handler");

	DPFPInit();
	GUID	*uids = NULL;
	devicesCount = 0;
	devicesGUID.clear();

	if (DPFPEnumerateDevices(&devicesCount, &uids) == S_OK)
	{
		if (uids != NULL)
		{
			for (unsigned int i = 0; i < devicesCount; i++)
			{
				DP_DEVICE_INFO	deviceInfo;
				if (DPFPGetDeviceInfo(uids[i], &deviceInfo) == S_OK)
				{
					devicesGUID.push_back(uids[i]);
				}
			}
		}
	}

}

void		ofxDigitalPersona::open(int	_deviceIndex)
{
	if (_deviceIndex > devicesCount)
	{
		log("There is no device with index " + ofToString(_deviceIndex));
	}
	else {
		open(devicesGUID[_deviceIndex]);
	}
}

void		ofxDigitalPersona::open(GUID	_guid)
{
	HDPOPERATION	operationEnroll(0);
	if (DPFPCreateAcquisition(DP_PRIORITY_NORMAL, _guid, DP_SAMPLE_TYPE_IMAGE, handle, WMUS_FP_NOTIFY, &operationEnroll) == S_OK)
	{
		log("Acquistion at " + ofToString(_guid.Data1) + " OK");
		HRESULT	res = DPFPStartAcquisition(operationEnroll);
		if (res == S_OK)
		{
			log("Started acquistion at " + ofToString(_guid.Data1));
		}
		else {
			log("Error starting acquistion");
		}
	}
	else {
		log("Error creating acquistion");
	}
}

void	ofxDigitalPersona::processMessage(UINT _msg, WPARAM _wParam, LPARAM _lParam)
{

	switch (_wParam)
	{
		case WN_COMPLETED: {
			DATA_BLOB* pImageBlob = reinterpret_cast<DATA_BLOB*>(_lParam);
			size_t Size = 0;
			PBITMAPINFO pOutBmp = NULL;
			HRESULT hr = DPFPConvertSampleToBitmap(pImageBlob, 0, &Size);
			pOutBmp = (PBITMAPINFO)new BYTE[Size];
			hr = DPFPConvertSampleToBitmap(pImageBlob, (PBYTE)pOutBmp, &Size);
			if (hr == S_OK)
			{
				size_t dwColorsSize = pOutBmp->bmiHeader.biClrUsed * sizeof(PALETTEENTRY);
				const BYTE* pBmpBits = (PBYTE)pOutBmp + sizeof(BITMAPINFOHEADER) + dwColorsSize;

				LONG WidthOut = 512;
				LONG HeightOut = 512;

				HDC screen_dc = GetDC(NULL);
				HDC shot_dc = CreateCompatibleDC(screen_dc);

				HBITMAP hBmp = CreateCompatibleBitmap(screen_dc, WidthOut, HeightOut);
				SelectObject(shot_dc, hBmp);

				int i = StretchDIBits(shot_dc, 0, 0, WidthOut, HeightOut, 0, 0, pOutBmp->bmiHeader.biWidth, pOutBmp->bmiHeader.biHeight, pBmpBits, pOutBmp, DIB_RGB_COLORS, SRCCOPY);
				HBITMAP hOldBmp = reinterpret_cast<HBITMAP>((LPARAM)hBmp);
				//	Thanks to https://forum.openframeworks.cc/t/recursive-screen-recording-solution-for-desktop-feedback-loop/22491/14

				BITMAPINFO bmi = { 0 };
				bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
				bmi.bmiHeader.biWidth = WidthOut;
				bmi.bmiHeader.biHeight = HeightOut;
				bmi.bmiHeader.biPlanes = 1;
				bmi.bmiHeader.biBitCount = 24;
				bmi.bmiHeader.biCompression = BI_RGB;

				ofImage	img;
				img.allocate(WidthOut, HeightOut, OF_IMAGE_COLOR);
				GetDIBits(screen_dc, hOldBmp, 0, HeightOut, &img.getPixels()[0], &bmi, DIB_RGB_COLORS);
				img.update();
				dispatchImageEvent(_wParam, currentGuid, img);

			}
			break;
		}
		default:{
			GUID*	guid =	reinterpret_cast<GUID*>(_lParam);
			dispatchEvent(_wParam, *guid);
			break;
		}
	}


}

void		ofxDigitalPersona::dispatchEvent(int	_status, GUID	_guid)
{
	
	string msg = "";
	switch (_status)
	{
		case WN_ERROR: {
			msg = "Error";
			break;
		}
		case WN_DISCONNECT:
			msg = "Disconnect";
			break;
		case WN_RECONNECT:
			msg = "Connected";
			break;
		case WN_FINGER_TOUCHED:
			msg = "Touched";
			break;
		case WN_FINGER_GONE:
			msg = "Finger gone";
			break;
			case WN_IMAGE_READY:{
				msg = "Image ready";
				currentGuid = _guid;
				break;
			}
		case WN_OPERATION_STOPPED:
			msg = "Operation stopped";
			break;
	}

	static	ofxDigitalPersonaEvent	newEvent;
	newEvent.status = _status;
	newEvent.guid = _guid;
	newEvent.message = msg;
	ofNotifyEvent(ofxDigitalPersonaEvent::events, newEvent);

}

void		ofxDigitalPersona::dispatchImageEvent(int	_status, GUID	_guid, ofImage _img)
{
	static	ofxDigitalPersonaEvent	newEvent;
	newEvent.status = _status;
	newEvent.guid = _guid;
	newEvent.image = _img;
	newEvent.message = "Completed";
	ofNotifyEvent(ofxDigitalPersonaEvent::events, newEvent);
}

void		ofxDigitalPersona::listDevices()
{
	ofLogNotice() << "ofxDigitalPersona : ";
	if (devicesGUID.size() == 0)
	{
		ofLogNotice() << "	There is no devices connected" << endl;
	}
	for (unsigned int i = 0; i < devicesGUID.size(); i++)
	{
		ofLogNotice() << "	Device " << i <<  " : " << devicesGUID.at(i).Data1 << endl;
	}

}

void		ofxDigitalPersona::log(string	_val)
{
	if (doLog)
	{
		ofLogNotice() << "ofxDigitalPersona : " << _val;
	}
}

int			ofxDigitalPersona::getDeviceCount()
{
	return devicesGUID.size();
}