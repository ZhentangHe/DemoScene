#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "FlowParticle.h"

#include <algorithm>
#include <random>
#include <unordered_set>

//#define DS_FLOWFIELD
#define DS_BRAINGLOW

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


	int frameCounter = 0;
	ofxAssimpModelLoader brainModel;
	ofMesh brainMesh;
	ofShader brainShader;

	ofShader fpShader;
	std::vector<std::shared_ptr<FlowParticle>> fpList;
	size_t fpSize;
	of3dPrimitive area;

	void makeFlowParticles();
};