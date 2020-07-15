#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(ofColor::black);
	ofSetBackgroundAuto(true);
	ofSetVerticalSync(true);

	fpSize = 1000;
	//TODO: set up area 
	
	makeFlowParticles();
}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto fp : fpList) {
		fp->update();
		//TODO: check edge
	}
	fpList.erase(
		remove_if(
			fpList.begin(),
			fpList.end(),
			[](auto fp) { return fp->isDead(); }
		),
		fpList.end()
	);
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	ofEnableDepthTest();
	for (auto& fp : fpList) {
		fp->display();
	}
	ofDisableDepthTest();
	cam.end();
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

void ofApp::makeFlowParticles() {
	while (fpList.size() < fpSize) {
		auto pos = ofVec3f(
			ofRandom(-300, 300),
			ofRandom(-300, 300),
			ofRandom(-300, 300)
		);
		fpList.push_back(std::make_shared<FlowParticle>(pos));
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
