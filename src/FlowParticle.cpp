#include "FlowParticle.h"

FlowParticle::FlowParticle(const ofVec3f& initPos) {
	life = ofGetFrameRate();
	speed = 1.5;
	color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	pos = initPos;
	acc = ofVec3f(0, 0, 0);
	vel = ofVec3f(0, 0, 0) * speed;
}

FlowParticle::~FlowParticle() {

}

void FlowParticle::update() {
	vel += acc;
	vel = vel.normalize() * speed;
	acc *= 0;
	life--;
}

bool FlowParticle::checkEdge() {
	return bool();
}

void FlowParticle::display() {
	ofPushMatrix();
	ofPushStyle();
	ofFill();
	ofSetColor(color);
	ofDrawEllipse(pos, 2., 2.);
	ofPopStyle();
	ofPopMatrix();
}

const bool FlowParticle::isDead() const {
	if (life <= 0)
		return true;
	return false;
}

