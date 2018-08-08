#include "ofxDigitalPersonaEvent.h"

ofEvent <ofxDigitalPersonaEvent>	ofxDigitalPersonaEvent::events;

ofxDigitalPersonaEvent::ofxDigitalPersonaEvent()
{
}


ofxDigitalPersonaEvent::~ofxDigitalPersonaEvent()
{
}

void	ofxDigitalPersonaEvent::print()
{
	ofLogNotice() << "ofxDigitalPersonaEvent: " << guid.Data1 << " = " << message;
}