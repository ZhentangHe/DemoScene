#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

//#define DS_FLOWFIELD
#define DS_BRAINGLOW

#ifdef DS_FLOWFIELD
#include "FlowParticle.h"
#endif // DS_FLOWFIELD

#ifdef DS_BRAINGLOW
#include "BrainGlow.h"
#endif // DS_BRAINGLOW


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

#ifdef DS_BRAINGLOW
	const int interval = 30;
	BrainGlow brainGlow;
	ofShader brainShader;
	vector<int> vecIdxSpread{ 0 };
#endif // DS_BRAINGLOW

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