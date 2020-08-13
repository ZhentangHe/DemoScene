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

	//brainShader.load("BrainGlow");
	
	//brainMesh = brainModel.getMesh(0);
	//for (auto i : brainMesh.getIndices()) {
	//	cout << i << endl;
	//}

	cout << brainModel.getMesh(0).getNumVertices() << endl;
	cout << brainModel.getMesh(0).getNumIndices() << endl;
	auto brainVertices = brainMesh.getVertices();
	//decltype(brainVertices) sampledVertices{ brainVertices[0]};
	//supported in CXX17
	//std::sample(
	//	brainVertices.begin(),
	//	brainVertices.end(),
	//	std::back_inserter(sampledVertices),
	//	10,
	//	std::mt19937{ std::random_device{}() }
	//);

	
#endif // DS_BRAINGLOW

}

//alternative sample method
//std::vector<int> pick(int N, int k) {
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	std::unordered_set<int> elems = pickSet(N, k, gen);
//
//	// ok, now we have a set of k elements. but now
//	// it's in a [unknown] deterministic order.
//	// so we have to shuffle it:
//
//	std::vector<int> result(elems.begin(), elems.end());
//	std::shuffle(result.begin(), result.end(), gen);
//	return result;
//}
//
//std::unordered_set<int> pickSet(int N, int k, std::mt19937& gen)
//{
//	std::uniform_int_distribution<> dis(1, N);
//	std::unordered_set<int> elems;
//
//	while (elems.size() < k) {
//		elems.insert(dis(gen));
//	}
//
//	return elems;
//}

//--------------------------------------------------------------
void ofApp::update() {
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
	
	//brainModel.drawFaces();
	//brainModel.drawVertices();
	//brainModel.drawWireframe();

	
	brainMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	
	ofPushMatrix();
	ofTranslate(75, -150);
	ofScale(5);
	ofRotateXDeg(-90);
	ofRotateZDeg(90);
	//brainMesh.drawWireframe();


	if (ofGetFrameNum() % 30 == 0) {
		brainMesh.addVertex(brainModel.getMesh(0).getVertex(frameCounter));
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