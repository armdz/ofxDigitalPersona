#pragma once

#include "ofMain.h"

class ofxDigitalPersonaEvent : public ofEventArgs {

public:
	ofxDigitalPersonaEvent();
	~ofxDigitalPersonaEvent();
	void	print();

	static ofEvent <ofxDigitalPersonaEvent>	events;
	unsigned int	status;
	unsigned int	deviceIndex;
	string				message;
	GUID					guid;
	ofImage				image;

};
