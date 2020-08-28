#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	const unsigned char* glVer = glGetString(GL_VERSION);
	cout << "OpenGL Version: "<< glVer << endl;

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
	//cam.setAutoDistance(false);
	brainGlow.init("brainmesh_3000_corrected.DAE");

#endif // DS_BRAINGLOW
	isShaderDirty = true;
	humanoidModel.loadModel("brainmesh_3000_corrected.DAE");
	humanoidModel.setScale(.25, .25, .25);
	humanoidModel.setPosition(75, -150, 0);
	humanoidModel.setRotation(humanoidModel.getNumRotations(), 90, 1, 0, 0);
	humanoidModel.setRotation(humanoidModel.getNumRotations(), -90, 0, 0, 1);

	humanoidMesh = humanoidModel.getMesh(0);
	
}

//--------------------------------------------------------------
void ofApp::update() {
#ifdef DS_BRAINGLOW
	//float prop = ofMap(ofGetElapsedTimeMillis() % 1000, 0, 10000, 0, 1);
	//heyPos = testMesh.getVertex(indexVertex) * prop + testMesh.getVertex(indexVertex + 1) * (1 - prop);
	//if (prop > 1)
	//	indexVertex++;
#endif // DS_BRAINGLOW
	if (isShaderDirty) {
		ofLogNotice() << "Reloading Shader.";
		humanoidShader = shared_ptr<ofShader>(new ofShader());
		humanoidShader->load("instanced_120.vert", "instanced_120.frag");
		GLint err = glGetError();
		if (err != GL_NO_ERROR) {
			ofLogNotice() << "Load Shader came back with GL error:	" << err;
		}

		isShaderDirty = false;
	}

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
	if (ofGetFrameNum() % 300 == 0 && !vecTemp.empty()) {
		vecTemp = brainGlow.spread(vecTemp);
	}
	

	// bind the shader
	humanoidShader->begin();
	// give the shader access to our texture
	//humanoidShader->setUniformTexture("tex0", mTexDepth, 0);
	// feed the shader a normalized float value that changes over time, to animate things a little
	humanoidShader->setUniform1f("timeValue", (ofGetElapsedTimeMillis() % 30000) / 30000.0f);
	// we only want to see triangles facing the camera.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// let's draw 128 * 128 == 16384 boxes !
	humanoidMesh.drawInstanced(OF_MESH_FILL, 12 * 12);

	glDisable(GL_CULL_FACE);
	humanoidShader->end();


	brainGlow.getMesh().drawWireframe();
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