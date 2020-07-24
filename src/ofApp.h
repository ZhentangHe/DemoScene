#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "FlowParticle.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	ofEasyCam cam;
	ofLight light;
	ofxAssimpModelLoader brainModel;

	ofShader fpShader;
	std::vector<std::shared_ptr<FlowParticle>> fpList;
	int fpSize;
	of3dPrimitive area;

	void makeFlowParticles();

};