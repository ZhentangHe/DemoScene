#include "FlowParticle.h"

FlowParticle::FlowParticle(const ofVec3f& initPos) {
	life = ofGetFrameRate() * 100;
	speed = 2;
	radius = 2;
	color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	pos = initPos;
	acc = ofVec3f::zero();
	vel = ofVec3f::zero();
}

FlowParticle::~FlowParticle() {

}

void FlowParticle::update() {
	move();
	checkEdge();
	trail.push_front(pos);
	while (trail.size() > 60) {
		trail.pop_back();
	}
	life--;
}

void FlowParticle::move() {
	float deg = 360. * ofNoise(
		pos.x / 300.,
		pos.y / 300.,
		pos.z / 300.,
		ofGetElapsedTimeMillis() / 10000.
	);
	float rad = ofDegToRad(deg);
	acc.set(cos(rad), sin(rad), (cos(rad) + sin(rad))/2.);
	vel += acc;
	vel = vel.normalize() * speed;
	pos += vel;
}

void FlowParticle::checkEdge() {
	if (pos.x > 300) {
		pos.x = -300;
		trail.clear();
	}
	if (pos.y > 300) {
		pos.y = -300;
		trail.clear();
	}
	if (pos.z > 300) {
		pos.z = -300;
		trail.clear();
	}
	if (pos.x < -300) {
		pos.x = 300;
		trail.clear();
	}
	if (pos.y < -300) {
		pos.y = 300;
		trail.clear();
	}
	if (pos.z < -300) {
		pos.z = 300;
		trail.clear();
	}
}

void FlowParticle::display() {
	//ofPushMatrix();
	//ofPushStyle();
	//ofFill();
	ofSetColor(color);
	ofDrawSphere(pos, radius);
	for (size_t i = 0; i < trail.size() - 1; i++) {
		ofSetColor(color, ofMap(i, 0, trail.size() - 1, 255, 0));
		ofDrawLine(trail[i], trail[i + 1]);
	}
	//TODO:draw trail
	//ofPopStyle();
	//ofPopMatrix();
}

const bool FlowParticle::isDead() const {
	if (life <= 0)
		return true;
	return false;
}

