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
	brainShader.load("brainshader");

#endif // DS_BRAINGLOW
	ofDisableArbTex();
	ofLoadImage(humanoidTex, "Zhentang4.jpg");

	isShaderDirty = true;
	humanoidModel.loadModel("Zhentang4_20000f.fbx");

	humanoidMesh = humanoidModel.getMesh(0);
	
}

//--------------------------------------------------------------
void ofApp::update() {
#ifdef DS_BRAINGLOW
	if (ofGetFrameNum() % interval == 0 && !vecIdxSpread.empty()) {
		vecIdxSpread = brainGlow.spread(vecIdxSpread);
	}
	else {
		//haven't figure out how this works
		float prop = (float)(ofGetFrameNum() % interval) / 30.;
	}

	//float prop = ofMap(ofGetElapsedTimeMillis() % 1000, 0, 10000, 0, 1);
	//heyPos = testMesh.getVertex(indexVertex) * prop + testMesh.getVertex(indexVertex + 1) * (1 - prop);
	//if (prop > 1)
	//	indexVertex++;
#endif // DS_BRAINGLOW
	if (isShaderDirty) {
		ofLogNotice() << "Reloading Shader.";
		humanoidShader = shared_ptr<ofShader>(new ofShader());
		humanoidShader->load("instanced");
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
	ofScale(7.5);
	ofRotateXDeg(-90);
	ofRotateZDeg(90);
	brainGlow.getMesh().drawWireframe();
	ofPopMatrix();

	//ofPushMatrix();
	//ofTranslate(100, -100);
	//ofScale(2.5);
	//humanoidTex.bind();
	//humanoidMesh.draw();
	//humanoidTex.unbind();
	//ofPopMatrix();

	int iCount = 4;
	humanoidShader->begin();
	humanoidShader->setUniform4f("globalColor", 1.0, 0.4, 0.5, 1.0);
	humanoidShader->setUniform1i("iCount", iCount);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	ofPushMatrix();
	//ofRotateX(30);
	ofTranslate(0, 0, 500);
	ofScale(2.5);
	//humanoidMesh.draw();
	humanoidMesh.drawInstanced(OF_MESH_WIREFRAME, iCount * iCount);
	ofPopMatrix();
	humanoidShader->end();

	//// bind the shader
	//humanoidShader->begin();
	//// give the shader access to our texture
	////humanoidShader->setUniformTexture("tex0", mTexDepth, 0);
	//// feed the shader a normalized float value that changes over time, to animate things a little
	//humanoidShader->setUniform1f("timeValue", (ofGetElapsedTimeMillis() % 30000) / 30000.0f);
	//// we only want to see triangles facing the camera.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//
	//// let's draw 128 * 128 == 16384 boxes !
	//humanoidMesh.drawInstanced(OF_MESH_FILL, 12 * 12);
	//
	//glDisable(GL_CULL_FACE);
	//humanoidShader->end();



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