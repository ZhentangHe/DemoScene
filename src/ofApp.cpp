#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(ofColor::black);
	ofSetBackgroundAuto(true);
	ofSetVerticalSync(true);
	ofSetLineWidth(2);

	fpSize = 1000;
	//TODO: set up area

	makeFlowParticles();

	light.setPosition(0, 0, 300);
	brainModel.loadModel("chip.DAE");
	//auto mesh = brainModel.getMesh(0);
	//const auto verCoords = mesh.getVertices();
	//for (int i = 0; i < verCoords.size(); i++) {
	//	cout << verCoords[i] << endl;
	//}
	//cout << "end vertex coords" << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto fp : fpList) {
		fp->update();
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
	light.enable();
	cam.begin();
	ofEnableDepthTest();

	//brainModel.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofPushMatrix();
	//brainModel.setRotation(0, 90, 0, 0, 1);
	brainModel.setScale(1. / 5., 1. / 5., 1. / 5.);
	brainModel.drawFaces();
	ofPopMatrix();

	for (auto& fp : fpList) {
		fp->display();
	}
	ofDisableDepthTest();
	cam.end();
	light.disable();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

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
void ofApp::dragEvent(ofDragInfo dragInfo) {

}