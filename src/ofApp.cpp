#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	const unsigned char* glVer = glGetString(GL_VERSION);
	cout << glVer << endl; // DO NOT PUT A DEREFERENCE OPERATOR infront of glVer

	ofSetFrameRate(60);
	ofBackground(ofColor::black);
	ofSetBackgroundAuto(true);
	ofSetVerticalSync(true);
	ofEnableDepthTest();

#ifdef DS_FLOWFIELD
	fpShader.load("FlowField");
	fpSize = 100;
	//TODO: set up area

	makeFlowParticles();
#endif // DS_FLOWFIELD

#ifdef DS_BRAINGLOW
	light.setPosition(0, 0, 300);

	brainModel.loadModel("brainmesh_3000_corrected.DAE");
	brainModel.setScale(.75, .75, .75);
	brainModel.setPosition(75, -150, 0);
	brainModel.setRotation(brainModel.getNumRotations(), 90, 1, 0, 0);
	brainModel.setRotation(brainModel.getNumRotations(), -90, 0, 0, 1);

	brainGlow.init("brainmesh_3000_corrected.DAE");
	//brainShader.load("BrainGlow");
	//1687 "real" vertices, 9996 overlapping vertices
	//auto vec = brainModel.getMesh(0).getVertices();
	//sort(vec.begin(), vec.end(), [](const glm::vec3& a, const glm::vec3& b) -> bool {
	//	if (abs(a.x - b.x) < 0.01) {
	//		if (abs(a.y - b.y) < 0.01) {
	//			return a.z < b.z;
	//		}
	//		else
	//			return a.y < b.y;
	//	}
	//	else
	//		return a.x < b.x;
	//	});
	//vec.erase(unique(vec.begin(), vec.end(),
	//	[](const glm::vec3& a, const glm::vec3& b) {
	//		return abs(a.x - b.x) < 0.01 && abs(a.y - b.y) < 0.01 && abs(a.z - b.z) < 0.01;
	//	}), vec.end());
	//cout << vec.size() << endl;
#endif // DS_BRAINGLOW

}

//--------------------------------------------------------------
void ofApp::update() {
#ifdef DS_BRAINGLOW
	//float prop = ofMap(ofGetElapsedTimeMillis() % 1000, 0, 10000, 0, 1);
	//heyPos = testMesh.getVertex(indexVertex) * prop + testMesh.getVertex(indexVertex + 1) * (1 - prop);
	//if (prop > 1)
	//	indexVertex++;
#endif // DS_BRAINGLOW


#ifdef DS_FLOWFIELD
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
#endif // DS_FLOWFIELD

}

//--------------------------------------------------------------
void ofApp::draw() {
#ifdef DS_BRAINGLOW
	light.enable();
	cam.begin();
	ofPushMatrix();
	ofTranslate(75, -150);
	ofScale(5);
	ofRotateXDeg(-90);
	ofRotateZDeg(90);
	//ofDrawSphere(heyPos, 5);
	if (ofGetFrameNum() % 30 == 0) {
		brainMesh.addVertex(brainModel.getMesh(0).getVertex(frameCounter));
		cout << brainModel.getMesh(0).getVertex(frameCounter) << endl;
		brainMesh.addColor(ofFloatColor(ofRandom(1), ofRandom(1), ofRandom(1)));
		ofDrawSphere(brainModel.getMesh(0).getVertex(frameCounter), 2);
		frameCounter++;
	}
	brainMesh.drawWireframe();
	ofPopMatrix();
	cam.end();
	light.disable();
#endif // DS_BRAINGLOW

#ifdef DS_FLOWFIELD
	light.enable();
	cam.begin();
	ofEnableDepthTest();

	fpShader.begin();
	for (auto& fp : fpList) {
		fp->display();
	}
	fpShader.end();

	ofDisableDepthTest();
	cam.end();
	light.disable();
#endif // DS_FLOWFIELD

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

#ifdef DS_FLOWFIELD
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

#endif // DS_FLOWFIELD

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}