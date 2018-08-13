#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	This example listen for an image event from the device

	digitalPersona.setup();
	digitalPersona.listDevices();
	digitalPersona.open(0);
	//	if you have more devies plugge, they can be opend by his index
	//	digitalPersona.open(1);
	//	digitalPersona.open(2);
	//	...		
	ofAddListener(ofxDigitalPersonaEvent::events, this, &ofApp::onDigitalPersonaEvent);

}


void	ofApp::exit()
{

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	if (fingerImage.isAllocated())
	{
		ofSetColor(255);
		fingerImage.draw(0, 0);
	}

}

//--------------------------------------------------------------

void	ofApp::onDigitalPersonaEvent(ofxDigitalPersonaEvent	&_args)
{	
	//	if you are using more than one device, you can know what device is sending you the image
	//	checking _args.deviceIndex 
	
	_args.print();
	if (_args.image.isAllocated())
		fingerImage = _args.image;

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
