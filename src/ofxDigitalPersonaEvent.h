#pragma once

#include "ofMain.h"

class ofxDigitalPersonaEvent : public ofEventArgs {

public:
	ofxDigitalPersonaEvent();
	~ofxDigitalPersonaEvent();
	void	print();

	static ofEvent <ofxDigitalPersonaEvent>	events;
	unsigned int	status;
	string				message;
	GUID					guid;
	ofImage				image;

};
