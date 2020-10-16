#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#ifdef DS_FLOWFIELD
#include "FlowParticle.h"
#endif // DS_FLOWFIELD

#include "BrainGlow.h"
#include "DemoCam.h"

class ofApp : public ofBaseApp {

public:
	ofApp() : cam(ofVec3f(-80, 150, 2000), ofVec3f(-50, 150, 2050)) {}

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
	DemoCam cam;
	ofLight light;

	const int interval = 30;
	BrainGlow brainGlow;
	ofShader brainShader;
	vector<int> vecIdxSpread{ 0 };

	ofxAssimpModelLoader humanoidModel;
	ofVboMesh humanoidMesh;
	ofTexture humanoidTex;
	shared_ptr<ofShader> humanoidShader;
	bool isShaderDirty;

#ifdef DS_FLOWFIELD
	ofShader fpShader;
	std::vector<std::shared_ptr<FlowParticle>> fpList;
	size_t fpSize;
	of3dPrimitive area;
	void makeFlowParticles();
#endif // DS_FLOWFIELD

};