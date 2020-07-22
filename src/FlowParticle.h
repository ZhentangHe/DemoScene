#pragma once

#include "ofMain.h"

class FlowParticle {

public:
	FlowParticle() = delete;
	FlowParticle(const ofVec3f& initPos);
	~FlowParticle();

	void update();
	void move();
	void checkEdge();
	void display();
	const bool isDead() const;
	//TODO: get; set;

private:
	ofVec3f vel;	//velocity
	ofVec3f acc;	//acceleration
	ofVec3f pos;	//position 
	ofColor color;  //color
	float speed;
	int life;
	float radius;
	deque<ofVec3f> trail;
	const size_t trailMaxSize = 60;
	vector<ofColor> trailColors;

};