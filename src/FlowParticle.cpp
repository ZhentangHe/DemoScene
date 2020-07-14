#include "FlowParticle.h"

FlowParticle::FlowParticle(const ofVec3f& initPos) {
	life = ofGetFrameRate() * 100;
	speed = 2;//TODO
	color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	pos = initPos;
	acc = ofVec3f(0, 0, 0);
	vel = ofVec3f(1, 1, 1) * speed;
}

FlowParticle::~FlowParticle() {

}

void FlowParticle::update() {
	vel += acc;
	vel = vel.normalize() * speed;
	acc *= 0;
	pos += vel;
	life--;
}

bool FlowParticle::checkEdge() {
	return bool();
}

void FlowParticle::display() {
	//ofPushMatrix();
	//ofPushStyle();
	//ofFill();
	ofSetColor(color);
	ofDrawSphere(pos, 2.);
	//TODO:draw trail
	//ofPopStyle();
	//ofPopMatrix();
}

const bool FlowParticle::isDead() const {
	if (life <= 0)
		return true;
	return false;
}

